#include "SerialNode.hpp"


SerialNode* SerialNode::create() {
    SerialNode* tempNode = new SerialNode();

    if (tempNode->init()) {
        tempNode->autorelease();

        return tempNode;
    } else {
        CC_SAFE_DELETE(tempNode);

        return nullptr;
    }
}

// inits a new Serial Node
bool SerialNode::init() {

    if (!CCNode::init()) return false;

    // returns true if serial monitor is inititated 
    DWORD COM_BAUD_RATE = static_cast<uint32_t>(Mod::get()->getSettingValue<int64_t>("baud-rate"));
    log::debug("baudRate: {}", Mod::get()->getSettingValue<int64_t>("baud-rate"));
    log::debug("comp port: {}", Mod::get()->getSettingValue<std::string>("COM port"));
    if (!SerialNode::initSerial(Mod::get()->getSettingValue<std::string>("COM port"), COM_BAUD_RATE)) return false;

    return true;
}

// creates the serial monitor 
bool SerialNode::initSerial(const std::string &com_port, DWORD COM_BAUD_RATE) {
    log::debug("Tryna log fuck it");
    try
    {
        writer = std::make_unique<SimpleSerial>(com_port, COM_BAUD_RATE);
    }
    catch(const std::exception& e)
    {
        return false; 
    }

    return true;
}

void SerialNode::writeBool(bool input) {
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
SerialNode::~SerialNode() {
    log::debug("deconstruct");
    try {
        writer->CloseSerialPort();
    }
    catch(const std::exception& e){
        log::debug("Writer was dropped but was not reused");
    }

    writer.release(); // drops the var
}

// returns if the serial monitor is active
bool SerialNode::isActive() {
    return writer->IsConnected();
}

