#pragma once

#include <boost/program_options.hpp>
namespace po = boost::program_options;

class BasicCommand
{
public:
    BasicCommand(void);
    bool run(int argc, char* argv[]);
    bool usage(void);
    bool usage(const std::string &error);

protected:
    virtual bool execute(void);

    po::options_description desc_;
    po::positional_options_description pos_;
    po::variables_map vm_;
};
