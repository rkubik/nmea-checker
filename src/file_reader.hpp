#pragma once

#include "ireader.hpp"

#include <fstream>

class FileReader : public IReader
{
public:
    FileReader(const std::string &file);

    /**
     * Signal that the file is done reading.
     *
     * @return True if next line is EOF, false otherwise.
     */
    bool done(void) override;

    /**
     * Return next line in opened file. Newlines are stripped from
     * the end of the line.
     *
     * @param next line
     */
    std::string read_line(void) override;

private:
    std::ifstream file_;
};
