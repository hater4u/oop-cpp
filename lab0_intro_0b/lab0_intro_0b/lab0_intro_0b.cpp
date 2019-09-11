#include <iostream>
#include <fstream>
#include <string>
#include <map>

int word_count(std::string inputf, std::string outputf) {
	std::string line;

	std::ifstream in(inputf);
	std::ofstream out;
	out.open(outputf);

	/*if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();*/

	while (std::getline(in, line)) {

		//std::cout << line << std::endl;
	}

	out.close();
	in.close();
	return 0;
}

int main(int argc, char** argv) {
	word_count(argv[1], argv[2]);

	return 0;
}