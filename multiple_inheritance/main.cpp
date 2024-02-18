#include <format>
#include <iostream>
#include <string>

int main() {
  using namespace std;
  struct Human {
    string name{};
    int age{};
  };
  struct Developer : Human {
    int experience{};
    void talk() { cout << "I'm a developer." << endl; }
  };
  struct Manager : Human {
    int personale{};
    void talk() { cout << "I'm a manager." << endl; }
  };
  struct LeadDeveloper : Developer, Manager {
    using Developer::talk;
    void show() {
      cout << format("name = {}, age = {}, experience = {}, personale = {}",
                     Developer::name, this->Manager::age, experience, personale)
           << endl;
      talk();
    }
  };
  LeadDeveloper leadDev{"Steve Wozniak", 26, 13, "Steve Jobs", 20, 0};
  leadDev.show();
}
