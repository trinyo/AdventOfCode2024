#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
  // Bemeneti fájl
  ifstream inputFile("input.txt");
  string line;
  list<int> list1{};
  list<int> list2{};

  while (getline(inputFile, line)) {
    istringstream iss(line);
    string token;
    int index = 0;

    try {
      while (getline(iss, token, ' ')) {
        if (!token.empty()) {
          if (index % 2 == 0) {
            list1.push_back(stoi(token));
          } else {
            list2.push_back(stoi(token));
          }
          index++;
        }
      }
    } catch (invalid_argument &e) {
      cerr << "Hiba történt a szám konvertálásakor: " << e.what() << endl;
    }
  }

  // Rendezés
  list1.sort();
  list2.sort();

  // Távolság számítása
  int distance = 0;
  auto it1 = list1.begin();
  auto it2 = list2.begin();
  while (it1 != list1.end() && it2 != list2.end()) {
    distance += std::abs(*it1 - *it2);
    ++it1;
    ++it2;
  }

  // Eredmény kiírása
  cout << "The result is: " << distance << "\n";

  return 0;
}
