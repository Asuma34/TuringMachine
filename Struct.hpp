#include <iostream>
#include <vector>
#include <string>
#include <map> 
#include "Tape.hpp"

struct Configuration; 
 
struct State {
  inline static size_t counter = 0;
  State() : id(counter) {
    ++counter;
  } 
  size_t id; 
  std::map<std::string, Configuration> dict; 
}; 
 
struct Configuration {
  Configuration() = default;
  Configuration(size_t next, std::string data, int mov) : data(data), id(next), move(mov) {}
  std::string data; 
  size_t id; 
  int move; 
};

class TuringMachine {
 public:
  TuringMachine(Tape& t, std::vector<State>& s) : tape(t), states(s) {
    alphabet.push_back("#");
    alphabet.push_back("0");
    alphabet.push_back("1");
  }
  TuringMachine() {
    alphabet.push_back("#");
    alphabet.push_back("0");
    alphabet.push_back("1");
  }
  TuringMachine(Tape& t) : tape(t) {
    alphabet.push_back("#");
    alphabet.push_back("0");
    alphabet.push_back("1");
  }
  TuringMachine(Tape& t, std::vector<State>& s, std::vector<std::string> alph) : tape(t), alphabet(alph), states(s) {}
  void Show() const;
  void Start(State& s, State& f);
  Tape& GetTape();
 private:
  Tape tape;
  std::vector<std::string> alphabet;
  std::vector<State> states;
  //std::map<State, size_t> dict_id;
  //std::map<std::string, State> dict;
  State start;
  State fin;
  void Step(Configuration);
};

void TuringMachine::Show() const {
  tape.Show();
}

void TuringMachine::Start(State& s, State& f) {
  start = s;
  fin = f;
  Step(start.dict[tape.Look()]);
}

void TuringMachine::Step(Configuration config) {
  tape.Set(config.data);
  tape += config.move;
  while (states[config.id].id != fin.id) {
    tape.Show();
    config = states[config.id].dict[tape.Look()];  
    tape.Set(config.data);
    tape += config.move;
  }
}
Tape& TuringMachine::GetTape() {
  return tape;
}
