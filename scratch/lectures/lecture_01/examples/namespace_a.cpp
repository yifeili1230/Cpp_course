#include <iostream>

namespace {

void MakeItSunny() {
    std::cout << "namespace_a.cpp internal MakeItSunny()\n";
}

}  // namespace

namespace demo_a {

void Run() {
    MakeItSunny();
}

void MakeItSunny() {
    std::cout << "demo_a::MakeItSunny()\n";
}

}  // namespace demo_a
