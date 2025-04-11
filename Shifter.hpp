#include "Struct.hpp"

// this code shifts all character up to # to the right

void Shift(MachineTuring& app, State& start_shift, State& fin) {
  State q_shift_0; // 1
  State q_shift_1; // 2
  std::vector<State> arr;
  arr.push_back(q_start_shift);
  arr.push_back(q_shift_0);
  arr.push_back(q_shift_1);
  arr.push_back(fin)
  arr[0].dict["1"] = Configuration(2, "#", 1);
  arr[0].dict["0"] = Configuration(1, "#", 1);
  arr[1].dict["0"] = Configuration(1, "0", 1);
  arr[1].dict["1"] = Configuration(2, "0", 1);
  arr[2].dict["0"] = Configuration(1, "1", 1);
  arr[2].dict["1"] = Configuration(2, "1", 1);
  arr[2].dict["#"] = Configuration(3, "1", 0);
  arr[1].dict["#"] = Configuration(3, "0", 0);
  MachineTuring ShiftMachine(app.GetTape(), arr);
  ShiftMachine.Start(start_shift, fin);
}
