#include <iostream>

namespace demo_a {
void Run();
void MakeItSunny();
}  // namespace demo_a

namespace demo_b {
void Run();
void MakeItSunny();
}  // namespace demo_b

int main() {
    std::cout << "Anonymous namespaces keep same-named helper functions private:\n";
    demo_a::Run();
    demo_b::Run();

    std::cout << "\nNamed namespaces make public symbols distinct:\n";
    demo_a::MakeItSunny();
    demo_b::MakeItSunny();
    return 0;
}
