#include "TritSet.h"

size_t trits_per_element = (sizeof(unsigned int) * 8 / 2);

unsigned int fill_value_Unknown()
{
	unsigned int res = 0;
	for (auto it = 0; it < trits_per_element; it++)
	{
		res |= 1 << (it * 2);
	}
	return res;
}

/*TritSet& TritSet::set(const unsigned int& position, const Trit& value)
{
	if (position > size_in_trits - 1)
	{
		if (value == Unknown) return *this;
		extend(position);
	}
	unsigned int mask = 0x0000;
	auto& selected_uint = tritset[position / trits_per_element];
	short shift = (trits_per_element - position - 1) * 2;
	switch (value)
	{
	case False:
		mask = (mask | 3) << shift;
		selected_uint &= ~mask;
		break;
	case Unknown:
		mask = (mask | 1) << (shift + 1);
		selected_uint &= ~mask;
		mask = 0;
		mask = (mask | 1) << shift;
		selected_uint |= mask;
		break;
	case True:
		mask = (mask | 3) << shift;
		selected_uint |= mask;
		break;
	}
	return *this;
}*/

Trit TritSet::get(const size_t& position) const//Вернуть & после мини тестов
{
	Trit result;
	if (position > size_in_trits - 1) return Unknown;
	auto shift = (trits_per_element - position - 1) * 2;
	auto selected_uint = tritset[position / trits_per_element];
	unsigned int mask = (((0x0000 | 3) << shift) & selected_uint) >> shift;

	switch (mask)
	{
	case 0:
		result = False;
		break;
	case 1:
		result = Unknown;
		break;
	case 3:
		result = True;
		break;
	}
	return result;
}

TritSet::TritSet(const unsigned int size, const Trit fill_value)
{
	this->size_in_trits = size;
	size_t size_need = size / trits_per_element + ((size % trits_per_element) ? 1 : 0);

	switch (fill_value) 
	{
	case False: 
		tritset.resize(size_need, 0);
		break;
	case Unknown:
		tritset.resize(0);
		this->size_in_trits = 0;
		break;
	case True:
		tritset.resize(size_need, UINT_MAX);
		break;
	}
}

TritSet::TritSet(const TritSet& other)
{
	this->tritset = other.tritset;
//	this->tritset.clear;
	this->size_in_trits = other.size_in_trits;
}

TritSet::reference& TritSet::reference::operator=(const reference& other)
{
	set_value(other.set->get(other.position)); //work???
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
		if (value == Unknown) return;
		set->extend(position);
	}
	size_t mask = 0x0000;
	size_t selected_uint = position / trits_per_element;
	short shift = (trits_per_element - position - 1) * 2;
	switch (value)
	{
	case False:
		mask = (mask | 3) << shift;
		set->tritset[selected_uint] &= ~mask;
		break;
	case Unknown:
		mask = (mask | 1) << (shift + 1);
		set->tritset[selected_uint] &= ~mask;
		mask = 0;
		mask = (mask | 1) << shift;
		set->tritset[selected_uint] |= mask;
		break;
	case True:
		mask = (mask | 3) << shift;
		set->tritset[selected_uint] |= mask;
		break;
	}
	return;
}

TritSet::reference::operator Trit()
{
	//set->tritset[position]
	return set->get(position);
}

/*bool TritSet::reference::operator==(const reference& obj)
{

	return false;
}

bool TritSet::reference::operator==(const Trit& value)
{

	return false;
}*/

bool TritSet::operator==(const TritSet& other)
{
	for (size_t it = 0; it < this->tritset.size(); it++)
	{
		if (this->tritset[it] != other.tritset[it]) return false;
	}
	return true;
}

TritSet& TritSet::operator&=(const TritSet& other)
{
	size_t max = size_in_trits > other.size_in_trits ? this->size_in_trits : other.size_in_trits;
	// maybe need resize
	Trit tmp1, tmp2;
	for (size_t it = max; it > 0; it--)
	{
		tmp1 = this->get(it);
		tmp2 = other.get(it);
		if ((tmp1 == False) || (tmp2 == False))
		{
			//this->set(it, False);
			(*this)[it] = False;
		}
		else if ((tmp1 == Unknown) || (tmp2 == Unknown))
		{
			//this->set(it, Unknown);
			(*this)[it] = Unknown;
		}
		else (*this)[it] = True;//this->set(it, True);
	}
	return (*this);
}

TritSet& TritSet::operator|=(const TritSet& other)
{
	size_t max = size_in_trits > other.size_in_trits ? this->size_in_trits : other.size_in_trits;
	// maybe need resize
	Trit tmp1, tmp2;
	for (size_t it = max; it > 0; it--)
	{
		tmp1 = this->get(it);
		tmp2 = other.get(it);
		if ((tmp1 == True) || (tmp2 == True))
		{
			(*this)[it] = True;
		}
		else if ((tmp1 == Unknown) || (tmp2 == Unknown))
		{
			(*this)[it] = Unknown;
		}
		else (*this)[it] = False;
	}
	return (*this);
}

TritSet& TritSet::operator~()
{
	for (size_t it = 0; it < size_in_trits; it++)
	{
		switch (TritSet::get(it))
		{
		case True:
			(*this)[it] = False;
			break;
		case False:
			(*this)[it] = True;
			break;
		case Unknown:
			(*this)[it] = Unknown;
			break;
		}
	}
	return (*this);
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

/*TritSet::~TritSet()
{
	delete[] tritset;
}*/ 

void TritSet::extend(const size_t position) {
	size_t size_need = position / trits_per_element + 1;
	tritset.resize(size_need, fill_value_Unknown());
	size_in_trits = position + 1;
}
