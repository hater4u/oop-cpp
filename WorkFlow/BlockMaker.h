#pragma once
#include "IBlockMaker.h"
#include "BlockFactory.h"

	template <typename T>

	class BlockMaker : public IBlockMaker {
	public:
		BlockMaker(std::string key) {
			Common::BlockFactory::Instance().registerBlock(key, this);
		}

		virtual Common::IBlock* create() const {
			return new T();
		}
	};
