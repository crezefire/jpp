#include <iostream>

#include "jpp/Jpp.h"

using namespace jpp::literals;
using namespace std::string_literals;

struct foo{ int x {1337}; foo(int y) : x(y) {} };

template<typename T>
class TD;

int main() {

  jpp::obj asdf {
    "string"_f = "stringy",
    "double"_f = 3.1415,
    "integer"_f = 13245,
    "boolean"_f = false,
    "fuckall"_f = foo(6666),
    "nothing"_f = nullptr
  };

  //return a lambda based struct with conversion to bool and <type> passed in
  //try to add template overload to asdf<type>["asdf"]
  auto a0 = asdf["string"].GetValue<jpp::str>();
  auto a1 = asdf["double"].GetValue<double>();
  auto a2 = asdf["integer"].GetValue<int>();
  auto a3 = asdf["boolean"].GetValue<bool>();
  auto a4 = asdf["fuckall"].GetValue<foo>();
  auto a5 = asdf["nothing"].GetValue<jpp::null>();

  a0++;
  a1 += 1.0f;
  a2++;
  a3 ^= a3;
  a4->x++;
  a4 = a5;


  return 0;
}