#include <iostream>

#include <sstream>
#include <iomanip> // I/O Manipulators

using std::cerr;
using std::cout;
using std::endl;
using std::cin;
using std::string;


bool is_valid_file(const string& filename, int& number, string& extension);

int main(int argc, char const *argv[]) {


    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    //using stringstream to read the input file
    auto file1 = argv[1];
    auto file2 = argv[2];

    int number1, number2;
    string extension1, extension2;

    if (!is_valid_file(file1, number1, extension1) || !is_valid_file(file2, number2, extension2)) {
        cerr << "Invalid input file name: " << file1 << " or " << file2 << endl;
        return 1;
    }

    if (extension1 == "txt" && extension2 == "txt") {
        cout << (number1 + number2)/2.0 << endl;
        return 0;
    } else if (extension1 == "png" && extension2 == "png") {
        cout << (number1 + number2) << endl;
        return 0;
    } else if (extension1 == "txt" && extension2 == "png") {
        if (number2 == 0) {
            cerr << "[ERROR]: Division by zero!" << endl;
            return 1;
        }
        cout << number1 % number2 << endl;
        return 0;
    } else {
        cerr << "Unsupported file extensions: " << extension1 << " and " << extension2 << endl;
        return 1;
    }

    return 0;
}

bool is_valid_file(const string& filename, int& number, string& extension) {
    // Check if the input is a valid number
    std::stringstream ss(filename);

    char dot;

    if (ss >> number >> dot >> extension) {
        if(dot == '.') {
            return true;
        }
    }
    return false;
}


