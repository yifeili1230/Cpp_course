#include <algorithm>
#include <array>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

// Lecture 4 review page:
// one file, chapter-by-chapter, with the examples ordered like the notes.

namespace {

void PrintSectionHeader(const std::string& title) {
    std::cout << "\n[" << title << "]\n";
}

template <typename Container>
void PrintRange(const Container& container, const std::string& prefix = "") {
    for (const auto& value : container) {
        if (!prefix.empty()) {
            std::cout << prefix;
        }
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

void PrintPairs(const std::map<int, std::string>& students) {
    for (const auto& [id, name] : students) {
        std::cout << id << " -> " << name << '\n';
    }
}

void PrintPairs(const std::unordered_map<int, std::string>& students) {
    for (const auto& [id, name] : students) {
        std::cout << id << " -> " << name << '\n';
    }
}

}  // namespace

int main() {
    std::cout << std::unitbuf;
    std::cout << "=== Lecture 4: Containers, Iterators, Algorithms ===\n";

    // 1) Containers.
    PrintSectionHeader("1. Containers");
    {
        std::cout << "[1.1] std::array\n";
        std::array<int, 3> data = {10, 100, 1000};
        std::cout << "empty: " << std::boolalpha << data.empty() << '\n';
        std::cout << "size: " << data.size() << '\n';
        std::cout << "first element: " << data[0] << '\n';

        std::cout << "[1.2] std::vector\n";
        std::vector<std::string> names;
        names.reserve(100);
        names.emplace_back("Nacho");
        names.emplace_back("Roberto");
        names.emplace_back("Ada");
        std::cout << "size: " << names.size() << " | capacity: " << names.capacity() << '\n';
        std::cout << "back: " << names.back() << '\n';
        names.clear();
        std::cout << "after clear, empty: " << names.empty() << '\n';

        std::cout << "[1.3] Why not C arrays\n";
        int c_array[] = {10, 100, 1000};
        std::cout << "sizeof(c_array) / sizeof(c_array[0]): "
                  << sizeof(c_array) / sizeof(c_array[0]) << '\n';
        std::cout << "STL containers give size(), empty(), back(), and clear() directly.\n";
    }

    // 2) Associative containers.
    PrintSectionHeader("2. Associative Containers");
    {
        std::cout << "[2.1] std::map\n";
        using StudentList = std::map<int, std::string>;
        StudentList cpp_students;
        cpp_students.emplace(10, "Nacho");
        cpp_students.emplace(2, "Marcelo");
        cpp_students.emplace(7, "Clara");
        PrintPairs(cpp_students);

        std::cout << "[2.2] std::unordered_map\n";
        std::unordered_map<int, std::string> fast_students;
        fast_students.emplace(10, "Nacho");
        fast_students.emplace(2, "Marcelo");
        fast_students.emplace(7, "Clara");
        PrintPairs(fast_students);
    }

    // 3) Iterators.
    PrintSectionHeader("3. Iterators");
    {
        std::vector<int> values = {1, 2, 3, 4, 5};

        std::cout << "forward iteration: ";
        for (auto it = values.begin(); it != values.end(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << '\n';

        std::cout << "const iteration: ";
        for (auto it = values.cbegin(); it != values.cend(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << '\n';

        std::cout << "reverse iteration: ";
        for (auto it = values.rbegin(); it != values.rend(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << '\n';
    }

    // 4) Algorithms.
    PrintSectionHeader("4. Algorithms");
    {
        std::vector<int> vec = {9, 4, 1, 3, 6, 3, 2, 8};

        std::cout << "original: ";
        PrintRange(vec);

        std::sort(vec.begin(), vec.end());
        std::cout << "sorted ascending: ";
        PrintRange(vec);

        std::sort(vec.rbegin(), vec.rend());
        std::cout << "sorted descending: ";
        PrintRange(vec);

        auto it = std::find(vec.begin(), vec.end(), 3);
        std::cout << "find 3: " << (it != vec.end() ? "found" : "not found") << '\n';

        std::fill(vec.begin(), vec.end(), -1);
        std::cout << "after fill: ";
        PrintRange(vec);

        vec = {9, 4, 1, 3, 6, 3, 2, 8};
        int num_threes = std::count(vec.begin(), vec.end(), 3);
        int count_divisible_by_three = std::count_if(vec.begin(), vec.end(), [](int i) {
            return i % 3 == 0;
        });
        std::cout << "count 3: " << num_threes << '\n';
        std::cout << "count divisible by 3: " << count_divisible_by_three << '\n';

        std::cout << "for_each: ";
        std::for_each(vec.begin(), vec.end(), [](int i) { std::cout << i << ' '; });
        std::cout << '\n';

        bool all_even = std::all_of(vec.begin(), vec.end(), [](int i) { return i % 2 == 0; });
        std::cout << "all even: " << std::boolalpha << all_even << '\n';

        std::rotate(vec.begin(), vec.begin() + 2, vec.end());
        std::cout << "after rotate: ";
        PrintRange(vec);

        std::string s = "hello";
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char ch) {
            return static_cast<char>(std::toupper(ch));
        });
        std::cout << "transform to upper: " << s << '\n';

        int sum = std::accumulate(vec.begin(), vec.end(), 0);
        int prod = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
        std::cout << "accumulate sum: " << sum << '\n';
        std::cout << "accumulate product: " << prod << '\n';

        std::cout << "clamp(0.5): " << std::clamp(0.5, 0.0, 1.0) << '\n';
        std::cout << "clamp(2.1): " << std::clamp(2.1, 0.0, 1.0) << '\n';
        std::cout << "clamp(-2.1): " << std::clamp(-2.1, 0.0, 1.0) << '\n';

        std::string in = "C++++School";
        std::string out;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::sample(in.begin(), in.end(), std::back_inserter(out), 5, gen);
        std::cout << "sampled string: " << out << '\n';
    }

    return 0;
}
