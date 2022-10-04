cmake_minimum_required(VERSION 3.21.1)									# Minimum required CMake version

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)										# Set c++ standard to 20

set(PROJECT_NAME "string-obfuscation")
project(${PROJECT_NAME})

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-inline -fvisibility=hidden -fsanitize=leak -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-inline -fvisibility=hidden -fsanitize=leak -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-inline -fvisibility=hidden -fsanitize=leak -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    	string(REGEX REPLACE "/W[0-4]" "/W4 /Zi" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  	else()
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Zi")
  	endif()
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-inline -fvisibility=hidden -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
endif()


add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(string)

target_include_directories(${PROJECT_NAME} PUBLIC string/)		# Link include directory 
target_link_directories(${PROJECT_NAME} PUBLIC string/)			# Link directories for libraries
target_link_libraries(${PROJECT_NAME} PUBLIC cgui_string_lib)					# Link libraries to the project
