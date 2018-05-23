#include "strmanip.hpp"

#include <sstream>
#include <fstream>

#include "../global.hpp"

std::vector<std::string> split(const std::string& str, const char& delimiter) {
	std::vector<std::string> items;
	std::stringstream stream(str);
	std::string item;
	while (std::getline(stream, item, delimiter)) {
		items.push_back(item);
	}
	return items;
}

std::string trim(const std::string& str) {
	
	std::string whitespace = "\n\r\t ";
	std::size_t true_begin = -1;
	std::size_t true_end = -1;
	
	bool previous_char_was_whitespace = false;
	for (int i=0; i<str.length(); i++) {
		if (whitespace.find(str[i]) == std::string::npos) {
			true_begin = i;// ? i - 1: i;
			break;
		}
	}
	for (int i=str.length() - 1; i >= 0; i--) {
		if (whitespace.find(str[i]) == std::string::npos) {
			true_end = i + 1;// ? i - 1: i;
			break;
		}
	}
	
	return str.substr(true_begin, true_end - true_begin);
}

std::string trim_internal(const std::string& str) {
	std::string text = "";
	std::string whitespace = "\n\r\t ";
	bool previous_char_was_whitespace = false;
	for (int i=0; i<str.length(); i++) {
		if (whitespace.find(str[i]) != std::string::npos) {
			if (!previous_char_was_whitespace) {
				previous_char_was_whitespace = true;
				text += str[i];
			}
		}
		else {
			previous_char_was_whitespace = false;
			text += str[i];
		}
	}
	
	return text;
}

std::string extract_substring(const std::string& str, const std::string& bounds) {
	std::vector<std::string> items = split(bounds, ':');
	if (items.size() > 1) {
		int a = items[0].empty() ? 0 : std::stoi(items[0]);
		int b = items[1].empty() ? str.length() - 1 : std::stoi(items[1]);
		
		if (a < 0) {
			a = str.length() + a;
		}
		
		if (b < 0) {
			b = str.length() + b;
		}
		
//		if (items.size() > 2) {
//			int pas = std::stoi(items[2]);
//		}
		
		return str.substr(a, (b - a > 0 ? b - a : 0));
	}
	return str;
}

std::vector<std::string> parse_file(const std::string& filepath) {
	std::ifstream myfile;
	std::vector<std::string> lines;
	std::string line;
	myfile.open(filepath);
	
	if (myfile) {
		
		while(std::getline(myfile, line)) {
			lines.push_back(line);
		}
		
		myfile.close();
	}
	
	return lines;
	
}

std::string replace_all(const std::string& input, const std::string& occurence, const std::string& sub) {
	std::string text = input;
	std::size_t it = -1;
	while (it = text.find(occurence, it + 1), it != std::string::npos) {
		text.replace(it, occurence.length(), sub);
		it += sub.length();
	}
	return text;
}

std::string replace_char(const std::string& input, const std::string& occurence, const char& sub) {
	std::string text = "";
	
	for (int i=0; i<input.size(); i++) {
		if (occurence.find(input[i]) != std::string::npos) {
			if (sub) {
				text += sub;
			}
		}
		else {
			text += input[i];
		}
	}
	
	return text;
}

std::string insert_args(const std::string& str, const std::vector<std::string>& args) {
	std::string result = str;
	for (uint i=0; i<args.size(); i++) {
		result = replace_all(result, "$" + std::to_string(i + 1), args[i]);
	}

	return result;
}

std::string wrap_text(const std::string& str, int len) {
	std::string result = str;
	
	result = replace_char(result, "\n", ' ');
//	result = trim(result);
//	LOG(result);
	result = trim_internal(result);
//	LOG(result);
	
	auto words = split(result, ' ');
	result = "";
	int count = 0;
	for (int i=0; i<words.size(); i++) {
		
		count += words[i].length();
		
		if (i && count >= len) {
			result += "\n ";
			count -= len;
		}
		else if (i) {
			result += " ";
		}
		result += words[i];
	}
	
//	for (int i=0;i<result.length(); i++) {
//		if (result[i] == '\t') result[i] = '#';
//		if (result[i] == ' ') result[i] = '_';
//	}
//	
	return result;
}