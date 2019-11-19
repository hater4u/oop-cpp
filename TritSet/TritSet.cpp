#include "TritSet.h"

size_t trits_per_element = (sizeof(unsigned int) * 8 / 2);

unsigned int fill_value_Unknown()
{
	unsigned int res = 0;
	for (size_t it = 0; it < trits_per_element; it++)
	{
		res |= 1 << (it * 2);
	}
	return res;
}

void TritSet::update_last()
{
	last = -1;
	for (size_t it = 0; it < size_in_trits; it++)
	{
		if ((*this)[it] != Trit::Unknown) last = it;
	}
}

Trit TritSet::get(const size_t& position) const
{
	Trit result;
	if (position > size_in_trits - 1) return Trit::Unknown;
	auto shift = (trits_per_element - position - 1) * 2;
	auto selected_uint = tritset[position / trits_per_element];
	unsigned int mask = (((0x0000 | 3) << shift) & selected_uint) >> shift;

	switch (mask)
	{
	case 0:
		result = Trit::False;
		break;
	case 1:
		result = Trit::Unknown;
		break;
	case 3:
		result = Trit::True;
		break;
	}
	return result;
}

TritSet::TritSet(const unsigned int size, const Trit fill_value)
{
	this->size_in_trits = size;
	last = size - 1;
	size_t size_need = size / trits_per_element + ((size % trits_per_element) ? 1 : 0);

	switch (fill_value) 
	{
	case Trit::False: 
		tritset.resize(size_need, 0);
		break;
	case Trit::Unknown:
		tritset.resize(size_need, fill_value_Unknown());
		last = -1;
		break;
	case Trit::True:
		tritset.resize(size_need, UINT_MAX);
		break;
	}
}

TritSet::reference& TritSet::reference::operator=(const reference& other)
{
	set_value(other.set->get(other.position));
	return (*this);
}

TritSet::reference& TritSet::reference::operator=(Trit other)
{
	set_value(other);
	return (*this);
}

void TritSet::reference::set_value(const Trit& value)
{
	if (position > set->size_in_trits - 1)
	{
		if (value == Trit::Unknown) return;
		set->extend(position);
		set->last = position;
	}
	size_t mask = 0x0000;
	size_t selected_uint = position / trits_per_element;
	size_t shift = (trits_per_element - position - 1) * 2;
	switch (value)
	{
	case Trit::False:
		mask = (mask | 3) << shift;
		set->tritset[selected_uint] &= ~mask;
		break;
	case Trit::Unknown:
		mask = (mask | 1) << (shift + 1);
		set->tritset[selected_uint] &= ~mask;
		mask = 0;
		mask = (mask | 1) << shift;
		set->tritset[selected_uint] |= mask;
		break;
	case Trit::True:
		mask = (mask | 3) << shift;
		set->tritset[selected_uint] |= mask;
		break;
	}
	return;
}

TritSet::reference::operator Trit() const
{
	return set->get(position);
}

bool TritSet::operator==(const TritSet& other) const
{
	for (size_t it = 0; it < this->tritset.size(); it++)
	{
		if (this->tritset[it] != other.tritset[it]) return false;
	}
	return true;
}

TritSet& TritSet::operator&=(const TritSet& other)
{
	size_t max;
	if (size_in_trits >= other.size_in_trits)
	{
		max = this->size_in_trits;
	}
	else
	{
		max = other.size_in_trits;
		extend(max - 1);
	}
	Trit tmp1, tmp2;

	for (size_t it = 0; it < max; it++)
	{
		tmp1 = this->get(it);
		tmp2 = other.get(it);
		(*this)[it] = tmp1 & tmp2;
	}
	return (*this);
}

TritSet& TritSet::operator|=(const TritSet& other)
{
	size_t max;
	if (size_in_trits >= other.size_in_trits)
	{
		max = this->size_in_trits;
	}
	else
	{
		max = other.size_in_trits;
		extend(max - 1);
	}
	Trit tmp1, tmp2;
	for (size_t it = 0; it < max; it++)
	{
		tmp1 = this->get(it);
		tmp2 = other.get(it);
		(*this)[it] = tmp1 | tmp2;
	}
	return (*this);
}

