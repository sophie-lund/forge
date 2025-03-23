#include <iostream>

int main() {
  std::cerr << "error: file does not exist 'test/test.frg'" << std::endl;
  std::cerr << std::endl;

  std::cerr << "test/test.frg: error: 'main' function not found" << std::endl;
  std::cerr << std::endl;

  return 0;
}
