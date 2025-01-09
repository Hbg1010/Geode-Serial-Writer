/**
 * This file is just for examples.
 */

// #include "simple-serial-port/SimpleSerial.cpp"
#include <memory> 
#include <string>
#include <Geode/Geode.hpp>
#include "nodes/SerialNode.cpp"

using namespace geode::prelude;


#include <Geode/modify/PlayLayer.hpp>
// using this to check player deaths
// class $modify (myPlayLayer, PlayLayer) {

// 	struct Fields {
// 		SerialNode* writer = nullptr;
// 	};

// 	// inits the scene
// 	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
// 		log::debug("init");
// 	/**
// 	 * We call the original init function so that the
// 	 * original class is properly initialized.
// 	 */
// 	if (!PlayLayer::init(level,useReplay, dontCreateObjects)) {
// 		return false;
// 	}

// 	// defines the writer.
// 	m_fields->writer = SerialNode::create();
// 	CCNode* sNode = m_fields->writer;
// 	sNode->setID("Serial Writer");
// 	log::debug("created in main. node: {}", sNode);

// 	this->addChild(sNode);

// 		return true;

// 	}

// 	void resetLevel() {
// 		log::debug("resetLevel");
// 		PlayLayer::resetLevel();

// 		if (m_fields->writer != nullptr) {
// 			m_fields->writer->writeBool(true);
// 		}
// 	}
// };

// old stuff 
// // holds the writer
// 	struct Fields {
// 		std::unique_ptr<SimpleSerial> writer;
// 		int cutOff = Mod::get()->getSettingValue<int64_t>("percentMode");

// 		// Function to initialize the serial object
// 		void initSerial(const std::string &com_port, DWORD COM_BAUD_RATE) {
// 			writer = std::make_unique<SimpleSerial>(com_port, COM_BAUD_RATE);
// 		}

// 		// writes a boolean to the serial monitor. This allows me to manipulate the LED
// 		void write(bool input) {

// 			// this solves a problem as reset is run prior to innit????????????????
// 			if (writer == nullptr) return;

// 			else if (writer->IsConnected()) {
// 			// defines the input as a string
// 			std::string val = input ? "1" : "0";
// 			char *to_send = &val[0];

// 			bool x = writer->WriteSerialPort(to_send); // write to port

// 			} else {
// 				log::debug("The writer is not connected! Please check to see if you have set the com port or baud rate correctly!");
// 			}
// 		}

	// 	// exclusivly used to drop writer on reset
	// 	~Fields() {

	// 		try {
	// 			writer->CloseSerialPort();
	// 		}
	// 		catch(const std::exception& e){
	// 			log::debug("Writer was dropped but was not reused");
	// 		}

	// 		writer.release(); // drops the var
	// 	}
	// };



/*
THIS DID NOT WORK. HAVING MULTIPLE NODES WILL CAUSE ISSUES WITH FUTURE WRITING. FIX THIS!

*/

#include <Geode/modify/PlayerObject.hpp>

class $modify (layer, PlayerObject) {
	struct Fields {
	SerialNode* writer = nullptr;
	};

	bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
		if (!PlayerObject::init(p0, p1, p2, p3, p4)) return false;


		m_fields->writer = SerialNode::create();
		CCNode* sNode = m_fields->writer;
		log::debug("created a node! {}", sNode);
		sNode->setID("Serial Writer");

		try
		{
			this->addChild(sNode, 3, 3);

		}
		catch(const std::exception& e)
		{
			log::debug("Kill yourself");
		}
		

		return true;
	}

	bool pushButton(PlayerButton p0) {
		if (m_fields->writer != nullptr) m_fields->writer->writeBool(true);

		
		return PlayerObject::pushButton(p0);
	}


};

// #include <Geode/modify/MenuLayer.hpp>
// class $modify(myMenuLayer, MenuLayer) {

// 		struct Fields {
// 			SerialNode* writer = nullptr;
// 			};

// 	bool init() {
// 		if (!MenuLayer::init()) return false;
// 		m_fields->writer = SerialNode::create();
// 		CCNode* sNode = m_fields->writer;
// 		log::debug("created a node! {}", sNode);
// 		sNode->setID("Serial Writer");

// 		return true;
// 	}

// 	void onMyProfile(CCObject* sender) {
// 		MenuLayer::onMyProfile(sender); 

// 		m_fields->writer->writeBool(true);
// 	}
// };