TritSet operator~(const TritSet& arg)
{
	TritSet tmp(arg);
	for (size_t it = 0; it < arg.size(); it++)
	{
		switch (arg[it])
		{
		case Trit::True:
			tmp[it] = Trit::False;
			break;
		case Trit::False:
			tmp[it] = Trit::True;
			break;
		case Trit::Unknown:
			tmp[it] = Trit::Unknown;
			break;
		}
	}
	return tmp;
}

TritSet operator&(const TritSet& arg1, const TritSet& arg2)
{
	TritSet tmp(arg1);
	tmp &= arg2;
	return tmp;
}

TritSet operator|(const TritSet& arg1, const TritSet& arg2)
{
	TritSet tmp(arg1);
	tmp |= arg2;
	return tmp;
}

TritSet::reference::reference(TritSet* _set, size_t _position)
	: set(_set), position(_position) {}

Trit TritSet::operator[](const size_t position) const
{
	return TritSet::get(position);
}

TritSet::reference TritSet::operator[] (const size_t position)
{
	return TritSet::reference(this, position);
}

void TritSet::extend(const size_t position) {
	size_t size_need = position / trits_per_element + 1;
	tritset.resize(size_need, fill_value_Unknown());
	size_in_trits = position + 1;
}

void TritSet::shrink() 
{
	update_last();
	if (last >= 0)
	{
		size_t size_need = last / trits_per_element + 1;
		tritset.resize(size_need);
		size_in_trits = last + 1;
		return;
	}
	tritset.resize(0);
	size_in_trits = last + 1;
}

void TritSet::trim(size_t lastIndex)
{
	size_t size_need = lastIndex / trits_per_element + 1;
	tritset.resize(size_need);
	size_in_trits = lastIndex + 1;
	update_last();
}

size_t TritSet::capacity() const
{
	return tritset.size() * trits_per_element;
}

size_t TritSet::cardinality(Trit value)
{
	update_last();
	size_t count = 0;
	for (size_t it = 0; it < last + 1; it++)
	{
		if ((*this)[it] == value) count++;
	}
	return count;
}

std::unordered_map<Trit, int> TritSet::cardinality() const//work??
{
	std::unordered_map<Trit, int> mymap;
	for (size_t it = 0; it < size_in_trits; it++) 
	{
		mymap[get(it)]++;
	}
	return mymap;
}

size_t TritSet::length()
{
	update_last();
	return last + 1;
}

size_t TritSet::size() const
{
	return size_in_trits;
}

std::string TritSet::to_string() const
{
	std::string str;
	str.resize(capacity());
	for (size_t it = 0; it < capacity(); it++)
	{
		switch ((*this)[it]) {
		case Trit::False:
			str[it] = '0';
			break;
		case Trit::True:
			str[it] = '1';
			break;
		case Trit::Unknown:
			str[it] = '?';
			break;
		}
	}
	return str;
}

void TritSet::print_tritset() const
{
	for (size_t it = 0; it < capacity(); it++)
	{
		switch ((*this)[it]) {
		case Trit::False:
			std::cout << '0';
			break;
		case Trit::True:
			std::cout << '1';
			break;
		case Trit::Unknown:
			std::cout << '?';
			break;
		}
		
	}
	std::cout << std::endl;
}

//Потритовые операторы
Trit operator&(Trit arg1, Trit arg2)
{
	Trit tmp = arg1;
	if ((arg1 == Trit::False) || (arg2 == Trit::False))
	{
		tmp = Trit::False;
	}
	else if ((arg1 == Trit::Unknown) || (arg2 == Trit::Unknown))
	{
		tmp = Trit::Unknown;
	}
	else tmp = Trit::True;
	return tmp;
}

Trit operator|(Trit arg1, Trit arg2)
{
	Trit tmp = arg1;
	if ((arg1 == Trit::True) || (arg2 == Trit::True))
	{
		tmp = Trit::True;
	}
	else if ((arg1 == Trit::Unknown) || (arg2 == Trit::Unknown))
	{
		tmp = Trit::Unknown;
	}
	else tmp = Trit::False;
	return tmp;
}

Trit operator~(Trit arg1)
{
	switch (arg1)
	{
	case Trit::False:
		return Trit::True;
	case Trit::Unknown:
		return Trit::Unknown;
	case Trit::True:
		return Trit::False;
	}
}