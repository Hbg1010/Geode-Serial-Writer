#include "SerialNode.hpp"
#include "../simple-serial-port/SimpleSerial.cpp"

static SimpleSerial* staticWriter = nullptr;
static unsigned int serialCount = 0;


// this 
SerialNode::SerialNode() {
    serialCount++;
}

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

    if (staticWriter == nullptr) {
        return SerialNode::initSerial(Mod::get()->getSettingValue<std::string>("COM port"), COM_BAUD_RATE);
    }

    return true;
}

// creates the serial monitor 
bool SerialNode::initSerial(const std::string &com_port, DWORD COM_BAUD_RATE) {

    try
    {
        staticWriter = new SimpleSerial(com_port, COM_BAUD_RATE);
        log::debug("I made a new writer!");
    }
    catch(const std::exception& e)
    {
        log::error("Error opening serial port: {}", e);
        return false; 
    }

    log::debug("the static monitor is on? {}", staticWriter->IsConnected());

    return true;
}

void SerialNode::writeBool(bool input) {
    // this solves a problem as reset is run prior to innit????????????????
    if (staticWriter == nullptr) return;
    
    if (staticWriter->IsConnected()) {
    // defines the input as a string
    std::string val = input ? "1" : "0";
    char *to_send = &val[0];
    
    bool x = staticWriter->WriteSerialPort(to_send); // write to port

    } else {
        log::debug("The writer is not connected! Please check to see if you have set the com port or baud rate correctly!");
    }
}

// void SerialNode::writeInt(int value) {
//     // this solves a problem as reset is run prior to innit????????????????
//     if (staticWriter == nullptr) return;

//     else if (staticWriter->IsConnected()) {
//     // defines the input as a string
//     std::string val = String
//     char *to_send = &val[0];
    
//     bool x = staticWriter->WriteSerialPort(to_send); // write to port

//     } else {
//         log::debug("The writer is not connected! Please check to see if you have set the com port or baud rate correctly!");
//     }
// }

// exclusivly used to drop writer on reset
SerialNode::~SerialNode() {
    log::debug("deconstruct {} and there are now {} writers", this, serialCount);
    
    serialCount--; // decrements the counter

    if (serialCount == 0) {
            try {
            staticWriter->CloseSerialPort();
        }
        catch(const std::exception& e){
            log::debug("Writer was dropped but was not reused");
        }

        staticWriter = nullptr;
    }
    
}

// returns if the serial monitor is active
bool SerialNode::isActive() {
    return staticWriter->IsConnected();
}



