#pragma once
#include "IBlock.h"

class GrepBlock : public Common::IBlock
{
public:
	GrepBlock() = default;

	std::string operation(std::vector<std::string> data) override;
};

