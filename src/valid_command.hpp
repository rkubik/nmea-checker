#pragma once

#include "basic_command.hpp"
#include "nmea_streamer.hpp"

class ValidCommand : public BasicCommand
{
public:
    ValidCommand(void);

protected:
    bool execute(void) override;

    /**
     * Print NMEA streamer statistics.
     *
     * @param stats Statistics
     */
    static void print_stats(const NmeaStats &stats);

    /**
     * Print checksum error.
     *
     * @param line_no Line number
     * @param message NMEA sentence
     * @param cs Checksum value
     */
    static void print_checksum(size_t line_no, const std::string &message,
                               uint8_t cs);

    /**
     * Print corrupt error.
     *
     * @param line_no Line number
     * @param message NMEA sentence
     */
    static void print_corrupt(size_t line_no, const std::string &message);

private:
    NmeaStreamer streamer_;
};
