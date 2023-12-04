#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>

std::unordered_map <std::string, uint32_t> limits = {
	{"blue", 14},
	{"green", 13},
	{"red", 12}
};


std::vector<std::string> split(const std::string& str, char c) {
	size_t offset = 0;
	size_t prevOffset = 0;
	std::vector<std::string> returnVector;
	while ((offset = str.find(c, offset)) != std::string::npos)
	{
		returnVector.push_back(str.substr(prevOffset, offset - prevOffset));
		offset++;
		prevOffset = offset;

	}
	if (prevOffset < str.length()) {
		returnVector.push_back(str.substr(prevOffset));
	}
	return returnVector;
}

std::string replace(std::string str, const std::string& from, const std::string& to) {
	size_t offset = 0;
	size_t prevOffset = 0;
	std::string returnString;
	while ((offset = str.find(from, offset)) != std::string::npos)
	{
		returnString += str.substr(prevOffset, offset - prevOffset) + to;
		offset++;
		prevOffset = offset;

	}
	if (prevOffset < str.length()) {
		returnString += str.substr(prevOffset);
	}
	return returnString;
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cerr << "Missing first argument: filepath" << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	if (!file.good()) {
		std::cerr << "File couldn't be open" << std::endl;
	}
	std::string line;
	size_t ID = 1;
	size_t sum = 0;
	while (std::getline(file, line)) {
		std::unordered_map<std::string, uint64_t> max = {
			{"red", 0},
			{"blue", 0},
			{"green", 0}
		};
		bool gameIsPossible = true;
		auto parts = split(line, ';');
		parts[0] = split(parts[0], ':')[1];
		for (auto part : parts) {
			auto balls = split(part, ',');
			for (auto t : balls) {
				auto pair = split(t, ' ');
				uint32_t number = atoi(pair[1].c_str());
				std::string& color = pair[2];
				if (number > max[color]) {
					max[color] = number;
				}
			}
		}
		sum += max["red"] * max["green"] * max["blue"];

	}
	std::cout << "Suma: " << sum << std::endl;

	file.close();
}

