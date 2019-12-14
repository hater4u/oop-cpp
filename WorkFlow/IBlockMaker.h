#pragma once
#include "IBlock.h"

	class IBlockMaker
	{
	public:
		virtual Common::IBlock* create() const = 0;

		virtual ~IBlockMaker() = default;
	};
