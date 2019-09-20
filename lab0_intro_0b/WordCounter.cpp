#include "WordCounter.h"

bool Compare(const std::pair<std::string, int> &A, const std::pair<std::string, int> &B)
{
	return A.second > B.second;
}

void WordCounter::InputWordCounter(const std::string &inputf)
{
	std::string line;
	std::string word;
	std::ifstream in(inputf);
	AllCount = 0;

	while (std::getline(in, line))
	{
		for (auto i = 0; i < line.size(); i++)
		{
			if (isalnum(line[i])) 
			{
				word += line[i];
			}
			else if (!word.empty())
			{
				MyMap[word]++;
				AllCount++;
				word.clear();
			}
		}
		if (!word.empty())
		{
			MyMap[word]++;
			AllCount++;
			word.clear();
		}
	}
	
	for (auto it = MyMap.begin(); it != MyMap.end(); ++it)
	{
		MyVector.push_back(std::make_pair(it->first, it->second));
	}
	std::sort(MyVector.begin(), MyVector.end(), Compare);

	in.close();
}

void WordCounter::OutputWordCounter(const std::string &outputf)
{
	std::ofstream out;
	out.open(outputf);
	
	for (auto it = MyVector.begin(); it != MyVector.end(); ++it)
	{
		out << it->first << "," << it->second << "," << ((double)it->second / AllCount) * 100 << "%" << std::endl;
	}

	out.close();
}
