#include "lecture01/tools.hpp"

#include <any>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

// Lecture 1: build system, compilation, declarations, and linkage.
// This file is meant to be the one-stop review page for the chapter.

int main() {
    // Keep stdout flushed immediately so the chapter output stays in order.
    std::cout << std::unitbuf;
    std::cout << "=== Lecture 1: Build System Notes ===\n";

    // 1) Compilation pipeline recap:
    //    this section shows a few standard-library types and then writes a small
    //    binary file so you can connect "source code" with a real artifact.
    std::cout << "\n[1] Compilation pipeline and standard library features\n";

    // std::variant stores exactly one value from a fixed set of types.
    std::variant<int, float> value = 42;
    std::cout << "variant<int, float>: " << std::get<int>(value) << '\n';

    // std::any stores a value of any copyable type, but you recover it with casts
    std::any dynamic_value{3.15};
    std::cout << "any<double>: " << std::any_cast<double>(dynamic_value) << '\n';
    dynamic_value = true;
    std::cout << "any<bool>: " << std::boolalpha
              << std::any_cast<bool>(dynamic_value) << '\n';

    // std::tuple groups unrelated values into one object.
    using Student = std::tuple<std::string, int, double>;
    Student student{"Alice", 20, 3.8};
    // Structured binding unpacks tuple elements into named variables.
    const auto& [name, age, gpa] = student;
    std::cout << "structured binding: " << name << ", age " << age
              << ", GPA " << gpa << '\n';

    // chrono gives you clock and duration types for measuring time.
    const auto start = std::chrono::steady_clock::now();
    const auto end = std::chrono::steady_clock::now();
    const auto elapsed = end - start;
    std::cout << "chrono ticks: " << elapsed.count() << '\n';

    // Write a small binary blob: this mirrors the lecture's discussion of
    // compile-time output and low-level artifacts.
    const std::string file_name = "example_image.dat";
    std::ofstream file(file_name, std::ios_base::out | std::ios_base::binary);
    const int rows = 2;
    const int cols = 3;
    const std::vector<float> image(static_cast<std::size_t>(rows * cols), 1.0F);

    // reinterpret_cast is used here because we are treating plain data as bytes.
    file.write(reinterpret_cast<const char*>(&rows), sizeof(rows));
    file.write(reinterpret_cast<const char*>(&cols), sizeof(cols));
    file.write(reinterpret_cast<const char*>(image.data()),
               static_cast<std::streamsize>(image.size() * sizeof(float)));
    std::cout << "wrote binary example: " << file_name << '\n';

    // 2) Declarations vs definitions, and the linker story.
    //    The header declares the functions; the compiled .cpp file defines them.
    std::cout << "\n[2] Declaration, definition, and linking\n";
    std::cout << "Header files carry declarations; source files carry definitions.\n";
    std::cout << "The real function bodies come from compiled objects linked together.\n";
    // These calls work because lecture01_tools is linked into this executable.
    lecture01::MakeItRain();
    lecture01::MakeItSunny();

    // 3) Cross-file behavior: namespace and symbol isolation.
    //    The detailed multi-file collision demo lives in examples/namespace_demo.cpp.
    std::cout << "\n[3] Namespace and cross-file symbol hygiene\n";
    std::cout << "Open lectures/lecture_01/examples/namespace_demo.cpp for the multi-file demo.\n";

    return 0;
}
