#include "ReadBlock.h"
#include "BlockMaker.h"

static BlockMaker<ReadBlock> readfileMaker("readfile");

std::string ReadBlock::operation(std::vector<std::string> data) 
{
	std::ifstream input_file;
	std::string resultStr = "", tmp;

	input_file.open(data[0]);

	while (getline(input_file, tmp)) 
	{
		resultStr += tmp + "\n";
	}
	input_file.close();
	return resultStr;
}