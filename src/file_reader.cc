#include "file_reader.hpp"

#include <stdexcept>
using namespace std;

FileReader::FileReader(const string &file)
{
    file_.open(file);

    if (!file_) {
        throw runtime_error("Unable to open file: " + file);
    }
}

bool FileReader::done(void)
{
    return file_.eof();
}

string FileReader::read_line(void)
{
    string line;
    if(file_.is_open()) {
        getline(file_, line);
    }
    return line;
}
