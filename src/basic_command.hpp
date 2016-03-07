#pragma once

#include <boost/program_options.hpp>
namespace po = boost::program_options;

class BasicCommand
{
public:
    BasicCommand(void);

    /**
     * Parse command-line arguments.
     *
     * @param argc
     * @param argv
     */
    bool execute(int argc, char* argv[]);

    /**
     * Print program usage.
     *
     * @return True
     */
    bool usage(void);

    /**
     * Print program usage with an error message.
     *
     * @param False
     */
    bool usage(const std::string &error);

protected:
    /**
     * Run command.
     *
     * @return whether command was successful
     */
    virtual bool execute(void);

    po::options_description desc_;
    po::positional_options_description pos_;
    po::variables_map vm_;
};
