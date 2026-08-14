#pragma once

#include <cstring>

#include <future>
#include <functional>

class SerialPortLinux {

#ifdef __linux__

public:
    void SetupSerialPort(const char* portname);

private:
    std::future<void> SerialPortAsync(int fd, const char *message);

    int OpenSerialPort(const char *portname);
    bool ConfigureSerialPort(int fd, int speed);

    int ReadFromSerialPort(int fd, char *buffer, size_t size);
    int WriteToSerialPort(int fd, const char *buffer, size_t size);

    void CloseSerialPort(int fd);

    // TODO Figure out how to store this for later use.
    int serialPort;

#endif // __linux__

};