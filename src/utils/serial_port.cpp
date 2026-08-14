#include "serial_port.h"

// https://www.geeksforgeeks.org/cpp/serial-port-connection-in-cpp/

// TODO Test this on Windows later.

#include <thread>

#include <future>
#include <functional>

#include "serialib.h"

// Serial port baud rate.
#define SERIAL_PORT_RATE 115200

// Serial port name
#if defined (_WIN32) || defined(_WIN64)
    //for serial ports above "COM9", we must use this extended syntax of "\\.\COMx".
    //also works for COM0 to COM9.
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea?redirectedfrom=MSDN#communications-resources
    #define SERIAL_PORT "\\\\.\\COM1"
#endif
#if defined (__linux__) || defined(__APPLE__)
    #define SERIAL_PORT "/dev/ttyUSB0"
#endif

SerialPortTest::SerialPortTest() 
{
    // printf ("Successful connection to %s\n",SERIAL_PORT);
    
    errorOpening = serial.openDevice(SERIAL_PORT, SERIAL_PORT_RATE);

    // if (errorOpening != 1) 
    // {
    //     std::cout << "Successful connection to " << SERIAL_PORT << std::endl;
    // } else 
    // {
    //     std::cerr << "Error: Connection to serial port " << SERIAL_PORT << " failed." << std::endl;
    // }
}

/**
 * Close the serial device and cleanup.
 */
SerialPortTest::~SerialPortTest()
{
    std::cout << "Closing connection to " << SERIAL_PORT << std::endl;
    serial.closeDevice();
}


/**
 * Setup the serial port
 * 
 * TODO Make this a bit more efficient, store the serial object instead of closing it each time.
 * I may have this working, I only get the closing connection message when I close ImGui.
 *
 * @param portname The name of the port to setup.
 */
// void SerialPortTest::SetupSerialPort(const char *portname)
void SerialPortTest::SendMessage(const char *portname, const char* message)
{

    // New test, this should work on Windows and Linux.
    // Serial object
    // serialib serial;

    // Connection to serial port
    // char errorOpening = serial.openDevice(SERIAL_PORT, 115200);

    // If connection fails, return the error code otherwise, display a success message
    if (errorOpening != 1) return;

    // Display ASCII characters (from 32 to 128)
    // for (int c=32;c<128;c++)
    // {
    //     serial.writeChar(c);
    //     usleep(10000);
    // }

    // Write a string to the serial port.
    // serial.writeString("Hello from C++ to serial port");
    serial.writeString(message);

    // Close the serial device
    // serial.closeDevice();
    //
}
