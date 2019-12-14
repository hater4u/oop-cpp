#pragma once
#include "IBlock.h"

class ReadBlock : public Common::IBlock
{
public:
	ReadBlock() = default;

	std::string operation(std::vector<std::string> data) override;
};

