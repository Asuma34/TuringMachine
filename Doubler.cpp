#include <iostream>
#include <vector>
#include <string>
#include "Struct.hpp"

// this code allows you to turn string of n units 1 into a string of 2n units

int main() {
  std::vector<State> array;
  Tape tape(25, "#");

  State q_start;           // 0
  State q_prep;            // 1
  State q_go_right;        // 2
  State q_go_left;         // 3
  State q_go_right_to_sig; // 4
  State q_go_to_end;       // 5
  State q_set_1;           // 6
  State q_go_left_to_sig;  // 7
  State q_fin;             // 8

  array.push_back(q_start);
  array.push_back(q_prep);
  array.push_back(q_go_right);
  array.push_back(q_go_left);
  array.push_back(q_go_right_to_sig);
  array.push_back(q_go_to_end);
  array.push_back(q_set_1);
  array.push_back(q_go_left_to_sig);
  array.push_back(q_fin);

  array[0].dict["1"] = Configuration(1, "1", -1);
  array[1].dict["#"] = Configuration(2, "end", 1);
  array[2].dict["1"] = Configuration(2, "1", 1);
  array[2].dict["#"] = Configuration(3, "|", -1);
  array[3].dict["1"] = Configuration(4, "#", 1);
  array[3].dict["#"] = Configuration(3, "#", -1);
  array[4].dict["#"] = Configuration(4, "#", 1);
  array[4].dict["|"] = Configuration(5, "|", 1);
  array[5].dict["1"] = Configuration(5, "1", 1);
  array[5].dict["#"] = Configuration(6, "1", 1);
  array[6].dict["#"] = Configuration(7, "1", -1);
  array[7].dict["1"] = Configuration(7, "1", -1);
  array[7].dict["|"] = Configuration(3, "|", -1);
  array[3].dict["end"] = Configuration(8, "end", 0);
  array[8].dict["end"] = Configuration(1, "end", 0);

  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.BackToStart();
  tape.Show();
  tape.Right();
  std::cout << "start: " << '\n';
  tape.Start(tape, array, 0, 8);
  tape.Show();

  return 0;
}
