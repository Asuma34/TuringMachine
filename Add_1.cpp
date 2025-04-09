#include <iostream>
#include <string>
#include <vector>
#include "Struct.hpp"

// this code allows you add 1 to the end of the string

int main() {
  std::vector<State> array;
  Tape tape(20, "#");
  State q_start;
  State q_return;
  State q_fin;
  array.push_back(q_start);
  array.push_back(q_return);
  array.push_back(q_fin);
  array[0].dict["0"] = Configuration(0, "0", 1);
  array[0].dict["1"] = Configuration(0, "1", 1);
  array[0].dict["#"] = Configuration(1, "1", -1);
  array[1].dict["1"] = Configuration(1, "1", -1);
  array[1].dict["0"] = Configuration(1, "0", -1);
  array[1].dict["#"] = Configuration(2, "#", 0);
  tape.Right();
  tape.Set("0");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("0");
  tape.BackToStart();
  tape.Show();
  tape.Right();
  std::cout << "start: " << '\n';
  tape.Start(tape, array, 0, 2);
  tape.Show();

  return 0;

}
