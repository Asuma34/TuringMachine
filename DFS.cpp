#include <iostream>
#include <vector>
#include <string>
#include "Struct.hpp"

int main() {
  Tape tape(20, "#");
  std::vector<State> arr;
  std::cout << "size alphabet:\n";
  int n;
  std::cin >> n;
  std::cout << "print give alphabet:\n";
  std::vector<std::string> alp(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> alp[i];
  }
  while (true) {
    std::string s;
    std::cin >> s;
    if (s == "end") {
      break;
    }
    tape.Put(s);
  }
  /*
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
  */
  tape.BackToStart();
  tape.Show();

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
  for (int i = 0; i < alp.size(); ++i) {
    arr[17 + alp.size()].dict[alp[i]] = Configuration(17 + alp.size(), alp[i], -1);
  }
  arr[17 + alp.size()].dict["ver"] = Configuration(17 + alp.size(), "ver", -1);
  arr[17 + alp.size()].dict["edge"] = Configuration(17 + alp.size(), "edge", -1);
  arr[17 + alp.size()].dict["flag_edge"] = Configuration(17 + alp.size(), "flag_edge", -1);
  arr[17 + alp.size()].dict["empty"] = Configuration(17 + alp.size(), "empty", -1);
  arr[17 + alp.size()].dict["stack"] = Configuration(18 + alp.size(), "stack", 1);
  arr.push_back(State()); // q_start - (18 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[18 + alp.size()].dict[alp[i]] = Configuration(18 + alp.size(), alp[i], 1);
  }
  arr[18 + alp.size()].dict["empty"] = Configuration(18 + alp.size(), "empty", 1);
  arr[18 + alp.size()].dict["ver"] = Configuration(19 + alp.size(), "ver", 1);
  arr.push_back(State()); // q_step - (19 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_add_been_<alp[i]> - (20 + alp.size() + i)
    arr[19 + alp.size()].dict[alp[i]] = Configuration(20 + alp.size() + i, alp[i], -1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    for (int j = 0; j < alp.size(); ++j) {
      arr[20 + alp.size() + i].dict[alp[j]] = Configuration(20 + alp.size() + i, alp[j], -1);
    }
    arr[20 + alp.size() + i].dict["flag_edge"] = Configuration(20 + alp.size() + i, "flag_edge", -1);
    arr[20 + alp.size() + i].dict["ver"] = Configuration(20 + alp.size() + i, "ver", -1);
    arr[20 + alp.size() + i].dict["empty"] = Configuration(20 + alp.size() + i, "empty", -1);
    arr[20 + alp.size() + i].dict["stack"] = Configuration(20 + alp.size() + i, "stack", -1);
    arr[20 + alp.size() + i].dict["edge"] = Configuration(20 + alp.size() + i, "edge", -1);
    arr[20 + alp.size() + i].dict["been"] = Configuration(20 + 2 * alp.size() + i, "been", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_set_been_<alp[i]> - (20 + 2 * alp.size() + i)
    for (int j = 0; j < alp.size(); ++j) {
      arr[20 + 2 * alp.size() + i].dict[alp[j]] = Configuration(20 + 2 * alp.size() + i, alp[j], 1);
    }
    arr[20 + 2 * alp.size() + i].dict["empty"] = Configuration(20 + 3 * alp.size() + i, alp[i], 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_add_to_stack_<alp[i]> - (20 + 3 * alp.size() + i)
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_go_to_<alp[i]> - (20 + 4 * alp.size() + i)
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr[20 + 4 * alp.size() + i].dict["ver"] = Configuration(20 + 5 * alp.size() + i, "ver", 1);
    for (int j = 0; j < alp.size(); ++j) {
      arr[20 + 4 * alp.size() + i].dict[alp[j]] = Configuration(20 + 4 * alp.size() + i, alp[j], 1);
    }
    arr[20 + 4 * alp.size() + i].dict["edge"] = Configuration(20 + 4 * alp.size() + i, "edge", 1);
    arr[20 + 4 * alp.size() + i].dict["empty"] = Configuration(20 + 4 * alp.size() + i, "empty", 1);
    arr[20 + 4 * alp.size() + i].dict["stack"] = Configuration(20 + 4 * alp.size() + i, "stack", 1);
    arr[20 + 4 * alp.size() + i].dict["been"] = Configuration(20 + 4 * alp.size() + i, "been", 1);
    arr[20 + 4 * alp.size() + i].dict["flag_edge"] = Configuration(20 + 4 * alp.size() + i, "flag_edge", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_check_next_<alp[i]> - (20 + 5 * alp.size() + i)
  }
  for (int i = 0; i < alp.size(); ++i) {
    for (int j = 0; j < alp.size(); ++j) {
      if (i == j) {
        arr[20 + 5 * alp.size() + i].dict[alp[j]] = Configuration(20 + 6 * alp.size(), alp[j], 1);
      } else {
        arr[20 + 5 * alp.size() + i].dict[alp[j]] = Configuration(20 + 4 * alp.size() + i, alp[j], 1);
      }
    }
  }
  arr.push_back(State()); // q_go_to_edge - (20 + 6 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[20 + 6 * alp.size()].dict[alp[i]] = Configuration(20 + 6 * alp.size(), alp[i], 1);
  }
  arr[20 + 6 * alp.size()].dict["edge"] = Configuration(20 + 6 * alp.size(), "edge", 1);
  arr[20 + 6 * alp.size()].dict["flag_edge"] = Configuration(21 + 6 * alp.size(), "flag_edge", 1);
  arr.push_back(State()); // q_next_edge - (21 + 6 * alp.size())
  arr[21 + 6 * alp.size()].dict["ver"] = Configuration(22 + 6 * alp.size(), "ver", -1);
  arr[21 + 6 * alp.size()].dict["#"] = Configuration(22 + 6 * alp.size(), "#", -1);
  arr.push_back(State()); // q_remove_from_stack - (22 + 6 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[21 + 6 * alp.size()].dict[alp[i]] = Configuration(23 + 6 * alp.size() + i, "flag_edge", -1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_shift_edge_<alp[i]> - (23 + 6 * alp.size() + i)
    arr[23 + 6 * alp.size() + i].dict["flag_edge"] = Configuration(23 + 7 * alp.size() + i, alp[i], -1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_check_been_<alp[i]> - (23 + 7 * alp.size() + i)
    for (int j = 0; j < alp.size(); ++j) {
      arr[23 + 7 * alp.size() + i].dict[alp[j]] = Configuration(23 + 7 * alp.size() + i, alp[j], -1);
    }
    arr[23 + 7 * alp.size() + i].dict["flag_edge"] = Configuration(23 + 7 * alp.size() + i, "flag_edge", -1);
    arr[23 + 7 * alp.size() + i].dict["ver"] = Configuration(23 + 7 * alp.size() + i, "ver", -1);
    arr[23 + 7 * alp.size() + i].dict["edge"] = Configuration(23 + 7 * alp.size() + i, "edge", -1);
    arr[23 + 7 * alp.size() + i].dict["empty"] = Configuration(23 + 7 * alp.size() + i, "empty", -1);
    arr[23 + 7 * alp.size() + i].dict["stack"] = Configuration(23 + 7 * alp.size() + i, "stack", -1);
    arr[23 + 7 * alp.size() + i].dict["been"] = Configuration(23 + 8 * alp.size() + i, "been", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_check_been1_<alp[i]> - (23 + 8 * alp.size() + i)
    for (int j = 0; j < alp.size(); ++j) {
      if (i == j) {
        arr[23 + 8 * alp.size() + i].dict[alp[j]] = Configuration(32 + 11 * alp.size(), alp[j], -1);
      } else {
        arr[23 + 8 * alp.size() + i].dict[alp[j]] = Configuration(23 + 8 * alp.size() + i, alp[j], 1);
      }
    }
    arr[23 + 8 * alp.size() + i].dict["empty"] = Configuration(20 + 3 * alp.size() + i, alp[i], 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr[20 + 3 * alp.size() + i].dict["empty"] = Configuration(20 + 3 * alp.size() + i, "empty",  1);
    arr[20 + 3 * alp.size() + i].dict["stack"] = Configuration(23 + 9 * alp.size() + i, "stack", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_add_to_stack1_<alp[i]> - (23 + 9 * alp.size() + i)
    for (int j = 0; j < alp.size(); ++j) {
      arr[23 + 9 * alp.size() + i].dict[alp[j]] = Configuration(23 + 9 * alp.size() + i, alp[j], 1);
    }
    arr[23 + 9 * alp.size() + i].dict["empty"] = Configuration(23 + 10 * alp.size(), alp[i], 1);
  }
  arr.push_back(State()); // q_check_stack_over - (23 + 10 * alp.size())
  arr[23 + 10 * alp.size()].dict["empty"] = Configuration(24 + 10 * alp.size(), "empty", -1);
  arr[23 + 10 * alp.size()].dict["ver"] = Configuration(25 + 10 * alp.size(), "ver", -1);
  arr.push_back(State()); // q_check_been_over - (24 + 10 * alp.size())
  arr.push_back(State()); // q_increase_stack - (25 + 10 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[25 + 10 * alp.size()].dict[alp[i]] = Configuration(26 + 10 * alp.size() + i, "flag_pre_check_been",  -1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_shift_left_<alp[i]> - (26 + 10 * alp.size() + i)
  }
  arr.push_back(State()); // q_shift_left_<"been"> - (26 + 11 * alp.size())
  arr.push_back(State()); // q_shift_left_<"stack"> - (27 + 11 * alp.size())
  arr.push_back(State()); // q_shift_left_<"empty"> - (28 + 11 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    for (int j = 0; j < alp.size(); ++j) {
      arr[26 + 10 * alp.size() + i].dict[alp[j]] = Configuration(26 + 10 * alp.size() + j, alp[i], -1);
    }
    arr[26 + 10 * alp.size() + i].dict["empty"] = Configuration(28 + 11 * alp.size(), alp[i], -1);
    arr[26 + 10 * alp.size() + i].dict["stack"] = Configuration(27 + 11 * alp.size(), alp[i], -1);
    arr[26 + 10 * alp.size() + i].dict["been"] = Configuration(26 + 11 * alp.size(), alp[i], -1);
    arr[26 + 10 * alp.size() + i].dict["#"] = Configuration(29 + 11 * alp.size(), alp[i], 1);
  }
  for (int j = 0; j < alp.size(); ++j) {
    arr[26 + 11 * alp.size()].dict[alp[j]] = Configuration(26 + 10 * alp.size() + j, "been", -1);
  }
  arr[26 + 11 * alp.size()].dict["empty"] = Configuration(28 + 11 * alp.size(), "been", -1);
  arr[26 + 11 * alp.size()].dict["stack"] = Configuration(27 + 11 * alp.size(), "been", -1);
  arr[26 + 11 * alp.size()].dict["been"] = Configuration(26 + 11 * alp.size(), "been", -1);
  arr[26 + 11 * alp.size()].dict["#"] = Configuration(29 + 11 * alp.size(), "been", 1);
  for (int j = 0; j < alp.size(); ++j) {
    arr[27 + 11 * alp.size()].dict[alp[j]] = Configuration(26 + 10 * alp.size() + j, "stack", -1);
  }
  arr[27 + 11 * alp.size()].dict["empty"] = Configuration(28 + 11 * alp.size(), "stack", -1);
  arr[27 + 11 * alp.size()].dict["stack"] = Configuration(27 + 11 * alp.size(), "stack", -1);
  arr[27 + 11 * alp.size()].dict["been"] = Configuration(26 + 11 * alp.size(), "stack", -1);
  arr[27 + 11 * alp.size()].dict["#"] = Configuration(29 + 11 * alp.size(), "stacK", 1);
  for (int j = 0; j < alp.size(); ++j) {
    arr[28 + 11 * alp.size()].dict[alp[j]] = Configuration(26 + 10 * alp.size() + j, "empty", -1);
  }
  arr[28 + 11 * alp.size()].dict["empty"] = Configuration(28 + 11 * alp.size(), "empty", -1);
  arr[28 + 11 * alp.size()].dict["stack"] = Configuration(27 + 11 * alp.size(), "empty", -1);
  arr[28 + 11 * alp.size()].dict["been"] = Configuration(26 + 11 * alp.size(), "empty", -1);
  arr[28 + 11 * alp.size()].dict["#"] = Configuration(29 + 11 * alp.size(), "empty", 1);
  arr.push_back(State()); // q_go_right_to_flag - (29 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[29 + 11 * alp.size()].dict[alp[j]] = Configuration(29 + 11 * alp.size(), alp[j], 1);
  }
  arr[29 + 11 * alp.size()].dict["been"] = Configuration(29 + 11 * alp.size(), "been", 1);
  arr[29 + 11 * alp.size()].dict["stack"] = Configuration(29 + 11 * alp.size(), "stack", 1);
  arr[29 + 11 * alp.size()].dict["empty"] = Configuration(29 + 11 * alp.size(), "empty", 1);
  arr[29 + 11 * alp.size()].dict["flag_pre_check_been"] = Configuration(24 + 10 * alp.size(), "empty", -1);
  for (int j = 0; j < alp.size(); ++j) {
    arr[24 + 10 * alp.size()].dict[alp[j]] = Configuration(24 + 10 * alp.size(), alp[j], -1);
  }
  arr[24 + 10 * alp.size()].dict["stack"] = Configuration(24 + 10 * alp.size(), "stack", -1);
  arr[24 + 10 * alp.size()].dict["empty"] = Configuration(24 + 10 * alp.size(), "empty", -1);
  arr[24 + 10 * alp.size()].dict["been"] = Configuration(30 + 11 * alp.size(), "been", 1);
  arr.push_back(State()); // q_check1_been_over - (30 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[30 + 11 * alp.size()].dict[alp[j]] = Configuration(30 + 11 * alp.size(), alp[j], 1);
  }
  arr[30 + 11 * alp.size()].dict["stack"] = Configuration(31 + 11 * alp.size(), "stack", -1);
  arr[30 + 11 * alp.size()].dict["empty"] = Configuration(32 + 11 * alp.size(), "empty", -1);
  arr.push_back(State()); // q_increase_stack - (31 + 11 * alp.size())
  arr.push_back(State()); // q_next_step - (32 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[31 + 11 * alp.size()].dict[alp[j]] = Configuration(26 + 10 * alp.size() + j, "flag_pre_next_step", -1);
  }
  arr[29 + 11 * alp.size()].dict["flag_pre_next_step"] = Configuration(32 + 11 * alp.size(), "empty", -1);
  for (int j = 0; j < alp.size(); ++j) {
    arr[32 + 11 * alp.size()].dict[alp[j]] = Configuration(32 + 11 * alp.size(), alp[j], -1);
  }
  arr[32 + 11 * alp.size()].dict["stack"] = Configuration(32 + 11 * alp.size(), "stack", -1);
  arr[32 + 11 * alp.size()].dict["edge"] = Configuration(32 + 11 * alp.size(), "edge", -1);
  arr[32 + 11 * alp.size()].dict["ver"] = Configuration(32 + 11 * alp.size(), "ver", -1);
  arr[32 + 11 * alp.size()].dict["empty"] = Configuration(32 + 11 * alp.size(), "empty", -1);
  arr[32 + 11 * alp.size()].dict["flag_edge"] = Configuration(32 + 11 * alp.size(), "flag_edge", -1);
  arr[32 + 11 * alp.size()].dict["been"] = Configuration(33 + 11 * alp.size(), "been", 1);
  arr.push_back(State()); // q_next_step_stack - (33 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[33 + 11 * alp.size()].dict[alp[j]] = Configuration(33 + 11 * alp.size(), alp[j], 1);
  }
  arr[33 + 11 * alp.size()].dict["empty"] = Configuration(33 + 11 * alp.size(), "empty", 1);
  arr[33 + 11 * alp.size()].dict["stack"] = Configuration(34 + 11 * alp.size(), "stack", 1);
  arr.push_back(State()); // q_next_step_edge - (34 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[34 + 11 * alp.size()].dict[alp[j]] = Configuration(34 + 11 * alp.size(), alp[j], 1);
  }
  arr[34 + 11 * alp.size()].dict["empty"] = Configuration(35 + 11 * alp.size(), "empty", -1);
  arr.push_back(State()); // q_pre_step - (35 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[35 + 11 * alp.size()].dict[alp[j]] = Configuration(20 + 4 * alp.size() + j, alp[j], -1);
  }
  for (int j = 0; j < alp.size(); ++j) {
    arr[22 + 6 * alp.size()].dict[alp[j]] = Configuration(22 + 6 * alp.size(), alp[j], -1);
  }
  arr[22 + 6 * alp.size()].dict["flag_edge"] = Configuration(22 + 6 * alp.size(), "flag_edge", -1);
  arr[22 + 6 * alp.size()].dict["ver"] = Configuration(22 + 6 * alp.size(), "ver", -1);
  arr[22 + 6 * alp.size()].dict["edge"] = Configuration(22 + 6 * alp.size(), "edge", -1);
  arr[22 + 6 * alp.size()].dict["empty"] = Configuration(22 + 6 * alp.size(), "empty", -1);
  arr[22 + 6 * alp.size()].dict["stack"] = Configuration(36 + 11 * alp.size(), "stack", 1);
  arr.push_back(State()); // q_remove_from_stack1 - (36 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[36 + 11 * alp.size()].dict[alp[j]] = Configuration(36 + 11 * alp.size(), alp[j], 1);
  }
  arr[36 + 11 * alp.size()].dict["empty"] = Configuration(37 + 11 * alp.size(), "empty", -1);
  arr.push_back(State()); // q_remove_from_stack2 - (37 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[37 + 11 * alp.size()].dict[alp[j]] = Configuration(38 + 11 * alp.size(), "empty", -1);
  }
  arr.push_back(State()); // q_check_end - (38 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[38 + 11 * alp.size()].dict[alp[j]] = Configuration(20 + 4 * alp.size() + j, alp[j], 1);
  }
  arr[38 + 11 * alp.size()].dict["stack"] = Configuration(39 + 11 * alp.size(), "stack", -1);
  arr.push_back(State()); // q_go_to_end - (39 + 11 * alp.size())
  for (int j = 0; j < alp.size(); ++j) {
    arr[39 + 11 * alp.size()].dict[alp[j]] = Configuration(39 + 11 * alp.size(), alp[j], -1);
  }
  arr[39 + 11 * alp.size()].dict["empty"] = Configuration(39 + 11 * alp.size(), "empty", -1);
  arr[39 + 11 * alp.size()].dict["been"] = Configuration(40 + 11 * alp.size(), "been", 0);
  arr.push_back(State()); // q_fin - (40 + 11 * alp.size())

  TuringMachine app(tape, arr);
  app.Start(arr[0], arr[40 + 11 * alp.size()]);
  app.Show();

  return 0;
}
