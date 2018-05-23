#ifndef STRMANIP_HPP_
#define STRMANIP_HPP_

#include <vector>
#include <string>

/** This file contains various string manipulation methods and other handy functions.
*/

/// Split a string with a specific delimiter.
std::vector<std::string> split(const std::string& str, const char& delimiter);

/// Removes whitespace left and right of the string.
std::string trim(const std::string& str);

/// Extracts a substring following the python syntax because I am lazy.
std::string extract_substring(const std::string& str, const std::string& bounds);

/// Parse a text file an return its lines.
std::vector<std::string> parse_file(const std::string& filepath);

/// Replace instances of 'occurence' by 'sub'
std::string replace_all(const std::string& text, const std::string& occurence, const std::string& sub);

/// Replace all instances of chars in 'occurence' by 'sub'
std::string replace_char(const std::string& text, const std::string& occurence, const char& sub);

/// Insert value at specific places in string
std::string insert_args(const std::string& str, const std::vector<std::string>& args);

/// Wrap text at specified length (simply add '\n')
std::string wrap_text(const std::string& str, int len);

#endif // STRMANIP_HPP_