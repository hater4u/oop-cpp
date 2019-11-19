#include "pch.h"
#include "../tritset/TritSet.cpp"

TEST(tritset_test_construct, constructors) 
{
	TritSet set1(10, Trit::True);
	ASSERT_EQ("1111111111??????", set1.to_string());
	TritSet set2(10, Trit::False);
	ASSERT_EQ("0000000000??????", set2.to_string());
	TritSet set3(10, Trit::Unknown);
	ASSERT_EQ("????????????????", set3.to_string());
	TritSet set4(0, Trit::Unknown);
	ASSERT_EQ("", set4.to_string());
	TritSet set5(0, Trit::True);
	ASSERT_EQ("", set5.to_string());
}

TEST(tritset_test_operators, operator_square_brackets) // fix assert(set[1], set[4])
{
	TritSet set(5, Trit::True);
	Trit tmp = set[2];
	ASSERT_EQ(Trit::True, tmp);
	set[2] = Trit::False;
	tmp = set[2];
	ASSERT_EQ(Trit::False, tmp);
	tmp = set[-1];
	ASSERT_EQ(Trit::Unknown, tmp);
	ASSERT_TRUE(set[1] == set[4]);
}

TEST(tritset_test_operators, operator_AND)
{
	TritSet A(5, Trit::True);
	TritSet B(10, Trit::False);
	A[0] = Trit::Unknown;
	B[0] = Trit::True;
	A[1] = Trit::Unknown;
	B[1] = Trit::False;
	B[2] = Trit::True;
	A[3] = Trit::False;
	A[4] = Trit::Unknown;
	B[4] = Trit::Unknown;
	TritSet C = A & B;
	ASSERT_EQ(C.to_string(), "?010?00000??????");
	ASSERT_EQ(C.length(), 10);
}

TEST(tritset_test_operators, operator_OR)
{
	TritSet A(5, Trit::True);
	TritSet B(10, Trit::False);
	A[0] = Trit::Unknown;
	B[0] = Trit::True;
	A[1] = Trit::Unknown;
	B[1] = Trit::False;
	B[2] = Trit::True;
	A[3] = Trit::False;
	A[4] = Trit::Unknown;
	B[4] = Trit::Unknown;
	TritSet C = A | B;
	ASSERT_EQ(C.to_string(), "1?10?11111??????");
	ASSERT_EQ(C.length(), 10);
}

TEST(tritset_test_operators, operator_NOT)
{
	TritSet A(10, Trit::True);
	A[0] = Trit::Unknown;
	A[1] = Trit::False;
	TritSet B = ~A;
	A = ~A;
	ASSERT_EQ("?100000000??????", B.to_string());
	ASSERT_EQ("?100000000??????", A.to_string());
}

TEST(tritset_test_operators, operator_if_eq)
{
	TritSet set(1000, Trit::True);
	TritSet cpy(set);
	ASSERT_TRUE(set == cpy);
	set[523] = Trit::Unknown;
	cpy[523] = Trit::Unknown;
	ASSERT_TRUE(set == cpy);
	ASSERT_TRUE(set[523] == set[523]);
}

TEST(tritset_test_from_task, create)
{
	//резерв пам€ти дл€ хранени€ 1000 тритов
	TritSet set(1000);
	// length of internal array
	size_t allocLength = set.capacity();
	ASSERT_TRUE(allocLength >= 1000 * 2 / 8 / sizeof(unsigned int));
	// 1000*2 - min bits count
	// 1000*2 / 8 - min bytes count
	// 1000*2 / 8 / sizeof(uint) - min uint[] size
}

TEST(tritset_test_from_task, no_memory_allocation)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	set[1000000000] = Trit::Unknown;
	ASSERT_TRUE(allocLength == set.capacity());
}


TEST(tritset_test_from_task, memory_allocation)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	// Trit::False, but no exception or memory allocation
	if (set[2000000000] == Trit::True) {}
	ASSERT_TRUE(allocLength == set.capacity());

	//выделение пам€ти
	set[1000000000] = Trit::True;
	ASSERT_TRUE(allocLength < set.capacity());
}

TEST(tritset_test_from_task, no_memory_operations)
{
	TritSet set(1000);
	size_t allocLength;
	set[1000000000] = Trit::True;
	//no memory operations
	allocLength = set.capacity();
	set[1000000000] = Trit::Unknown;
	set[1000000] = Trit::False;
	ASSERT_TRUE(allocLength == set.capacity());
}

TEST(tritset_test_from_task, test_shrink)
{
	TritSet set(1000);
	size_t allocLength;
	set[1000000000] = Trit::True;
	allocLength = set.capacity();
	set[1000000000] = Trit::Unknown;
	set[1000000] = Trit::False;
	set.shrink();
	ASSERT_TRUE(allocLength > set.capacity());
}

TEST(tritset_test_from_task, memory_test_operator_AND)
{
	TritSet setA(1000);
	TritSet setB(2000);
	TritSet setC = setA & setB;
	ASSERT_TRUE(setC.capacity() == setB.capacity());
}

TEST(tritset_test_additional_methods, test_trim)
{
	TritSet set(1000, Trit::True);
	set.trim(613);
	ASSERT_TRUE(set[614] == Trit::Unknown);
}

TEST(tritset_test_additional_methods, test_cardinality)
{
	TritSet set(100, Trit::False);
	set[3] = Trit::True;
	set[9] = Trit::True;
	set[27] = Trit::True;
	ASSERT_EQ(set.cardinality(Trit::False), 97);
	ASSERT_EQ(set.cardinality(Trit::True), 3);
	ASSERT_EQ(set.cardinality(Trit::Unknown), 0);

	TritSet set1(100, Trit::Unknown);
	set1[3] = Trit::True;
	set1[9] = Trit::False;
	set1[27] = Trit::True;
	ASSERT_EQ(set1.cardinality(Trit::False), 1);
	ASSERT_EQ(set1.cardinality(Trit::True), 2);
	ASSERT_EQ(set1.cardinality(Trit::Unknown), 25);
}