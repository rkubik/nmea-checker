#include "string_reader.hpp"
using namespace std;

StringReader::StringReader(const string &message)
{
}

bool StringReader::done(void)
{
    return true;
}

string StringReader::read_line(void)
{
    return message_;
}
