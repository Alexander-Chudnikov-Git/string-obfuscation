#include "string/string_lib.hpp"
#include <iostream>
#include <bitset>

std::string debug_echo(const char* initial_string, std::size_t length)
{
	std::string buffer = "";
	for(std::size_t index = 0; index < length; ++index)
	{
		buffer += std::bitset<8>(initial_string[index]).to_string();
		buffer += " ";
	}
	return buffer;
}

int main()
{
	auto key = ObfuscatedString::cgi_r<char, 64>();
	std::cout << debug_echo(key, 64) << " - " << std::string(key) << std::endl;
	std::cout << __CGUI_OBF__("Some long string, that should be encrypted") << std::endl;
	std::cout << __CGUI_OBF_S__("Some long string, that should be encrypted") << std::endl;
	std::cout << debug_echo(ObfuscatedString::string_encrypt("Some long string, that should be encrypted", 24, key, 64), 24) << " - " << ObfuscatedString::string_encrypt("Some long string, that should be encrypted", 24, key, 64) << " - " << ObfuscatedString::string_decrypt(ObfuscatedString::string_encrypt("Some long string, that should be encrypted", 24, key, 64), 24, key, 64) << std::endl;
	return 0;
}