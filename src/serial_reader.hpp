#pragma once

#include "ireader.hpp"

class SerialReader : public IReader
{
public:
    SerialReader(const std::string &device);
    ~SerialReader();

    bool done(void) override;

    std::string read_line(void) override;

    static void signal_handler(int sig);

private:
    static volatile bool signal_;

    int fd_;
    bool done_;
};
