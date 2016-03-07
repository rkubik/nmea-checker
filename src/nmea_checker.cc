#include "valid_command.hpp"
#include "checksum_command.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
using namespace std;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    const string command = (argc > 1) ? string(argv[1]) : "";
    unique_ptr<BasicCommand> runner(new BasicCommand());

    try {
        if (command == "valid") {
            runner = move(unique_ptr<ValidCommand>(new ValidCommand()));
        } else if (command == "checksum") {
            runner = move(unique_ptr<ChecksumCommand>(new ChecksumCommand()));
        }
        return runner->execute(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
    } catch(const runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
    }
    return EXIT_FAILURE;
}
