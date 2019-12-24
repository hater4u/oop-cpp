#include "ReplaceBlock.h"
#include "BlockMaker.h"

static BlockMaker<ReplaceBlock> replaceMaker("replace");

std::string ReplaceBlock::operation(const std::string &text, const std::vector<std::string> &data)
{
	if (text.empty() || data.empty() || data.size() > 2)
	{
		throw new std::exception("EXCEPTION: invalid arguments for replace");
	}
	std::string word1 = data[0], word2 = data[1];
	std::string tmp = text;
	int pos;
	while (tmp.find(word1) != -1)
	{
		pos = tmp.find(word1);
		tmp.erase(pos, word1.size());
		tmp.insert(pos, word2);
	}
	return tmp;
}
