#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "animal.hpp"

using std::cerr;
using std::endl;
using std::string;

void *LoadFuncOrDie(void *lib, const string& func_name) {
  void* func = dlsym(lib, func_name.c_str());
  const char* dlsym_error = dlerror();
  if (dlsym_error) {
    cerr << "Cannot load symbol create: " << dlsym_error << endl;
    dlclose(lib);
    exit(EXIT_FAILURE);
  }
  return func;
}

void *LoadLibOrDie(const string& path) {
  void *lib = dlopen(path.c_str(), RTLD_LAZY);
  if (!lib) {
    cerr << "Cannot load library: " << dlerror() << endl;
    exit(EXIT_FAILURE);
  }
  return lib;
}

int main(int argc, char **argv) {
  const auto catlib = LoadLibOrDie("./cat.so");
  const auto doglib = LoadLibOrDie("./dog.so");
  const AnimalCreateFunc* CreateCat = (AnimalCreateFunc*) LoadFuncOrDie(catlib, "Create");
  const AnimalCreateFunc* CreateDog = (AnimalCreateFunc*) LoadFuncOrDie(doglib, "Create");
  {
    const auto& cat = CreateCat();
    cat->Cry();
  }
  {
    const auto& dog = CreateDog();
    dog->Cry();
  }
  dlclose(catlib);
  dlclose(doglib);
}
