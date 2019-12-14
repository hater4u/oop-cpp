#include "ReplaceBlock.h"
#include "BlockMaker.h"

static BlockMaker<ReplaceBlock> replaceMaker("replace");

std::string ReplaceBlock::operation(std::vector<std::string> data)
{
	std::string word1 = data[0], word2 = data[1];
	std::string tmp = data[2];
	int pos;
	while (tmp.find(word1) != -1)
	{
		pos = tmp.find(word1);
		tmp.erase(pos, word1.size());
		tmp.insert(pos, word2);
	}
	return tmp;
}
