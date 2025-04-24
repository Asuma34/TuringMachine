#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Struct.hpp"

int main() {
  Tape tape(20, "#");
  tape.Show();
  int n1;
  int n2;
  int a;
  std::cout << "everything needs to be written on different lines: \n";
  std::cout << "write the number of word in the alphabet: \n";
  std::cin >> a;
  std::vector<std::string> alp(a);
  std::cout << "write the alphabet: \n";
  std::map<std::string, int> dict;
  for (int i = 0; i < a; ++i) {
    std::cin >> alp[i];
    dict[alp[i]] = i;
  }
  std::cout << "write the number of digits in the substring: \n";
  std::cin >> n1;
  std::cout << "write the number of digits in string: \n";
  std::cin >> n2;
  std::cout << "write the substring: \n";
  for (int i = 0; i < n1; ++i) {
    std::string x;
    std::cin >> x;
    tape.Put(x);
  }
  tape.Put("|");
  std::cout << "write the string: \n";
  for (int i = 0; i < n2; ++i) {
    std::string x;
    std::cin >> x;
    tape.Put(x);
  }

  tape.BackToStart();
  tape.Show();

  std::vector<State> arr;

  arr.push_back(State()); // q_start - 0
  arr[0].dict["#"] = Configuration(0, "#", 1);
  for (int i = 0; i < alp.size(); ++i) {
    arr[0].dict[alp[i]] = Configuration(1, alp[i], -1);
  }
  arr.push_back(State()); // q_set_flag - 1
  arr[1].dict["#"] = Configuration(2, "flag_sym1", 1);
  arr.push_back(State()); // q_go_| - 2
  arr[2].dict["|"] = Configuration(3, "|", 1);
  for (int i = 0; i < alp.size(); ++i) {
    arr[2].dict[alp[i]] = Configuration(2, alp[i], 1);
  }
  arr.push_back(State()); // q_shift - 3
  for (int i = 0; i < alp.size(); ++i) {
    arr[3].dict[alp[i]] = Configuration(4 + dict[alp[i]], "flag_empty", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_shift_<alp[i]> - (4 + i)
  }
  for (int i = 0; i < alp.size(); ++i) {
    for (int j = 0; j < alp.size(); ++j) {
      arr[4 + i].dict[alp[j]] = Configuration(4 + dict[alp[j]], alp[i], 1);
    }
    arr[4 + i].dict["#"] = Configuration(4 + alp.size(), alp[i], -1);
  }
  arr.push_back(State()); // q_go_to_flag - (4 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[4 + alp.size()].dict[alp[i]] = Configuration(4 + alp.size(), alp[i], -1);
  }
  arr[4 + alp.size()].dict["flag_empty"] = Configuration(5 + alp.size(), "flag_word", 1);
  arr.push_back(State()); // q_set_sym2 - (5 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[5 + alp.size()].dict[alp[i]] = Configuration(4 + i, "flag_prestart", 1);
  }
  arr[4 + alp.size()].dict["flag_prestart"] = Configuration(6 + alp.size(), "flag_sym2", -1);
  arr.push_back(State()); // q_go_to_start - (6 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[6 + alp.size()].dict[alp[i]] = Configuration(6 + alp.size(), alp[i], -1);
  }
  arr[6 + alp.size()].dict["|"] = Configuration(6 + alp.size(), "|", -1);
  arr[6 + alp.size()].dict["flag_sym1"] = Configuration(6 + alp.size(), "flag_sym1", -1);
  arr[6 + alp.size()].dict["flag_sym2"] = Configuration(6 + alp.size(), "flag_sym2", -1);
  arr[6 + alp.size()].dict["flag_word"] = Configuration(6 + alp.size(), "flag_word", -1);
  arr[6 + alp.size()].dict["#"] = Configuration(7 + alp.size(), "#", 1);
  arr.push_back(State()); // q_begin0 - (7 + alp.size())
 
  // end prepare

  arr[7 + alp.size()].dict["flag_sym1"] = Configuration(8 + alp.size(), "flag_sym1", 1);
  arr.push_back(State()); // q_shift_flag - (8 + alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[8 + alp.size()].dict[alp[i]] = Configuration(9 + alp.size() + dict[alp[i]], "flag_sym1", -1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_shift_flag_<alp[i]> - (9 + alp.size() + dict[alp[i]])
    arr[9 + alp.size() + dict[alp[i]]].dict["flag_sym1"] = Configuration(9 + 2 * alp.size() + dict[alp[i]], alp[i], 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_find0_<alp[i]> - (9 + 2 * alp.size() + dict[alp[i]])
  }
  for (int i = 0; i < alp.size(); ++i) {
    for (int j = 0; j < alp.size(); ++j) {
      arr[9 + 2 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(9 + 2 * alp.size() + dict[alp[i]], alp[j], 1);
    }
    arr[9 + 2 * alp.size() + dict[alp[i]]].dict["|"] = Configuration(9 + 2 * alp.size() + dict[alp[i]], "|", 1);
    arr[9 + 2 * alp.size() + dict[alp[i]]].dict["flag_sym1"] = Configuration(9 + 2 * alp.size() + dict[alp[i]], "flag_sym1", 1);
    arr[9 + 2 * alp.size() + dict[alp[i]]].dict["flag_word"] = Configuration(9 + 3 * alp.size() + dict[alp[i]], "flag_word", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_find1_<alp[i]> - (9 + 3 * alp.size() + dict[alp[i]])
    arr[9 + 3 * alp.size() + dict[alp[i]]].dict["flag_sym2"] = Configuration(9 + 4 * alp.size() + dict[alp[i]], "flag_sym2", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_check0_<alp[i]> - (9 + 4 * alp.size() + dict[alp[i]])
    for (int j = 0; j < alp.size(); ++j) {
      if (i != j) {
        arr[9 + 4 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(9 + 5 * alp.size() + dict[alp[j]], "flag_sym2", -1);
      } else {
        arr[9 + 4 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(12 + 6 * alp.size() + dict[alp[j]], "flag_sym2", -1);
      }
    }
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_shift_throw_flag_<alp[i]> - (9 + 5 * alp.size() + dict[alp[i]])
    arr[9 + 5 * alp.size() + dict[alp[i]]].dict["flag_word"] = Configuration(9 + 6 * alp.size(), alp[i], -1);
    arr[9 + 5 * alp.size() + dict[alp[i]]].dict["flag_sym2"] = Configuration(9 + 5 * alp.size() + dict[alp[i]], "flag_word", -1);
  }
  arr.push_back(State()); // q_reset - (9 + 6 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[9 + 6 * alp.size()].dict[alp[i]] = Configuration(9 + 6 * alp.size(), alp[i], -1);
  }
  arr[9 + 6 * alp.size()].dict["|"] = Configuration(9 + 6 * alp.size(), "|", -1);
  arr[9 + 6 * alp.size()].dict["flag_word"] = Configuration(9 + 6 * alp.size(), "flag_word", -1);
  arr[9 + 6 * alp.size()].dict["flag_sym2"] = Configuration(9 + 6 * alp.size(), "flag_sym2", -1);
  arr[9 + 6 * alp.size()].dict["flag_sym1"] = Configuration(10 + 6 * alp.size(), "#", -1);
  arr.push_back(State()); // q_go_to_shift - (10 + 6 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[10 + 6 * alp.size()].dict[alp[i]] = Configuration(10 + 6 * alp.size(), alp[i], -1);
  }
  arr[10 + 6 * alp.size()].dict["#"] = Configuration(11 + 6 * alp.size(), "#", 1);
  arr.push_back(State()); // q_pre_reset - (11 + 6 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[11 + 6 * alp.size()].dict[alp[i]] = Configuration(4 + i, "flag_begin", 1);
  }
  arr[4 + alp.size()].dict["flag_begin"] = Configuration(7 + alp.size(), "flag_sym1", 0);
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_shift_success_<alp[i]> - (12 + 6 * alp.size() + dict[alp[i]])
    arr[12 + 6 * alp.size() + dict[alp[i]]].dict["flag_sym2"] = Configuration(12 + 7 * alp.size() + dict[alp[i]], "empty", -1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_suc_check_<alp[i]> - (12 + 7 * alp.size() + dict[alp[i]])
    arr[12 + 7 * alp.size() + dict[alp[i]]].dict["flag_word"] = Configuration(12 + 8 * alp.size(), alp[i], 1);
    for (int j = 0; j < alp.size(); ++j) {
      arr[12 + 7 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(14 + 8 * alp.size() + dict[alp[i]], alp[j], 1);
    }
  }
  arr.push_back(State()); // q_shift_suc_word - (12 + 8 * alp.size())
  arr[12 + 8 * alp.size()].dict["empty"] = Configuration(13 + 8 * alp.size(), "flag_word", -1);
  arr.push_back(State()); // q_next_sym - (13 + 8 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[13 + 8 * alp.size()].dict[alp[i]] = Configuration(13 + 8 * alp.size(), alp[i], -1);
  }
  arr[13 + 8 * alp.size()].dict["|"] = Configuration(13 + 8 * alp.size(), "|", -1);
  arr[13 + 8 * alp.size()].dict["flag_word"] = Configuration(13 + 8 * alp.size(), "flag_word", -1);
  arr[13 + 8 * alp.size()].dict["flag_sym1"] = Configuration(8 + alp.size(), "flag_sym1", 1);
  arr[8 + alp.size()].dict["|"] = Configuration(16 + 12 * alp.size(), "1", 0);
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_set_suc_<alp[i]> - (14 + 8 * alp.size() + dict[alp[i]])
    arr[14 + 8 * alp.size() + dict[alp[i]]].dict["empty"] = Configuration(13 + 8 * alp.size(), alp[i], -1);
  }


  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_find2_<alp[i]> - (14 + 9 * alp.size() + dict[alp[i]])
    for (int j = 0; j < alp.size(); ++j) {
      arr[9 + 3 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(14 + 9 * alp.size() + dict[alp[i]], alp[j], 1);
    }
  }
  for (int i = 0; i < alp.size(); ++i) {
    for (int j = 0; j < alp.size(); ++j) {
      arr[14 + 9 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(14 + 9 * alp.size() + dict[alp[i]], alp[j], 1);
    }
    arr[14 + 9 * alp.size() + dict[alp[i]]].dict["flag_sym2"] = Configuration(14 + 10 * alp.size() + dict[alp[i]], "flag_sym2", 1);
  }
  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_check1_<alp[i]> - (14 + 10 * alp.size() + dict[alp[i]])
    for (int j = 0; j < alp.size(); ++j) {
      if (i != j) {
        arr[14 + 10 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(14 + 11 * alp.size(), alp[j], -1);
      } else {
        arr[14 + 10 * alp.size() + dict[alp[i]]].dict[alp[j]] = Configuration(16 + 11 * alp.size() + dict[alp[i]], "flag_sym2", -1);
      }
    }
  }
  arr.push_back(State()); // q_fail - (14 + 11 * alp.size())
  arr[14 + 11 * alp.size()].dict["flag_sym2"] = Configuration(14 + 11 * alp.size(), "#", -1);
  for (int i = 0; i < alp.size(); ++i) {
    arr[14 + 11 * alp.size()].dict[alp[i]] = Configuration(14 + 11 * alp.size(), alp[i], -1);
  }
  arr[14 + 11 * alp.size()].dict["flag_word"] = Configuration(15 + 11 * alp.size(), "flag_word", 1);
  arr.push_back(State()); // q_fail1 - (15 + 11 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[15 + 11 * alp.size()].dict[alp[i]] = Configuration(4 + i, "flag_fail", 1);
  }
  arr[4 + alp.size()].dict["flag_fail"] = Configuration(9 + 6 * alp.size(), "flag_sym2", -1);
 

  for (int i = 0; i < alp.size(); ++i) {
    arr.push_back(State()); // q_suc1_<alp[i]> - (16 + 11 * alp.size() + dict[alp[i]])
    arr[16 + 11 * alp.size() + dict[alp[i]]].dict["flag_sym2"] = Configuration(13 + 8 * alp.size(), alp[i], -1);
  }
  arr.push_back(State()); // q_fin - (16 + 12 * alp.size())
  for (int i = 0; i < alp.size(); ++i) {
    arr[9 + 2 * alp.size() + dict[alp[i]]].dict["#"] = Configuration(16 + 12 * alp.size(), "0", 0);
    arr[9 + 3 * alp.size() + dict[alp[i]]].dict["#"] = Configuration(16 + 12 * alp.size(), "0", 0);
    arr[9 + 4 * alp.size() + dict[alp[i]]].dict["#"] = Configuration(16 + 12 * alp.size(), "0", 0);
    arr[14 + 9 * alp.size() + dict[alp[i]]].dict["#"] = Configuration(16 + 12 * alp.size(), "0", 0);
    arr[14 + 10 * alp.size() + dict[alp[i]]].dict["#"] = Configuration(16 + 12 * alp.size(), "0", 0);
  }


  TuringMachine app(tape, arr);
  app.Start(arr[0], arr[16 + 12 * alp.size()]);
  app.Show();

  return 0;
}

