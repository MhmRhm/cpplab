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
    void work() { cout << "I am fixing a bug." << endl; }
    void work(size_t bugNumber) {
      cout << format("I am fixing item #{}.", bugNumber) << endl;
    }
  };
  struct Manager : Human {
    int personale{};
    void work() { cout << "I am in a meeting." << endl; }
  };
  struct LeadDeveloper : Developer, Manager {
    using Developer::work;
    void work(int hours) {
      cout << format("Codign and having meetings for {} hours.", hours) << endl;
    }
    void show() {
      cout << format("name = {}, age = {}, experience = {}, personale = {}",
                     Developer::name, this->Manager::age, experience, personale)
           << endl;
      work();
      work(6);
      work(6UL);
    }
  };
  LeadDeveloper leadDev{"Steve Wozniak", 26, 13, "Steve Jobs", 20, 1};
  leadDev.show();
}
