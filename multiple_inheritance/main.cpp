#include <format>
#include <iostream>
#include <string>

int main() {
  using namespace std;
  struct Human {
    string name{};
    int age{};

    void getOld() { age += 1; };
  };

  struct Developer : /*virtual*/ Human {
    int experience{};

    void work() { cout << "I am fixing a bug." << endl; }
    void work(size_t bugNumber) const {
      cout << format("I am fixing item #{}.", bugNumber) << endl;
    }
  };
  
  struct Manager : /*virtual*/ Human {
    int personale{};

    void work() const { cout << "I am in a meeting." << endl; }
  };
  
  struct LeadDeveloper : Developer, Manager {
    using Developer::work;

    // hides bases work
    void work(int hours) const {
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
  // leadDev.getOld();
  leadDev.show();
}
