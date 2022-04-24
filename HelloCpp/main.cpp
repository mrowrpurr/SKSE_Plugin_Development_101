#include <format>
#include <iostream>

// Use an included library (from vcpkg)
#include <SimpleIni.h>

int main(int, char* []) {
    std::cout << "Hello, C++!\n";

    // Use library for reading .ini files
    // as an example of using a library from vcpkg
    CSimpleIni ini;
    auto error = ini.LoadFile("../../../sample.ini");
    if (error == SI_OK) {
        auto value = ini.GetDoubleValue("Some Section", "fSomeValue");
        std::cout << std::format("Sample .ini value: {}\n", value);
    }
}
