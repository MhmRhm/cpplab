#include <cstdint>
#include <format>
#include <iostream>

int main() {
  using namespace std;
  struct Human {
    const char *name{};
    int age{};

    void getOld() { age += 1; };
  };

  struct Developer : /*virtual*/ Human {
    int experience{};

    void work() const { cout << "I am fixing a bug." << endl; }
    void work(unsigned long int bugNumber) const {
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

    void show() const {
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

  struct Memory {
    uint64_t qwords[sizeof(LeadDeveloper) / 8]{};
  };
  cout << format("sizeof(Memory) = {}, sizeof(LeadDeveloper) = {}",
                 sizeof(Memory), sizeof(LeadDeveloper))
       << endl;
  static_assert(sizeof(Memory) == sizeof(LeadDeveloper),
                "Memory must be of the same size as LeadDeveloper.");

  // Cpp 20 bit_cat
  cout << "is LeadDeveloper trivially copyable: "
       << is_trivially_copyable_v<LeadDeveloper> << endl;
  Memory memory{bit_cast<Memory>(leadDev)};

  cout << format("&Developer::name = {:0X}",
                 reinterpret_cast<uint64_t>(leadDev.Developer::name))
       << endl;
  cout << format("&Manager::name = {:0X}",
                 reinterpret_cast<uint64_t>(leadDev.Manager::name))
       << endl;
  for (auto &&qw : memory.qwords) {
    cout << format("{:016X}", qw) << endl;
  }
}
