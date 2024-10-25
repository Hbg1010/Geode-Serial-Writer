/*
Body of serial port node
*/

#pragma once
#include <Geode/Geode.hpp>
#include "../simple-serial-port/SimpleSerial.cpp"
#include <memory> 
#include <string>

using namespace geode::prelude;

class SerialNode : public CCNode {
    private:
        std::unique_ptr<SimpleSerial> writer;

    public:
        bool init();
        bool initSerial(const std::string &com_port, DWORD COM_BAUD_RATE);
        void writeBool(bool input);
        void writeInt(int input);
        bool isActive();
        bool deactivate();
        ~SerialNode();

        static SerialNode* create(); 
};