#include "serial_port_linux.h"

#include <thread>
#include <future>
#include <functional>

#ifdef __linux__

#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

// TODO Move this
// Serial port write rate in seconds.
#define SERIAL_PORT_RATE 3

// https://codezup.com/mastering-asynchronous-programming-in-cpp/

// Create a future to represent the result of an asynchronous operation

/**
 * Async for my serial port testing.
 */
std::future<void> SerialPortLinux::SerialPortAsync(int fd, const char *message)
{

    // Create a coroutine that performs an asynchronous operation
    // std::function<int()> op = []()
    
    // Fix for error, added '&' here.
    // https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
    std::function<void()> op = [&]()
    {
        // Write to the serial port every set amount of seconds.
        std::this_thread::sleep_for(std::chrono::seconds(SERIAL_PORT_RATE));
        if (WriteToSerialPort(fd, message, strlen(message)) < 0)
        {
            std::cerr << "Error writing to serial port: " << strerror(errno) << std::endl;
        }
    };

    CloseSerialPort(fd);

    // Create a future to represent the result of the operation
    return std::async(std::launch::async, op);
}
#endif
//

/**
 * Open the serial port
 *
 * @param portname The serial port to open.
 */
int SerialPortLinux::OpenSerialPort(const char *portname)
{
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        std::cerr << "Error opening " << portname << ": "
                  << strerror(errno) << std::endl;
        return - // Function to open the serial port
            1;
    }
    return fd;
}

/**
 * Configure the serial port
 *
 * @param fd
 * @param speed
 */
bool SerialPortLinux::ConfigureSerialPort(int fd, int speed)
{
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0)
    {
        std::cerr << "Error from tcgetattr: " << strerror(errno)
                  << std::endl;
        return false;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit characters
    tty.c_iflag &= ~IGNBRK;                     // disable break processing
    tty.c_lflag = 0;                            // no signaling chars, no echo, no
                                                // canonical processing
    tty.c_oflag = 0;                            // no remapping, no delays
    tty.c_cc[VMIN] = 0;                         // read doesn't block
    tty.c_cc[VTIME] = 5;                        // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);   // ignore modem controls,
                                       // enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        std::cerr << "Error from tcsetattr: " << strerror(errno)
                  << std::endl;
        return false;
    }
    return true;
}

/**
 * Read data from the serial port.
 *
 * @param fd
 * @param buffer
 * @param size
 */
int SerialPortLinux::ReadFromSerialPort(int fd, char *buffer, size_t size)
{
    return read(fd, buffer, size);
}

/**
 * Write data to the serial port.
 *
 * @param fd
 * @param buffer
 * @param size
 */
int SerialPortLinux::WriteToSerialPort(int fd, const char *buffer, size_t size)
{
    return write(fd, buffer, size);
}

/**
 * Close the serial port.
 *
 * @param fd
 */
void SerialPortLinux::CloseSerialPort(int fd) { close(fd); }

/**
 * Setup the serial port
 *
 * @param portname The name of the port to setup.
 */
void SerialPortLinux::SetupSerialPort(const char *portname)
// void SerialPortLinux::SetupSerialPort()
{
    int fd = OpenSerialPort(portname);

    if (fd < 0)
    {
        std::cout << "Couldn't open serial port." << std::endl;
        return;
    }

    if (!ConfigureSerialPort(fd, B9600))
    {
        CloseSerialPort(fd);
        std::cout << "Couldn't configure serial port, closed connection." << std::endl;

        return;
    }

    //------
    // Writing to serial port
    //------
    const char *message = "Hello, Serial Port!";
    if (WriteToSerialPort(fd, message, strlen(message)) < 0)
    {
        std::cerr << "Error writing to serial port: " << strerror(errno) << std::endl;
    }

    // Blocking operation
    // FIXME: Make this async or something, possibly use coroutines.
    // while (true)
    // {
    //     // Write to the serial port every set amount of seconds.
    //     std::this_thread::sleep_for(std::chrono::seconds(SERIAL_PORT_RATE));
    //     if (WriteToSerialPort(fd, message, strlen(message)) < 0)
    //     {
    //         std::cerr << "Error writing to serial port: " << strerror(errno) << std::endl;
    //     }
    // }

    // Attempt to use the new serial port async function
    // SerialPortAsync(fd, message);

    // TODO Fix this for the async function, it doesn't work and says bad file descriptor.
    // SerialPortAsync(fd, message).get();

    //------
    // Reading from serial port
    //------
    char buffer[100];
    int n = ReadFromSerialPort(fd, buffer, sizeof(buffer));
    if (n < 0)
    {
        std::cerr << "Error reading from serial port: "
             << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "Read from serial port: "
             << std::string(buffer, n) << std::endl;
    }

    CloseSerialPort(fd);
}

// #endif // __linux__