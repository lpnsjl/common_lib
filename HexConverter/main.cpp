#include "HexConverter.h"

int main()
{
	std::cout << std::endl << "convert between int32_t and hex" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << hex_to_int("03e8") << std::endl;  // 03e8 ==> 1000
	std::cout << hex_to_int("ffffffff") << std::endl;  // ffffffff ==> -1
	std::cout << int_to_hex(1000) << std::endl;  // 1000 ==> 03e8
	std::cout << int_to_hex(-1) << std::endl;  // -1 ==> ffffffff

	std::cout << std::endl << "convert between uint32_t and hex" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << hex_to_uint32("ffffffff") << std::endl;  // ffffffff ==> 4294967295
	std::cout << hex_to_uint32("3e8") << std::endl;  // 3e8 ==> 1000
	std::cout << uint32_to_hex(4294967295) << std::endl;  // 4294967295 ==> ffffffff
	std::cout << uint32_to_hex(1000) << std::endl; // 1000 ==> 3e8

	std::cout << std::endl << "convert between int64_t and hex" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << hex_to_int64("ffffffffffffffff") << std::endl;  // ffffffffffffffff ==> -1
	std::cout << hex_to_int64("09fffffff6") << std::endl;  // 09fffffff6 ==> 42949672950
	std::cout << int64_to_hex(-1) << std::endl;  // -1 ==> ffffffffffffffff
	std::cout << int64_to_hex(42949672950) << std::endl;  // 42949672950 ==> 09fffffff6

	std::cout << std::endl << "convert between uint64_t and hex" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << hex_to_uint64("ffffffffffffffff") << std::endl;  // ffffffffffffffff ==> 18446744073709551615
	std::cout << hex_to_uint64("3e8") << std::endl;  // 3e8 ==> 1000
	std::cout << uint64_to_hex(18446744073709551615) << std::endl;  // 18446744073709551615 ==> ffffffffffffffff
	std::cout << uint64_to_hex(1000) << std::endl;  // 1000 ==> 3e8

	std::cout << std::endl << "convert between float and hex" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << hex_to_float("3f8ccccd") << std::endl;  // 3f8ccccd ==> 1.1
	std::cout << hex_to_float("461c4000") << std::endl;  // 461c4000 ==> 10000
	std::cout << float_to_hex(1.1) << std::endl;  // 1.1 ==> 3f8ccccd
	std::cout << float_to_hex(10000) << std::endl;  // 10000 ==> 461c4000

	std::cout << std::endl << "convert between double and hex" << std::endl;
	std::cout << "=================================" << std::endl;
	double d = 10000;
	std::cout << hex_to_double("3ff199999999999a") << std::endl;  // 3ff199999999999a ==> 1.1
	std::cout << hex_to_double("40c3880000000000") << std::endl;  // 40c3880000000000 ==> 10000
	std::cout << double_to_hex(1.1) << std::endl;  // 1.1 ==> 3ff199999999999a
	std::cout << double_to_hex(10000) << std::endl;  // 10000 ==> 40c3880000000000

	std::cout << std::endl << "convert between string and hex" << std::endl;
	std::string src = "aabbccdd";  // 不可用0xaabbccdd, 否则转换结果不正确
	char* dst = new char[src.size()];
	bool ret = str_to_hex(src, dst, 4);  // dst内存视图: aa bb cc dd
	delete[] dst;

	unsigned char src1[4] = {0xaa, 0xbb, 0xcc, 0xdd};
	std::string s = hex_to_str((char*)src1, 4);  // s = "aabbccdd"
	std::cout << s << std::endl;

	return 0;
}
