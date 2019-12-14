#pragma once
#include "IBlock.h"

class SortBlock : public Common::IBlock
{
public:
	SortBlock() = default;

	std::string operation(std::vector<std::string> data) override;
};

