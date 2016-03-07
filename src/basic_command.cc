#include "basic_command.hpp"

#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

BasicCommand::BasicCommand(void)
{
    desc_.add_options()
        ("command,c", po::value<string>(), "valid/checksum")
        ("help,h",    "Help message")
    ;
    pos_.add("command", 1);
}

bool BasicCommand::execute(int argc, char* argv[])
{
    try {
        po::store(
            po::command_line_parser(argc, argv).
            options(desc_).
            positional(pos_).
            run(),
            vm_);

        if (vm_.count("help")) {
            return usage();
        }

        po::notify(vm_);
    } catch(const po::error &e) {
        throw runtime_error(e.what());
    }

    return execute();
}

bool BasicCommand::execute(void)
{
    return usage();
}

bool BasicCommand::usage(const string &error)
{
    usage();
    cerr << "Error: " << error << endl;
    return false;
}

bool BasicCommand::usage(void)
{
    cout << "nmea-checker - NMEA sentence validation tool" << endl << endl
         << "USAGE" << endl << endl
         << "\tnmea-checker [COMMAND] [OPTIONS...]" << endl << endl
         << "COMMAND" << endl << endl
         << "  valid" << endl
         << "  checksum" << endl << endl
         << "OPTIONS" << endl << endl
         << desc_ << endl;
    return true;
}
