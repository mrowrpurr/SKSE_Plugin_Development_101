cmake_minimum_required(VERSION 3.21)

project(HelloCpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# Define your program
# add_executable(${PROJECT_NAME} main.cpp)

find_package(CommonLibSSE CONFIG REQUIRED)

    add_compile_definitions(
        UNICODE
        _UNICODE
        NOMINMAX
        _AMD64_
        WIN32_LEAN_AND_MEAN
        _CRT_USE_BUILTIN_OFFSETOF # Fixes MSVC being non-compliant with offsetof behavior by default.
    )

 add_compile_options(
        /bigobj # support large object file format
        /utf-8  # assume UTF-8 sources even without a BOM

        # warnings -> errors
        /we4715 # 'function' : not all control paths return a value

        # disable warnings
        /wd4005 # macro redefinition, needed for workarounds for CLion
        /wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
        /wd4117 # definition of reserved macro, needed for workarounds for CLion
        /wd4200 # nonstandard extension used : zero-sized array in struct/union
        /wd4201 # nonstandard extension used : nameless struct/union
        /wd4265 # 'type': class has virtual functions, but its non-trivial destructor is not virtual; instances of this class may not be destructed correctly
        /wd4266 # 'function' : no override available for virtual member function from base 'type'; function is hidden
        /wd4371 # 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
        /wd4459 # declaration of 'identifier' hides global declaration
        /wd4514 # 'function' : unreferenced inline function has been removed
        /wd4582 # 'type': constructor is not implicitly called
        /wd4583 # 'type': destructor is not implicitly called
        /wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
        /wd4625 # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
        /wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
        /wd4710 # 'function' : function not inlined
        /wd4711 # function 'function' selected for inline expansion
        /wd4820 # 'bytes' bytes padding added after construct 'member_name'
        /wd5026 # 'type': move constructor was implicitly defined as deleted
        /wd5027 # 'type': move assignment operator was implicitly defined as deleted
        /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
        /wd5053 # support for 'explicit(<expr>)' in C++17 and earlier is a vendor extension
        /wd5204 # 'type-name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
        /wd5220 # 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial
    )

# Add a package from vcpkg (to prove that you setup vcpkg correctly!)
# find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")
# target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES Plugin.cpp PCH.h)

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		PCH.h
)
