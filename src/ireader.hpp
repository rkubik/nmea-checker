#pragma once

#include <string>

class IReader
{
public:
    /**
     * Returns true if the reader is complete.
     *
     * @return true if reader is complete, false otherwise.
     */
    virtual bool done(void) = 0;

    /**
     * Return the next line in the buffer.
     *
     * @return next line in buffer.
     */
    virtual std::string read_line(void) = 0;
};
