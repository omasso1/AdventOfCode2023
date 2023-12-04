#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


std::string numbers[] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

int64_t find_in_string(const std::string& str, size_t index) {
	size_t i = 0;
	for (const std::string& number : numbers) {
		if (str.substr(index, number.length()).find(number.c_str()) != std::string::npos) {
			return i;
		}
		i++;
	}
	return -1;
}


mojaUnia cos;
cos.a = 5;
cos.b = 7;

int main(int argc, char**argv)
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

	uint64_t sum = 0;
	while (std::getline(file, line)) {
		size_t left = 0;
		size_t right = line.length();
		uint64_t temp;


		while (left < line.size()) {
			if (isdigit(line[left])) {
				sum += (line[left] & 0x0f) * 10;
				break;
			}
			else if ((temp = find_in_string(line, left)) != -1) {
				sum += 10 * temp;
				break;
			}
			left++;
		};
		while (right-- != 0) {
			if (isdigit(line[right])) {
				sum += (line[right] & 0x0f);
				break;
			}
			else if ((temp = find_in_string(line, right)) != -1) {
				sum += temp;
				break;
			}
		}

	}

	std::cout << (sum) << std::endl;

	file.close();
}

