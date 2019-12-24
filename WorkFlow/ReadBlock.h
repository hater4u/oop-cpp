#pragma once
#include "IBlock.h"

class ReadBlock : public Common::IBlock
{
public:
	ReadBlock() = default;

	std::string operation(const std::string& text, const std::vector<std::string>& data) override;
};

