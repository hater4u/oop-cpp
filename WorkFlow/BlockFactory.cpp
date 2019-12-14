#include "BlockFactory.h"
#include <iostream>

using namespace Common;

BlockFactory& BlockFactory::Instance()
{
	static BlockFactory factory;
	return factory;
}

IBlock* Common::BlockFactory::createBlock(std::string blockName)
{
	auto block = _blockMap.find(blockName);
	IBlockMaker* blockMaker = block->second;
	return blockMaker->create();
}

void Common::BlockFactory::registerBlock(std::string newBlockName, IBlockMaker* newBlock)
{
	if (_blockMap.find(newBlockName) != _blockMap.end()) 
	{
		throw new std::exception("error, multiple makers for this block name");
	}
	_blockMap[newBlockName] = newBlock;
}
