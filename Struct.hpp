#include <iostream>
#include <vector>
#include <string>
#include <map> 

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
  Configuration(State* s, std::string data, int mov) : data(data), state(s), move(mov) {}
  std::string data; 
  State* state; 
  int move; 
};

struct Node {
  std::string data = "#";
  Node* next = nullptr;
  Node* prev = nullptr;
};

class Tape {
 public:
  Tape() {
    Node* new_node = new Node;
    new_node->data = "#";
    start = new_node;
    head = new_node;
  }
  Tape(std::string data) { // constructor from string
    Node* new_node = new Node;
    new_node->data = data;
    start = new_node;
    head = new_node;
  }
  Tape(size_t n, std::string data) { // constructor from string and number
    Node* new_node = new Node;
    new_node->data = data;
    start = new_node;
    head = new_node;
    for (size_t i = 1; i < n; ++i) {
      Node* new_node = new Node;
      new_node->data = data;
      head->next = new_node;
      new_node->prev = head;
      head = new_node;
    }
    head = start;
  }
  ~Tape() {
    while (start != nullptr) {
      Node* old_start = start;
      start = start->next;
      delete old_start;
    }
  }
  Tape& operator+=(int x) {
    if (x == -1) {
      Left();
    } else if (x == 1) {
      Right();
    }
    return *this;
  }
  void Right();
  void Left();
  void Set(std::string data);
  void BackToStart();
  std::string Look();
  void Show() const;
  void Start(Tape& tape, std::vector<State>& array, size_t id, size_t end); // not need?
  Node* head;
  Node* start;
};

void Tape::Right() {
  if (head->next == nullptr) {
    Node* new_node = new Node;
    head->next = new_node;
    new_node->prev = head;
  }
  head = head->next;
}

void Tape::Left() {
    if (head->prev == nullptr) {
    Node* new_node = new Node;
    head->prev = new_node;
    new_node->next = head;
    start = head;
  }
  head = head->prev;
}

void Tape::Set(std::string data) {
  head->data = data;
}

void Tape::BackToStart() {
  head = start;
}

std::string Tape::Look() {
  return head->data;
}

void Tape::Show() const {
  Node* first = start;
  while (first != nullptr) {
    if (first == head) {
      std::cout << "[" << first->data << "]";
    } else {
      std::cout << first->data << ";";
    }
    first = first->next;
  }
  std::cout << '\n';
}

void Tape::Start(Tape& tape, std::vector<State>& array, size_t id, size_t end) {
  Configuration new_config = array[id].dict[tape.Look()];
  tape.Set(new_config.data);
  tape += new_config.move;
  tape.Show();
  // std::cout << new_config.id << ' ' << new_config.data << ' ' << new_config.move << ' ' << tape.Look() << '\n';
  if (new_config.id != end) {
    Start(tape, array, new_config.id, end);
  } else {
    Configuration end_config = array[end].dict[tape.Look()];
    tape.Set(new_config.data);
  }
}

class TuringMachine {
 public:
  TuringMachine(Tape& t, std::vector<State>& s, std::map<State, size_t> d) : tape(t), states(s), dict_id(d) {}
  TuringMachine() {}
  TuringMachine(Tape& t) : tape(t) {}
  TuringMachine(Tape& t, std::vector<State>& s) : tape(t), states(s) {}
 private:
  Tape tape;
  std::vector<State> states;
  std::map<State, size_t> dict_id;
  std::vector<std::string> alphabet;
};
