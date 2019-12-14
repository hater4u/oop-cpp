#include "WorkFlow.h"
#include "Parser.h"
#include "BlockFactory.h"
#include <algorithm>

using namespace Common;

void WorkFlow::start(std::string fileName)
{
	Parser parser;
	std::string result = "";
	std::unordered_map<size_t, std::vector<std::string>> parsedData;
	std::vector<size_t> parsedSequence;
	BlockFactory blockfactory = BlockFactory::Instance();
	std::vector<size_t> keys;

	parser.parse(fileName);
	parsedData = parser.getData();
	parsedSequence = parser.getSequence();
	keys = parser.getKeys();
	sort(keys.begin(), keys.end());

	for (size_t it = 0; it != parsedSequence.size(); ++it)
	{
		for (size_t j = 0; j != keys.size(); ++j)
		{
			if (parsedSequence[it] == keys[j])
			{
				IBlock* command = blockfactory.createBlock(parsedData[keys[j]][0]);
				parsedData[keys[j]].push_back(result);
				result = command->operation(std::vector<std::string>(parsedData[keys[j]].begin() + 1, parsedData[keys[j]].end()));
				delete command;
				break;
			}
		}

	}
}
