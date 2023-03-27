#include <UnitTest++/UnitTest++.h>
#include <../LFSR/LFSR_Galois.cpp>
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;
struct LFSR_fixture {
	LFSR_Galois * p;
	LFSR_fixture()
	{
		p = new LFSR_Galois();

	}
	~LFSR_fixture()
	{
		delete p;
	}
};
SUITE(RevesreTest)
{
	TEST(ValidKey_1) {
		CHECK_EQUAL(0x0000000000000001, LFSR_Galois().reverse_bits(0x8000000000000000));
	}
	TEST(ValidKey_2) {
		CHECK_EQUAL(0x367ba866dd1438b8, LFSR_Galois().reverse_bits(0x1d1c28bb6615de6c));
	}
	TEST(ZeroKey) {
		CHECK_THROW(LFSR_Galois().reverse_bits(0x0000000000000000), GaloisError);
	}
}
SUITE(SetBitsTest)
{
	TEST_FIXTURE(LFSR_fixture, NonZeroStartBits) {
		p->set_start_bits(0x0000000000000001);
		CHECK_EQUAL(p->get_start_bits(),0x0000000000000001);
	}
	TEST_FIXTURE(LFSR_fixture, ZeroStartBits) {
		CHECK_THROW(p->set_start_bits(0x0000000000000000),GaloisError);
	}
}
SUITE(GenerateTest)
{
	
	TEST_FIXTURE(LFSR_fixture, GenBits_1) {
		p->set_start_bits(0x0000000000000001);
		CHECK_EQUAL(0x8e38e38e38e38e3a,p->get_respond_bits(false));
	}
	TEST_FIXTURE(LFSR_fixture, GenBits_2) {
		p->set_start_bits(0x010c00a0ea01f001);
		CHECK_EQUAL(0x8e16dace238ea926,p->get_respond_bits(false));
	}
	
}
SUITE(RandomTest)
{
	TEST_FIXTURE(LFSR_fixture, RandBits_1) {
		CHECK(p->get_random_bits() != p->get_random_bits());
	}
}

int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}
