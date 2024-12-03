#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> splitstring(const std::string &str, char delimiter) {
  std::vector<std::string> result;
  std::stringstream ss(str);
  std::string item;

  while (std::getline(ss, item, delimiter)) {
    result.push_back(item);
  }

  return result;
}

int main() {
  std::ifstream MyFile("input.txt");
  std::string line;
  int counterForCorrectRows = 0;

  while (std::getline(MyFile, line)) {
    std::vector<std::string> result = splitstring(line, ' ');

    // Skip lines with fewer than 2 numbers
    if (result.size() < 2) {
      continue;
    }

    // Convert strings to integers for processing
    std::vector<int> numbers(result.size());
    for (size_t i = 0; i < result.size(); ++i) {
      numbers[i] = std::stoi(result[i]);
    }

    // Check if the line is ascending or descending
    bool isAscending = true;
    bool isDescending = true;

    for (size_t i = 0; i < numbers.size() - 1; ++i) {
      if (numbers[i] > numbers[i + 1]) {
        isAscending = false;
      }
      if (numbers[i] < numbers[i + 1]) {
        isDescending = false;
      }
    }

    // Check if differences between consecutive numbers are within range
    bool validDifferences = true;
    for (size_t i = 0; i < numbers.size() - 1; ++i) {
      int diff = std::abs(numbers[i] - numbers[i + 1]);
      if (diff <= 0 || diff >= 4) {
        validDifferences = false;
        break;
      }
    }

    // Increment counter if the row is valid
    if ((isAscending || isDescending) && validDifferences) {
      ++counterForCorrectRows;
    }
  }

  std::cout << "The result is: " << counterForCorrectRows << std::endl;
  return 0;
}
