#include "GrepBlock.h"
#include "BlockMaker.h"

static BlockMaker<GrepBlock> grepMaker("grep");

std::string GrepBlock::operation(std::vector<std::string> data)
{
	std::string word = data[0];
	std::string tmp = "", resultStr = "";
	for (size_t it = 0; it != data[1].size(); ++it)
	{
		if (data[1][it] == '\n')
		{
			if (tmp.find(word) != -1)
			{
				tmp += "\n";
				resultStr += tmp;
			}
			tmp.clear();
		}
		else tmp += data[1][it];
	}

	return resultStr;
}
