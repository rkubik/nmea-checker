#pragma once

#include "ireader.hpp"

class StringReader : public IReader
{
public:
    StringReader(const std::string &message);

    /**
     * Return true.
     */
    bool done(void) override;

    /**
     * Return message.
     *
     * @param return stored message.
     */
    std::string read_line(void) override;

private:
    std::string message_;
};
