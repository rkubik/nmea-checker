#pragma once

#include "ireader.hpp"

class SerialReader : public IReader
{
public:
    SerialReader(const std::string &device);
    ~SerialReader();

    /**
     * Return true when SIGINT signal is received.
     *
     * @return true when done reading serial port
     */
    bool done(void) override;

    /**
     * Read next line in serial buffer.
     */
    std::string read_line(void) override;

    /**
     * Receive signal.
     *
     * @param sig Signal number
     */
    static void signal_handler(int sig);

private:
    static volatile bool signal_;

    int fd_;
    bool done_;
};
