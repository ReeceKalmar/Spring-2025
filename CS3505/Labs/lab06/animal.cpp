#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal {
protected:
  string name;
  double age;

public:
  Animal(string name) : name(name), age(0) {};
  virtual void speak() { cout << "I am an Animal named " << name << endl; }
  void talk() { speak(); }
};

class Cat : public Animal {
  bool isHouseCat;

public:
  Cat(string catName, bool houseCat) : Animal(catName), isHouseCat(houseCat) {}

  virtual void speak() {
    cout << "Meow" << " I am " << name << " and my housecatness is "
         << isHouseCat << endl;
  }
};

class Dog : public Animal {
public:
  Dog(string dogName) : Animal(dogName) {}

  void speak() override { cout << "Woof! I am " << name << endl; }
};

int main(int argc, char *argv[]) {
  Cat cat("world", true);
  Dog dog("hello");

  cat.speak();
  dog.speak();

  std::vector<Animal *> animalList;

  animalList.push_back(&cat);
  animalList.push_back(&dog);

  for (Animal *animal : animalList) {
    animal->speak();
  }

	std::cout << "LAST" << "\n";

	Animal* confused = new Cat("Constantinople", false);

	confused->talk();

  return 0;
}
