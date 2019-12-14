#pragma once
#include "IBlock.h"

class DumpBlock : public Common::IBlock
{
public:
	DumpBlock() = default;

	std::string operation(std::vector<std::string> data) override;
};

