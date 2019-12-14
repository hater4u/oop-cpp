#pragma once

#include "WorkFlow.h"
namespace Common
{
	class Parser {
	public:
		void parse(std::string fileName);

		std::unordered_map <size_t, std::vector<std::string>> getData() const;

		std::vector<size_t> getSequence() const;

		std::vector<size_t> getKeys() const;

	private:
		std::unordered_map <size_t, std::vector<std::string>> _parsedData;
		std::vector<size_t> _sequence;
		std::ifstream _fin;
		std::vector<size_t> _keys;

		std::vector<std::string> _split(const std::string& s, char delim);

		void _wrongIdException(std::string& id, size_t number_of_line);

		size_t _stringToInt(std::string& s, size_t number_of_line);
	};
}
