#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int main() {
  std::string PathOfFile;
  std::cout << "Please enter an input" << std::endl;
  std::getline(std::cin, PathOfFile);
  std::ifstream file(PathOfFile); // create an object of the file
  if (!file.is_open()) {
    std::cout << "File not found\n";
  } else {
    std::cout << "File Found";
  }
  return 0;
}
