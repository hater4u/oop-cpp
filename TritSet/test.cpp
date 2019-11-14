#include "pch.h"
#include "../tritset/TritSet.cpp"

TEST(tritset_test_construct, constructors) 
{
	TritSet set1(10, True);
	ASSERT_EQ("1111111111??????", set1.to_string());
	TritSet set2(10, False);
	ASSERT_EQ("0000000000??????", set2.to_string());
	TritSet set3(10, Unknown);
	ASSERT_EQ("????????????????", set3.to_string());
	TritSet set4(0, Unknown);
	ASSERT_EQ("", set4.to_string());
	TritSet set5(0, True);
	ASSERT_EQ("", set5.to_string());
}

TEST(tritset_test_operators, operator_square_brackets) // fix assert(set[1], set[4])
{
	TritSet set(5, True);
	Trit tmp = set[2];
	ASSERT_EQ(True, tmp);
	set[2] = False;
	tmp = set[2];
	ASSERT_EQ(False, tmp);
	tmp = set[-1];
	ASSERT_EQ(Unknown, tmp);
	ASSERT_TRUE(set[1] == set[4]);
}

TEST(tritset_test_operators, operator_AND)
{
	TritSet A(5, True);
	TritSet B(10, False);
	A[0] = Unknown;
	B[0] = True;
	A[1] = Unknown;
	B[1] = False;
	B[2] = True;
	A[3] = False;
	A[4] = Unknown;
	B[4] = Unknown;
	TritSet C = A & B;
	ASSERT_EQ(C.to_string(), "?010?00000??????");
	ASSERT_EQ(C.length(), 10);
}

TEST(tritset_test_operators, operator_OR)
{
	TritSet A(5, True);
	TritSet B(10, False);
	A[0] = Unknown;
	B[0] = True;
	A[1] = Unknown;
	B[1] = False;
	B[2] = True;
	A[3] = False;
	A[4] = Unknown;
	B[4] = Unknown;
	TritSet C = A | B;
	ASSERT_EQ(C.to_string(), "1?10?11111??????");
	ASSERT_EQ(C.length(), 10);
}

TEST(tritset_test_operators, operator_NOT)
{
	TritSet A(10, True);
	A[0] = Unknown;
	A[1] = False;
	TritSet B = ~A;
	A = ~A;
	ASSERT_EQ("?100000000??????", B.to_string());
	ASSERT_EQ("?100000000??????", A.to_string());
}

TEST(tritset_test_operators, operator_if_eq)
{
	TritSet set(1000, True);
	TritSet cpy(set);
	ASSERT_TRUE(set == cpy);
	set[523] = Unknown;
	cpy[523] = Unknown;
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
	set[1000000000] = Unknown;
	ASSERT_TRUE(allocLength == set.capacity());
}


TEST(tritset_test_from_task, memory_allocation)
{
	TritSet set(1000);
	size_t allocLength = set.capacity();
	// false, but no exception or memory allocation
	if (set[2000000000] == True) {}
	ASSERT_TRUE(allocLength == set.capacity());

	//выделение пам€ти
	set[1000000000] = True;
	ASSERT_TRUE(allocLength < set.capacity());
}

TEST(tritset_test_from_task, no_memory_operations)
{
	TritSet set(1000);
	size_t allocLength;
	set[1000000000] = True;
	//no memory operations
	allocLength = set.capacity();
	set[1000000000] = Unknown;
	set[1000000] = False;
	ASSERT_TRUE(allocLength == set.capacity());
}

TEST(tritset_test_from_task, test_shrink)
{
	TritSet set(1000);
	size_t allocLength;
	set[1000000000] = True;
	allocLength = set.capacity();
	set[1000000000] = Unknown;
	set[1000000] = False;
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
	TritSet set(1000, True);
	set.trim(613);
	ASSERT_TRUE(set[614] == Unknown);
}

TEST(tritset_test_additional_methods, test_cardinality)
{
	TritSet set(100, False);
	set[3] = True;
	set[9] = True;
	set[27] = True;
	ASSERT_EQ(set.cardinality(False), 97);
	ASSERT_EQ(set.cardinality(True), 3);
	ASSERT_EQ(set.cardinality(Unknown), 0);

	TritSet set1(100, Unknown);
	set1[3] = True;
	set1[9] = False;
	set1[27] = True;
	ASSERT_EQ(set1.cardinality(False), 1);
	ASSERT_EQ(set1.cardinality(True), 2);
	ASSERT_EQ(set1.cardinality(Unknown), 25);
}