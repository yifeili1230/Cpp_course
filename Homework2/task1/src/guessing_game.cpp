#include <cstdlib>
#include <iostream>
#include <random>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 99);
  int secret_number = distr(gen);
  int guess;

  cout << "Welcome to the Guessing Game! Enter a number between 0 and 99 to "
          "guess: "
       << endl;

  while (true) {
    cin >> guess;

    if (cin.fail()) {
      if (cin.eof()) {
        cerr << "Error encountered, exiting..." << endl;
        cout << "The secret number was: " << secret_number << endl;
        return 1;
      }
      cin.clear(); // Clear the error state
      cin.ignore(std::numeric_limits<std::streamsize>::max(),
                 '\n'); // Discard invalid input

      cerr << "[WARNING] : Number must be between 0 and 99" << endl;
      continue;
    }

    if (guess < 0 || guess > 99) {
      cerr << "[WARNING] : Number must be between 0 and 99" << endl;
      continue;
    }

    if (guess < secret_number) {
      cout << "Too low! Try again: " << endl;
    } else if (guess > secret_number) {
      cout << "Too high! Try again: " << endl;
    } else {
      cout << "Congratulations! You've guessed the number!" << endl;
      break;
    }
  }

  return 0;
};
