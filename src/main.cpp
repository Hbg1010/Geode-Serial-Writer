/**
 * Include the Geode headers.
 */

#include "simple-serial-port/SimpleSerial.cpp"
#include <memory> 
#include <string>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/PlayLayer.hpp>

// using this to check player deaths
class $modify (myPlayLayer, PlayLayer) {

	// holds the writer
	struct Fields {
		std::unique_ptr<SimpleSerial> writer;
		int cutOff = Mod::get()->getSettingValue<int64_t>("percentMode");

		// Function to initialize the serial object
		void initSerial(const std::string &com_port, DWORD COM_BAUD_RATE) {
			writer = std::make_unique<SimpleSerial>(com_port, COM_BAUD_RATE);
		}

		// writes a boolean to the serial monitor. This allows me to manipulate the LED
		void write(bool input) {

			// this solves a problem as reset is run prior to innit????????????????
			if (writer == nullptr) return;

			else if (writer->IsConnected()) {
			// defines the input as a string
			std::string val = input ? "1" : "0";
			char *to_send = &val[0];

			bool x = writer->WriteSerialPort(to_send); // write to port

			} else {
				log::debug("The writer is not connected! Please check to see if you have set the com port or baud rate correctly!");
			}
		}

		// exclusivly used to drop writer on reset
		~Fields() {

			try {
				writer->CloseSerialPort();
			}
			catch(const std::exception& e){
				log::debug("Writer was dropped but was not reused");
			}

			writer.release(); // drops the var
		}
	};

	// inits the scene
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {

	/**
	 * We call the original init function so that the
	 * original class is properly initialized.
	 */
	if (!PlayLayer::init(level,useReplay, dontCreateObjects)) {
		return false;
	}

		// reads user settings
		std::string x = Mod::get()->getSettingValue<std::string>("COM port");

		DWORD COM_BAUD_RATE = static_cast<uint32_t>(Mod::get()->getSettingValue<int64_t>("baud-rate"));
		log::debug("baud rate is {}", Mod::get()->getSettingValue<int64_t>("baud-rate"));
		// initiates it
		m_fields->initSerial(x, COM_BAUD_RATE);

		return true;

	}

	void resetLevel() {

		PlayLayer::resetLevel();

		// checks to see if the player has passed the cutoff
		if (PlayLayer::getCurrentPercentInt() >= m_fields->cutOff) {
			try {
				m_fields->write(true); 
			}
			catch(const std::exception& e)
			{
				log::debug("Writer was not able to write");
			}
		}
	}
};
