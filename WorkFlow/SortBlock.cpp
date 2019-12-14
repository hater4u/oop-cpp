#include "SortBlock.h"
#include "BlockMaker.h"
#include <algorithm>

static BlockMaker<SortBlock> sortMaker("sort");

std::string SortBlock::operation(std::vector<std::string> data)
{
	std::string resultStr, tmp = "";
	std::vector<std::string> vec;
	for (size_t it = 0; it != data[0].size(); ++it)
	{
		if (data[0][it] == '\n')
		{
			vec.push_back(tmp);
			tmp.clear();
		}
		else tmp += data[0][it];
	}
	sort(vec.begin(), vec.end());

	for (auto it = 0; it != vec.size(); ++ it)
	{
		resultStr += vec[it] + "\n";
	}

	return resultStr;
}
