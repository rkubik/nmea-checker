#include "valid_command.hpp"
#include "string_reader.hpp"
#include "serial_reader.hpp"
#include "file_reader.hpp"
#include "utils.hpp"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

ValidCommand::ValidCommand(void)
{
    desc_.add_options()
        ("file,f", po::value<string>(), "File input")
        ("serial,d", po::value<string>(), "Serial input")
        ("sentence,s", po::value<string>(), "Sentence input")
        ("stop-error,r", "Stop on first error")
    ;
}

bool ValidCommand::execute(void)
{
    if (vm_.count("stop-error")) {
        streamer_.stop_on_error();
    }

    if (vm_.count("file")) {
        streamer_.set_reader(new FileReader(vm_["file"].as<string>()));
    } else if (vm_.count("serial")) {
        streamer_.set_reader(new SerialReader(vm_["serial"].as<string>()));
    } else if (vm_.count("sentence")) {
        streamer_.set_reader(new StringReader(vm_["sentence"].as<string>()));
    } else {
        return usage("Must choose at least one input");
    }

    streamer_.on_fail_checksum(print_checksum);
    streamer_.on_fail_corrupt(print_corrupt);
    streamer_.on_done(print_stats);

    return streamer_.start();
}

void ValidCommand::print_stats(const NmeaStats &stats)
{
    cout << "Total sentences: " << stats.num_sentences << endl
         << "Total empty:     " << stats.num_empty << endl
         << "Total unknown:   " << stats.num_unknown << endl
         << "Total errors:    " << stats.num_corrupt + stats.num_checksum << endl
         << "  Corrupt:       " << stats.num_corrupt << endl
         << "  Bad Checksum:  " << stats.num_checksum << endl
         << "Error rate:      "
         << fixed
            << showpoint
                << setprecision(2)
                    << (stats.num_sentences - stats.num_empty == 0 ? 0 :
                    ((double) (stats.num_corrupt + stats.num_checksum)/
                    (double) (stats.num_sentences - stats.num_empty) * 100))
         << "%" << endl;
}

void ValidCommand::print_checksum(size_t line_no, const string &message, uint8_t cs)
{
    cout << line_no << ") " << utils::trim(message) << " (BAD CHECKSUM: ";
    printf("%02X", cs);
    cout << ")" << endl;
}

void ValidCommand::print_corrupt(size_t line_no, const string &message)
{
    cout << line_no << ") " << utils::trim(message) << " (CORRUPTED)" << endl;
}
