#include <iostream>
#include <vector>
#include <string>
#include "Struct.hpp"

int main() {
  Tape tape(20, "#");
  std::vector<State> arr;
  tape.Put("ver");
  tape.Put("A1");
  tape.Put("edge");
  tape.Put("A2");
  tape.Put("ver");
  tape.Put("A2");
  tape.Put("edge");
  tape.Put("A1");
  tape.Put("A3");
  tape.Put("ver");
  tape.Put("A3");
  tape.Put("edge");
  tape.BackToStart();
  tape.Show();

  std::vector<std::string> alp = {"A1", "A2", "A3"};
  arr.push_back(State()); // q_start - 0
  arr[0].dict["ver"] = Configuration(1, "ver", -1);
  arr.push_back(State()); // q_pre4 - 1
  arr.push_back(State()); // q_pre3 - 2
  arr.push_back(State()); // q_pre2 - 3
  arr.push_back(State()); // q_pre1 - 4
  arr.push_back(State()); // q_pre0 - 5
  arr[1].dict["#"] = Configuration(2, "empty", -1);
  arr[2].dict["#"] = Configuration(3, "empty", -1);
  arr[3].dict["#"] = Configuration(4, "empty", -1);
  arr[4].dict["#"] = Configuration(5, "empty", -1);
  arr[5].dict["#"] = Configuration(6, "stack", -1);
  arr.push_back(State()); // q_pre_been4 - 6
  arr.push_back(State()); // q_pre_been3 - 7
  arr.push_back(State()); // q_pre_been2 - 8
  arr.push_back(State()); // q_pre_been1 - 9
  arr.push_back(State()); // q_pre_been0 - 10
  arr[6].dict["#"] = Configuration(7, "empty", -1);
  arr[7].dict["#"] = Configuration(8, "empty", -1);
  arr[8].dict["#"] = Configuration(9, "empty", -1);
  arr[9].dict["#"] = Configuration(10, "empty", -1);
  arr[10].dict["#"] = Configuration(11, "been", 1);
  arr.push_back(State()); // q_go_to_set_flag - 11
  for (int i = 0; i < alp.size(); ++i) {
    arr[11].dict[alp[i]] = Configuration(11, alp[i], 1);
  }
  arr[11].dict["empty"] = Configuration(11, "empty", 1);
  arr[11].dict["ver"] = Configuration(11, "ver", 1);
  arr[11].dict["stack"] = Configuration(11, "stack", 1);
  arr[11].dict["edge"] = Configuration(12, "edge", 1);
  arr.push_back(State()); // q_set_flag_edge - 12
  for (int i = 0; i < alp.size(); ++i) {
    arr[12].dict[alp[i]] = Configuration(13 + i, "flag_pre_edge", 1);
  }
  arr[12].dict["#"] = Configuration(16 + alp.size(), "flag_pre_edge", 0);
  arr[12].dict["ver"] = Configuration(13 + alp.size(), "flag_pre_edge", 1);
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_shift_<alp[i]> - (13 + i)
  }
  arr.push_back(State()); // q_shift_<ver> - (13 + alp.size())
  arr.push_back(State()); // q_shift_<edge> - (14 + alp.size())
  arr.push_back(State()); // q_shift_<flag_edge> - (15 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    for (int j = 0; j < alp.size(); ++j) {
      arr[13 + i].dict[alp[j]] = Configuration(13 + j, alp[i], 1);
    }
    arr[13 + i].dict["#"] = Configuration(16 + alp.size(), alp[i], -1);
    arr[13 + i].dict["ver"] = Configuration(13 + alp.size(), alp[i], 1);
    arr[13 + i].dict["edge"] = Configuration(14 + alp.size(), alp[i], 1);
    arr[13 + i].dict["flag_edge"] = Configuration(15 + alp.size(), alp[i], 1);
  }
  for (int j = 0; j < alp.size(); ++j) {
    arr[13 + alp.size()].dict[alp[j]] = Configuration(13 + j, "ver", 1);
  }
  arr[13 + alp.size()].dict["#"] = Configuration(16 + alp.size(), "ver", -1);
  arr[13 + alp.size()].dict["ver"] = Configuration(13 + alp.size(), "ver", 1);
  arr[13 + alp.size()].dict["edge"] = Configuration(14 + alp.size(), "ver", 1);
  arr[13 + alp.size()].dict["flag_edge"] = Configuration(15 + alp.size(), "ver", 1);
  for (int j = 0; j < alp.size(); ++j) {
    arr[14 + alp.size()].dict[alp[j]] = Configuration(13 + j, "edge", 1);
  }
  arr[14 + alp.size()].dict["#"] = Configuration(16 + alp.size(), "edge", -1);
  arr[14 + alp.size()].dict["ver"] = Configuration(13 + alp.size(), "edge", 1);
  arr[14 + alp.size()].dict["edge"] = Configuration(14 + alp.size(), "edge", 1);
  arr[14 + alp.size()].dict["flag_edge"] = Configuration(15 + alp.size(), "edge", 1);
  for (int j = 0; j < alp.size(); ++j) {
    arr[15 + alp.size()].dict[alp[j]] = Configuration(13 + j, "flag_edge", 1);
  }
  arr[15 + alp.size()].dict["#"] = Configuration(16 + alp.size(), "flag_edge", -1);
  arr[15 + alp.size()].dict["ver"] = Configuration(13 + alp.size(), "flag_edge", 1);
  arr[15 + alp.size()].dict["edge"] = Configuration(14 + alp.size(), "flag_edge", 1);
  arr[15 + alp.size()].dict["flag_edge"] = Configuration(15 + alp.size(), "flag_edge", 1);
  arr.push_back(State()); // q_go_to_flag - (16 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[16 + alp.size()].dict[alp[i]] = Configuration(16 + alp.size(), alp[i], -1);
  }
  arr[16 + alp.size()].dict["ver"] = Configuration(16 + alp.size(), "ver", -1);
  arr[16 + alp.size()].dict["edge"] = Configuration(16 + alp.size(), "edge", -1);
  arr[16 + alp.size()].dict["flag_edge"] = Configuration(16 + alp.size(), "flag_edge", -1);
  arr[16 + alp.size()].dict["flag_pre_edge"] = Configuration(11, "flag_edge", 1);
  arr[11].dict["#"] = Configuration(17 + alp.size(), "#", -1);
  arr.push_back(State()); // q_go_to_start - (17 + alp.size())

  TuringMachine app(tape, arr);
  app.Start(arr[0], arr[17 + alp.size()]);
  app.Show();

  return 0;
}
