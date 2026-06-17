#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

// Lecture 3 review page:
// one file, chapter-by-chapter, matching the note order as closely as possible.

namespace {

// A small helper with file-local visibility.
void PrintSectionHeader(const std::string& title) {
    std::cout << "\n[" << title << "]\n";
}

// Used for the auto-return example.
auto get_dictionary() {
    std::map<std::string, int> dict = {{"apple", 1}, {"banana", 2}};
    return dict;
}

// Used for the structured-binding multi-return example.
std::tuple<std::string, double> get_student_info() {
    return {"Alice", 4.0};
}

// Bad example from the notes: returns a reference to a dead local variable.
// We keep it here as a commented reminder, not as callable code.
/*
int& multiply_by_ten(int number) {
    int result = number * 10;
    return result;
}
*/

int count_calls_impl() {
    static int counter = 0;
    return ++counter;
}

// Inline example from the notes.
inline int square(int x) {
    return x * x;
}

void print_type(int value) {
    std::cout << "This is an integer: " << value << '\n';
}

void print_type(double value) {
    std::cout << "This is a double: " << value << '\n';
}

void print_type(const std::string& value) {
    std::cout << "This is a string: " << value << '\n';
}

const double PI = 3.14159265;

void local_helper() {
    std::cout << "Helper reference.\n";
}

}  // namespace

// A local namespace example for the `using` discussion.
double pow(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return 100.0;
}

int main() {
    std::cout << std::unitbuf;
    std::cout << "=== Lecture 3: Functions, Strings, Namespaces ===\n";

    // 1) C style strings vs C++ strings.
    PrintSectionHeader("1. C Style vs C++ Style Strings");
    {
        // The modern approach: std::string copies safely and manages memory.
        const std::string source = "This is a safe C++ string";
        std::string destination;
        destination = source;
        std::cout << "std::string copy: " << destination << '\n';

        // The C-style warning from the notes.
        const char* c_source = "This is a very long string";
        char destination_buffer[10];
        std::cout << "C-style source example: " << c_source << '\n';
        std::cout << "C-style destination buffer size: " << sizeof(destination_buffer) << '\n';
        std::cout << "Avoid strcpy-style copies that ignore bounds.\n";
    }

    // 2) Function anatomy.
    PrintSectionHeader("2. Function Anatomy");
    {
        auto my_dict = get_dictionary();
        std::cout << "auto return type example: " << my_dict["apple"] << '\n';

        const auto [name, gpa] = get_student_info();
        std::cout << "structured binding return: " << name << ", GPA " << gpa << '\n';
    }

    // 3) Function pitfalls and optimization principles.
    PrintSectionHeader("3. Function Pitfalls and Optimization");
    {
        std::cout << "Returning a reference to a local variable is undefined behavior.\n";
        std::cout << "Static local call count: " << count_calls_impl() << '\n';
        std::cout << "Static local call count: " << count_calls_impl() << '\n';
    }

    // 4) Pass by const reference.
    PrintSectionHeader("4. Pass by Const Reference");
    {
        auto print_image_path_bad = [](std::string path) {
            std::cout << "bad pass-by-value: " << path << '\n';
        };
        auto print_image_path_good = [](const std::string& path) {
            std::cout << "good const-ref: " << path << '\n';
        };

        const std::string huge_path = "usr/local/share/images/dataset/image_001.png";
        print_image_path_bad(huge_path);
        print_image_path_good(huge_path);
    }

    // 5) Inline functions.
    PrintSectionHeader("5. Inline Functions");
    {
        std::cout << "square(5): " << square(5) << '\n';
    }

    // 6) Function overloading.
    PrintSectionHeader("6. Function Overloading");
    {
        print_type(10);
        print_type(3.14);
        print_type(std::string("hi"));
    }

    // 7) Namespaces and `using`.
    PrintSectionHeader("7. Namespaces and using");
    {
        using std::cout;
        using std::endl;

        cout << "local pow(2.0, 3): " << pow(2.0, 3) << endl;
        cout << "std::string demo keeps names explicit." << endl;

        std::cout << "Anonymous namespace constant PI: " << PI << '\n';
        local_helper();
    }

    // C-style string caution from the notes.
    PrintSectionHeader("Extra: CString Caution");
    {
        const char* source = "This is a very long string";
        char destination[10];
        std::cout << "source: " << source << '\n';
        std::cout << "destination buffer size: " << sizeof(destination) << '\n';
        std::cout << "Never copy blindly into a fixed-size buffer.\n";
    }

    return 0;
}
