#pragma once
#include <vector>

enum Trit
{
	False = 0, // 0 и 1 можно было не переприсваивать
	Unknown = 1,
	True = 3
};

class TritSet
{
private:
	std::vector<unsigned int> tritset;
	unsigned int size_in_trits;

	//TritSet& set(const unsigned int& position, const Trit& value);

	Trit get(const size_t& position) const;
public:

	TritSet(const unsigned int size = 0, const Trit fill_value = Unknown);

	TritSet(const TritSet& other);

	//~TritSet();

	// CLASS reference
	class reference  // proxy for an element
	{
	private:
		void set_value(const Trit& value);

		TritSet* set;
		size_t position;
	public:
		reference(TritSet* _set, size_t _position);

		~reference() noexcept { // TRANSITION, ABI
		}

		reference& operator=(const reference& other);

		reference& operator=(Trit other);

		operator Trit();

	};

	bool operator==(const TritSet& other);

	TritSet& operator&=(const TritSet& other);

	TritSet& operator|=(const TritSet& other);

	TritSet& operator~();

	reference operator[] (const size_t position);

	Trit operator[] (const size_t position) const;

	void extend(const size_t new_size);
};
