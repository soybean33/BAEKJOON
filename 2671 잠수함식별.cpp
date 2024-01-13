#include <iostream>
#include <string>
#include <regex>

int main() {
	std::string s;
	std::cin >> s;
	std::cout << (std::regex_match(s, std::regex("(100+1+|01)+")) ? "SUBMARINE": "NOISE");
}