#include <iostream>

namespace {

void MakeItSunny() {
    std::cout << "namespace_b.cpp internal MakeItSunny()\n";
}

}  // namespace

namespace demo_b {

void Run() {
    MakeItSunny();
}

void MakeItSunny() {
    std::cout << "demo_b::MakeItSunny()\n";
}

}  // namespace demo_b
