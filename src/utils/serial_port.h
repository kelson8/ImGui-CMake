#pragma once

#include <cstring>

#include <future>
#include <functional>

#include "serialib.h"

class SerialPortTest {

public:
    static SerialPortTest &getInstance()
    {
        static SerialPortTest instance; // Guaranteed to be destroyed.
        return instance;
    }

    void SendMessage(const char *portname, const char* message);

private:
    SerialPortTest();
    ~SerialPortTest(); // Optional deconstructor
    SerialPortTest(const SerialPortTest &) = delete;            // Prevent copy-construction
    SerialPortTest &operator=(const SerialPortTest &) = delete; // Prevent assignment


    serialib serial;
    char errorOpening;
};