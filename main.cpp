#include "string/string_lib.hpp"
#include <iostream>

int main()
{
	std::cout << __CGUI_OBF__("Some long string, that should be encrypted") << std::endl;
	std::cout << __CGUI_OBF__("Some long string, that should be encrypted") << std::endl;
	std::cout << __CGUI_OBF__("Some long string, that should be encrypted") << std::endl;
	std::cout << __CGUI_OBF__("Some long string, that should be encrypted") << std::endl;
	
	std::cout << __CGUI_OBF_S__("Some long string, that should be encrypted") << std::endl;
	std::cout << __CGUI_OBF_S__("Some long string, that should be encrypted") << std::endl;
	std::cout << __CGUI_OBF_S__("Some long string, that should be encrypted") << std::endl;
	std::cout << __CGUI_OBF_S__("Some long string, that should be encrypted") << std::endl;
	
	return 0;
}
