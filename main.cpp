#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// Function to split a string by a delimiter
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
  std::ifstream MyInput("input.txt");
  if (!MyInput.is_open()) {
    std::cerr << "Error: Unable to open file" << std::endl;
    return 1;
  }

  std::regex pattern(R"(\b(mul\(\d+,\d+\)|don't\(\)|do\(\)))");
  std::smatch match;
  std::vector<std::string> matches; // To store all matches

  std::string line;
  while (std::getline(MyInput, line)) {
    while (std::regex_search(line, match, pattern)) {
      matches.push_back(match.str()); // Store the full match
      line = match.suffix().str();    // Advance to the rest of the line
    }
  }
  MyInput.close();

  // Split and calculate multiplication
  int sum = 0;
  bool ifdont = false;
  for (const auto &multi : matches) {

    if (multi == "do()") {
      ifdont = false;
    }
    if (multi == "don't()") {
      ifdont = true;
    }
    if (ifdont)
      continue;

    std::string inner =
        multi.substr(4, multi.length() - 5); // Extract inner content
    std::vector<std::string> splited = splitstring(inner, ',');
    if (splited.size() == 2) { // Ensure two numbers are present
      sum += std::stoi(splited[0]) * std::stoi(splited[1]);
    }
  }

  std::cout << "The result is: " << sum << std::endl;
  return 0;
}
