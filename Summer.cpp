#include <iostream>
#include <vector>
#include "Struct.hpp"

int main() {
  std::vector<State> st;
  Tape tape(20, "#");
  tape.Show();
  /*
  // this example if you don't want to enter the number yourself
  tape.Set("1");
  tape.Right();
  tape.Set("0");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("0");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("0");
  tape.Right();
  tape.Set("0");
  tape.Right();
  tape.Set("|");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.Set("1");
  tape.Right();
  tape.BackToStart();*/
  int n1;
  int n2;
  std::cout << "write the number of digits in the first number: \n";
  std::cin >> n1;
  std::cout << "write the number of digits in the second number: \n";
  std::cin >> n2;
  std::cout << "write the first number: \n";
  for (int i = 0; i < n1; ++i) {
    std::string x;
    std::cin >> x;
    tape.Put(x);
  }
  tape.Put("|");
  std::cout << "write the second number: \n";
  for (int i = 0; i < n2; ++i) {
    std::string x;
    std::cin >> x;
    tape.Put(x);
  }

  tape.BackToStart();
  tape.Show();

  State q_start; // 4
  State q_find_end; // 5
  State q_ret_to_l; // 6

  State q_start_shift; // 0
  State q_shift_0; // 1
  State q_shift_1; // 2
  State q_shift_l;  // 17
  State q_fin_shift; // 3

  State q_ret_to_l2; // 7
  State q_set_flag; // 8
  State q_go_right; // 9
  State q_find_num; // 10
  State q_add_0; // 11
  State q_add_1; // 12
  State q_shift_flag; // 13
  State q_plus; // 14
  State q_go_to_flag; // 15
  State q_fin; // 16
  State q_shift_flag0; // 18
  State q_shift_flag1; // 19

  State q_clean; // 20
  State q_cshift_0; // 21
  State q_cshift_1; // 22

  std::vector<State> arr;

  arr.push_back(q_start_shift);
  arr.push_back(q_shift_0);
  arr.push_back(q_shift_1);
  arr.push_back(q_fin_shift);
  arr.push_back(q_start);
  arr.push_back(q_find_end);
  arr.push_back(q_ret_to_l);
  arr.push_back(q_ret_to_l2);
  arr.push_back(q_set_flag);
  arr.push_back(q_go_right);
  arr.push_back(q_find_num);
  arr.push_back(q_add_0);
  arr.push_back(q_add_1);
  arr.push_back(q_shift_flag);
  arr.push_back(q_plus);
  arr.push_back(q_go_to_flag);
  arr.push_back(q_fin);
  arr.push_back(q_shift_l);
  arr.push_back(q_shift_flag0);
  arr.push_back(q_shift_flag1);
  arr.push_back(q_clean);
  arr.push_back(q_cshift_0);
  arr.push_back(q_cshift_1);

  arr[4].dict["#"] = Configuration(4, "#", 1);
  arr[4].dict["1"] = Configuration(5, "1", 1);
  arr[4].dict["0"] = Configuration(5, "0", 1);
  arr[5].dict["1"] = Configuration(5, "1", 1);
  arr[5].dict["0"] = Configuration(5, "0", 1);
  arr[5].dict["|"] = Configuration(5, "|", 1);
  arr[5].dict["#"] = Configuration(6, "#", -1);
  arr[6].dict["1"] = Configuration(6, "1", -1);
  arr[6].dict["0"] = Configuration(6, "0", -1);
  arr[6].dict["|"] = Configuration(0, "|", 1);
  
  
  arr[17].dict["1"] = Configuration(2, "|", 1);
  arr[17].dict["0"] = Configuration(1, "|", 1);
  arr[0].dict["1"] = Configuration(2, "#", 1);
  arr[0].dict["0"] = Configuration(1, "#", 1);
  arr[1].dict["0"] = Configuration(1, "0", 1);
  arr[1].dict["1"] = Configuration(2, "0", 1);
  arr[2].dict["0"] = Configuration(1, "1", 1);
  arr[2].dict["1"] = Configuration(2, "1", 1);
  arr[2].dict["#"] = Configuration(3, "1", 0);
  arr[1].dict["#"] = Configuration(3, "0", 0);
  arr[3].dict["1"] = Configuration(7, "1", -1);
  arr[3].dict["0"] = Configuration(7, "0", -1);
  arr[3].dict["#"] = Configuration(7, "1", -1);

  arr[7].dict["1"] = Configuration(7, "1", -1);
  arr[7].dict["0"] = Configuration(7, "0", -1);
  arr[7].dict["#"] = Configuration(7, "|", -1);
  arr[7].dict["|"] = Configuration(8, "#", 0);
  arr[8].dict["#"] = Configuration(9, "flag", 1);

  arr[9].dict["|"] = Configuration(9, "|", 1);
  arr[9].dict["1"] = Configuration(9, "1", 1);
  arr[9].dict["0"] = Configuration(9, "0", 1);
  arr[9].dict["#"] = Configuration(10, "#", -1);
  arr[10].dict["1"] = Configuration(12, "#", -1);
  arr[10].dict["0"] = Configuration(11, "#", -1);

  
  arr[12].dict["1"] = Configuration(12, "1", -1);
  arr[12].dict["0"] = Configuration(12, "0", -1);
  arr[11].dict["1"] = Configuration(11, "1", -1);
  arr[11].dict["0"] = Configuration(11, "0", -1);
  arr[12].dict["|"] = Configuration(12, "|", -1);
  arr[11].dict["|"] = Configuration(11, "|", -1);

  arr[11].dict["flag"] = Configuration(13, "#", -1);
  arr[13].dict["0"] = Configuration(18, "flag", 1);
  arr[18].dict["#"] = Configuration(9, "0", 1);
  arr[13].dict["#"] = Configuration(18, "flag", 1);
  arr[13].dict["1"] = Configuration(19, "flag", 1);
  arr[19].dict["#"] = Configuration(9, "1", 1);

  arr[12].dict["flag"] = Configuration(14, "flag", -1);
  arr[14].dict["0"] = Configuration(15, "1", 1);
  arr[14].dict["1"] = Configuration(14, "0", -1);
  arr[14].dict["#"] = Configuration(15, "1", 1);


  arr[15].dict["1"] = Configuration(15, "1", 1);
  arr[15].dict["0"] = Configuration(15, "0", 1);
  arr[15].dict["flag"] = Configuration(13, "#", -1);
  arr[10].dict["|"] = Configuration(20, "#", -1);
  // clean  
  arr[20].dict["0"] = Configuration(21, "|", -1);
  arr[20].dict["1"] = Configuration(22, "|", -1);
  arr[20].dict["flag"] = Configuration(16, "|", 0);
  arr[21].dict["0"] = Configuration(21, "0", -1);
  arr[21].dict["1"] = Configuration(22, "0", -1);
  arr[21].dict["flag"] = Configuration(16, "0", 0);
  arr[22].dict["0"] = Configuration(21, "1", -1);
  arr[22].dict["1"] = Configuration(22, "1", -1);
  arr[22].dict["flag"] = Configuration(16, "1", 0);

  TuringMachine app(tape, arr);
  app.Start(arr[4], arr[16]);
  app.Show();

  return 0;
}
