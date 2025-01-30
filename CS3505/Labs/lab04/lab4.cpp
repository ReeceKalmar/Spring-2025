#include <iostream>

int *getIntPtr() {
  int number = 5;
  return &number;
}

int main(int argc, char *argv[]) {
  int *ptr = getIntPtr();
  std::cout << ptr << " " << *ptr << std::endl;
}
