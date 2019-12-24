#pragma once
#include <map>
#include "IBlock.h"
#include "DumpBlock.h"
#include "ReadBlock.h"
#include "WriteBlock.h"
#include "GrepBlock.h"
#include "SortBlock.h"
#include "ReplaceBlock.h"
#include "IBlockMaker.h"

namespace Common {

	class BlockFactory
	{
		BlockFactory() = default;
	public:
		BlockFactory(const BlockFactory&) = delete;
		BlockFactory& operator = (const BlockFactory&) = delete;
		static BlockFactory& Instance();

		~BlockFactory() = default;

		IBlock* createBlock(std::string blockName);

		void registerBlock(std::string newBlockName, IBlockMaker* newBlock);
	private:
		std::map<std::string, IBlockMaker*> _blockMap;
	};
}
