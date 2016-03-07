#include "serial_reader.hpp"

#include <stdexcept>
using namespace std;

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>

volatile bool SerialReader::signal_ = false;

SerialReader::SerialReader(const string &device) : fd_(-1), done_(false)
{
    fd_ = open(device.c_str(), O_RDWR | O_NOCTTY);

    if (fd_ == -1) {
        throw runtime_error("Unable to open serial device: " + device);
    }

    struct termios ts;
    if (tcgetattr(fd_, &ts) == -1) {
        throw runtime_error("tcgetattr failed");
    }
    cfmakeraw(&ts);
    if (tcsetattr(fd_, TCSANOW, &ts) == -1) {
        throw runtime_error("tcsetattr failed");
    }

    signal(SIGINT, signal_handler);
}

SerialReader::~SerialReader()
{
    if (fd_ != -1) {
        close(fd_);
    }
}

bool SerialReader::done(void)
{
    return  done_ || signal_;
}

string SerialReader::read_line(void)
{
    string line;
    bool start = false;

    for (;;) {
        char buffer[1];

        int num = read(fd_, buffer, 1);

        if (num == 0) {
            break;
        } else if (num == -1) {
            done_ = true;
            break;
        }

        if (!start && buffer[0] == '$') {
            start = true;
        }

        if (start) {
            line += buffer[0];
            if (buffer[0] == '\n') {
                break;
            }
        }

        if (line.size() >= 82) {
            break;
        }
    }
    return line;
}

void SerialReader::signal_handler(int sig)
{
    signal_ = true;
}
