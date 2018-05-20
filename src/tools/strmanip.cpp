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
	return str;
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

std::string insert_args(const std::string& str, const std::vector<std::string>& args) {
	std::string result = str;
	for (uint i=0; i<args.size(); i++) {
		result = replace_all(result, "$" + std::to_string(i + 1), args[i]);
	}

	return result;
}