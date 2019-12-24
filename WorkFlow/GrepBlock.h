#pragma once
#include "IBlock.h"

class GrepBlock : public Common::IBlock
{
public:
	GrepBlock() = default;

	std::string operation(const std::string& text, const std::vector<std::string>& data) override;
};

