#pragma once

#include "ireader.hpp"

class StringReader : public IReader
{
public:
    StringReader(const std::string &message);

    bool done(void) override;

    std::string read_line(void) override;

private:
    std::string message_;
};
