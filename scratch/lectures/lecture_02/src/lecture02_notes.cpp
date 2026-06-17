#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Lecture 2 is kept in one file on purpose so each chapter can be reviewed
// without jumping around. The helper functions below stay internal to this file.

// Section 1: declarations, definitions, and basic entities.
// `sayHello` is a definition, while a declaration would only promise it exists.
void sayHello() {
    std::cout << "Hello!\n";
}

// A complete type: the compiler knows the full layout here.
struct MyType {
    int id;
};

// Section 3.1: scoped enumeration with switch.
// enum class is preferred over raw ints because it keeps the values typed.
enum class RGB {
    Red,
    Green,
    Blue
};

// This switch is intentionally small so the lecture can focus on the syntax.
void PrintColor(RGB color) {
    switch (color) {
        case RGB::Red:
            std::cout << "It's Red\n";
            break;
        case RGB::Green:
            std::cout << "It's Green\n";
            break;
        case RGB::Blue:
            std::cout << "It's Blue\n";
            break;
    }
}

// Section 5: stringstream parsing helper.
// This mirrors the lecture's "string -> typed pieces" parsing example.
struct FileParts {
    int number;
    std::string extension;
};

// Parse "00205.txt" into an integer and a file extension.
FileParts ParseFileName(const std::string& file_name) {
    std::stringstream ss(file_name);
    FileParts result{};
    char dot = '\0';
    ss >> result.number >> dot >> result.extension;
    return result;
}

}  // namespace

int main() {
    std::cout << std::unitbuf;
    std::cout << "=== Lecture 2: Core C++ Notes ===\n";

    // 1) Declarations vs definitions.
    // The key idea is that a declaration introduces a name, while a definition
    // gives the compiler the full thing.
    std::cout << "[lecture 2] declarations vs definitions\n";
    std::cout << "A declaration introduces a name; a definition gives it full meaning.\n";
    std::cout << "This demo keeps the concepts in one place and exposes them through the header.\n";

    // 2) Scope and lifetime.
    // A block `{ ... }` creates a new scope. Variables inside it disappear when
    // execution leaves the block.
    std::cout << "[lecture 2] scope and lifetime\n";
    int outer_var = 100;
    std::cout << "outer before inner block: " << outer_var << '\n';
    {
        int inner_var = 42;
        std::cout << "inner_var inside block: " << inner_var << '\n';
        std::cout << "outer_var still visible: " << outer_var << '\n';
        int outer_var = 5;
        std::cout << "shadowed outer_var inside block: " << outer_var << '\n';
    }
    std::cout << "outer after inner block: " << outer_var << '\n';

    // 3) Control structures and strong typing.
    // Scoped enums keep the names under `RGB::` and avoid accidental mixing with ints.
    std::cout << "[lecture 2] enum class and loops\n";
    PrintColor(RGB::Red);
    PrintColor(RGB::Green);
    PrintColor(RGB::Blue);

    // Range-based for is the cleanest way to traverse a container when you do not
    // need an index.
    std::vector<std::string> names = {"Alice", "Bob", "Charlie"};
    for (const auto& name : names) {
        std::cout << "name: " << name << '\n';
    }

    // Structured binding lets you unpack the map key/value pair directly.
    std::map<std::string, int> age_dict = {{"Alice", 27}, {"Bob", 30}};
    for (const auto& [name, age] : age_dict) {
        std::cout << "key: " << name << ", value: " << age << '\n';
    }

    // 4) Variables, const, references, and floating-point comparisons.
    // `auto` asks the compiler to infer the type from the initializer.
    std::cout << "[lecture 2] auto, const, references, floating-point compare\n";
    auto small_int = 42;
    auto precise_num = 0.01f;
    std::cout << "auto small_int: " << small_int << '\n';
    std::cout << "auto precise_num: " << precise_num << '\n';

    // Floating-point equality is fragile, so compare a small difference instead.
    double a = 0.1 + 0.2;
    double b = 0.3;
    std::cout << "direct equality check: " << std::boolalpha << (a == b) << '\n';
    std::cout << "epsilon check: " << std::boolalpha << (std::abs(a - b) < 1e-9) << '\n';

    // A reference is another name for the same object.
    int original_score = 90;
    int& ref_to_score = original_score;
    ref_to_score = 95;
    std::cout << "original_score after ref update: " << original_score << '\n';

    // `const` means this value should not be modified after initialization.
    const int kMaxPoints = 100;
    std::cout << "const value: " << kMaxPoints << '\n';

    // 5) stringstream as a practical parsing helper.
    // The stream extraction operators parse typed values from a string.
    std::cout << "[lecture 2] stringstream parsing\n";
    const std::string file_name = "00205.txt";
    const FileParts parts = ParseFileName(file_name);
    std::cout << "file_name: " << file_name << '\n';
    std::cout << "number: " << parts.number << '\n';
    std::cout << "extension: " << parts.extension << '\n';

    // Small closing helpers to keep the chapter feeling like a complete pass.
    // These lines are just a tiny closing example of a function call and a struct.
    sayHello();
    MyType type{7};
    std::cout << "MyType.id: " << type.id << '\n';
    return 0;
}
