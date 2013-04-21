#include <iostream>
#include <memory>
#include <cmath>
#include "animal.hpp"

using std::cout;
using std::endl;
using std::unique_ptr;

class Cat : public Animal {
public:
  Cat() {
    cout << "Cat was born." << endl;
  }
  ~Cat() {
    cout << "Cat died." << endl;
  }
  virtual void Cry() const {
     cout << "\"Meow\"" << endl;
  }
};

extern "C" unique_ptr<Animal> Create() {
  return unique_ptr<Animal>(new Cat);
}
