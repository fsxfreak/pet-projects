#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

#include "passGenChain.hpp"

namespace mgen
{

template <class T>
PassGenChain<T>::PassGenChain(T from, T to)
	: Chain<T>(from, to)
{ }

std::string readFile(std::string dir)
{
	std::ifstream in(dir);
	std::string text((std::istreambuf_iterator<char>(in))
		, std::istreambuf_iterator<char>());
	return text;
}

std::string stripSpecialChars(std::string text, char from, char to)
{
	text.erase(std::remove_if(text.begin(), text.end(),
		[&] (char c) {
			if (c < from || c > to) 
				return true;
			return false;
		}), 
			   text.end()
	);

	return text;
}

struct CharPairHash
{
	inline size_t operator()(const std::pair<char, char> &pair) const
	{
		return ((pair.first << 9 * pair.second << 7) % 67181);
	}
};

template <class T>
void PassGenChain<T>::buildTransitions()
{
	T from = Chain<T>::stateSpace.front().get();
	T to   = Chain<T>::stateSpace.back().get();

	std::string str = stripSpecialChars(readFile("../txts/feed.txt"), from, to);
	const std::vector<char> text(str.begin(), str.end());

	std::unordered_multiset<std::pair<T, T>, CharPairHash> sequenceCounts;
	auto it = text.begin();
	auto itend = text.end();
	for (; it != itend; ++it)
	{
		auto next = std::next(it, 1);
		if (*next < from || *next > to)
			continue;
		sequenceCounts.insert(std::make_pair(*it, *next));
	}

	std::vector<
		std::vector<
			std::pair<T, double> 
				   > 
			   > allTransitions(Chain<T>::stateSpace.size());
	int totalPairs = str.size() - 1;
	for (int i = 0; i < allTransitions.size(); ++i)
	{
		for (int j = 0; j < allTransitions.size(); ++j)
		{
			int count = sequenceCounts.count(
					std::make_pair(static_cast<char>(from + i)
								 , static_cast<char>(from + j)));
			allTransitions[i].push_back(
				std::make_pair(from + j, static_cast<double>(count) / totalPairs));
		}
		Chain<T>::stateSpace[i].setTransitions(allTransitions[i]);
	}
}

template class PassGenChain<char>;

} //::mgen