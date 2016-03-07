#include "utils.hpp"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
using namespace std;

namespace utils {

    void replace_all(string &str, const string &to, const string &from)
    {
        if(from.empty()) {
            return;
        }

        size_t start_pos = 0;

        while((start_pos = str.find(from, start_pos)) != string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

    string &ltrim(string &s)
    {
        s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
        return s;
    }

    string &rtrim(string &s)
    {
        s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
        return s;
    }

    string trim(string s)
    {
        return ltrim(rtrim(s));
    }

};
