#include "checksum_command.hpp"
#include "minimea.hpp"

#include <cstdio>
#include <string>
#include <vector>
using namespace std;

ChecksumCommand::ChecksumCommand(void)
{
    desc_.add_options()
        ("sentence,s", po::value<vector<string> >(), "Sentence to check (multiple allowed)")
    ;
}

bool ChecksumCommand::execute(void)
{
    if (!vm_.count("sentence")) {
        return usage("Must specify at least one sentence");
    }

    for (const auto& sentence : vm_["sentence"].as<vector<string> >()) {
        printf("%02X\n", minmea_checksum(sentence.c_str()));
    }

    return true;
}
