#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>



enum class Trit
{
	False = 0, // 0 и 1 можно было не переприсваивать
	Unknown = 1,
	True = 3
};

class TritSet
{
private:
	std::vector<unsigned int> tritset;
	size_t size_in_trits;

	int last;
	void update_last();

	Trit get(const size_t& position) const;
public:

	TritSet(const unsigned int size = 0, const Trit fill_value = Trit::Unknown);

	// CLASS reference
	class reference  // proxy for an element
	{
		friend TritSet;
	private:
		void set_value(const Trit& value);

		TritSet* set;
		size_t position;

		reference(TritSet* _set, size_t _position);
	public:

		~reference() noexcept {}

		reference& operator=(const reference& other);

		reference& operator=(Trit other);

		operator Trit() const;

	};

	bool operator==(const TritSet& other) const;

	TritSet& operator&=(const TritSet& other);

	TritSet& operator|=(const TritSet& other);

	reference operator[] (const size_t position);

	Trit operator[] (const size_t position) const;

	void extend(const size_t new_size);

	void shrink();

	void trim(size_t lastIndex);

	size_t capacity() const;

	size_t cardinality(Trit value);

	std::unordered_map< Trit, int > cardinality() const;

	size_t length();

	size_t size() const;

	std::string to_string() const;

	void print_tritset() const;
};


TritSet operator~(const TritSet& arg);

TritSet operator&(const TritSet& arg1, const TritSet& arg2);

TritSet operator|(const TritSet& arg1, const TritSet& arg2);

Trit operator&(Trit arg1, Trit arg2);

Trit operator|(Trit arg1, Trit arg2);

Trit operator~(Trit arg1);