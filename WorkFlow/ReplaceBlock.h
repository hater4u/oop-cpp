#pragma once
#include "IBlock.h"

class ReplaceBlock : public Common::IBlock
{
public:
	ReplaceBlock() = default;

	std::string operation(std::vector<std::string> data) override;
};

