/*
Body of serial port node
*/

#pragma once
// #include <Geode/Geode.hpp>
#include <Geode/cocos/base_nodes/CCNode.h>
#include <Geode/loader/Mod.hpp>
#include <memory> 
#include <string>

using namespace geode::prelude;

class SerialNode : public CCNode {
private:
    // std::unique_ptr<SimpleSerial> writer;

public:
    SerialNode();
    static SerialNode* create(); 
    bool init();
    bool initSerial(const std::string &com_port, DWORD COM_BAUD_RATE);
    bool isActive();
    bool deactivate();
    void writeBool(bool input);
    void writeInt(int input);
    void writeString(std::string input);
    // add more writer functions here
    ~SerialNode();

        
};