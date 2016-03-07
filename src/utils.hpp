#pragma once

#include <string>

namespace utils {
    /**
     * Replace all occurances of string with substitute.
     *
     * @param str Reference of string to search and replace
     * @param to What to replace with
     * @param from What to search
     */
    void replace_all(std::string &str,
                     const std::string &to,
                     const std::string &from);

    /**
     * Left trim string.
     *
     * @param s Reference of string to trim
     * @return Reference of trimmed string
     */
    std::string &ltrim(std::string &s);

    /**
     * Right trim string.
     *
     * @param s Reference of string to trim
     * @return Reference of trimmed string
     */
    std::string &rtrim(std::string &s);

    /**
     * Left and right trim given string. Return new string.
     *
     * @param s String to trim
     */
    std::string trim(std::string s);
};