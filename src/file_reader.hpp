#pragma once

#include "ireader.hpp"

#include <fstream>

class FileReader : public IReader
{
public:
    FileReader(const std::string &file);

    bool done(void) override;

    std::string read_line(void) override;

private:
    std::ifstream file_;
};
