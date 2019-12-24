#include "GrepBlock.h"
#include "BlockMaker.h"

static BlockMaker<GrepBlock> grepMaker("grep");

std::string GrepBlock::operation(const std::string& text, const std::vector<std::string>& data)
{
	if (data.empty() || data.size() > 1 || text.empty())
	{
		throw new std::exception("EXCEPTION: invalid arguments for dump");
	}
	std::string word = data[0];
	std::string tmp = "", resultStr = "";
	for (size_t it = 0; it != text.size(); ++it)
	{
		if (text[it] == '\n')
		{
			if (tmp.find(word) != -1)
			{
				tmp += "\n";
				resultStr += tmp;
			}
			tmp.clear();
		}
		else tmp += text[it];
	}

	return resultStr;
}
