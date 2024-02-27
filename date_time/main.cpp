#include <chrono>
#include <format>
#include <iomanip>
#include <iostream>
#include <ratio>

int main() {
  using namespace std;

  auto var1 = 1.f / 3.f;
  auto var2 = 1.f / 3.f;
  cout << format("1/3 + 1/3 = {:3.10f}", var1 + var2) << endl;

  using third = ratio<12, 36>;
  using result1 = ratio_add<third, third>::type;
  cout << format("1/3 + 1/3 = {}/{}", result1::num, result1::den) << endl;

  using result2 = ratio_multiply<kilo, milli>;
  cout << format("ratio_multiply<kilo, milli> = {}/{}", result2::num,
                 result2::den)
       << endl;

  chrono::duration<intmax_t, ratio<1, 1'000>> mSecs{1'000'000};
  cout << format("is mSecs 1'000ms? {}", mSecs == chrono::milliseconds{1'000})
       << endl;
  cout << format("is mSecs 1'000s? {}", mSecs == chrono::seconds{1'000})
       << endl;

  chrono::duration<intmax_t> i1s{1};
  chrono::duration<intmax_t, milli> i1ms{1};
  cout << format("is i1s / 1'000 same as i1ms? {}", (i1s / 1'000) == i1ms)
       << endl;

  chrono::duration<double> d1s{1.};
  chrono::duration<double, milli> d1ms{1.};
  cout << format("is d1s / 1'000 same as d1ms? {}", (d1s / 1'000) == d1ms)
       << endl;

  using namespace chrono_literals;

  chrono::minutes oneHour{1h};
  // chrono::hours oneMin{1min};
  cout << format("one hour is {}", oneHour) << endl;

  // Cpp 20 Calendar
  // chrono::days oneWeek{7d};
  // chrono::day fourYear{4y};

  // each clock consists of a timepoint and a duration
  // each timepoint is associated with a clock
  // std::chrono::steady_clock::time_point =
  // std::chrono::time_point<std::chrono::steady_clock>
  // 1979
  chrono::steady_clock::time_point tp2{chrono::years{9}};
  // timepoints only have a relative meaning
  chrono::time_point<chrono::system_clock, chrono::seconds> tp1{
      chrono::floor<chrono::seconds>(chrono::system_clock::now())};
  auto nextWeek{tp1 + chrono::days{7}};
  cout << format("next week is {}", nextWeek) << endl;

  // Cpp 20
  chrono::sys_days dec_21_2012{chrono::round<chrono::days>(
      chrono::years{42} + chrono::months{11} + chrono::days{21})};
  cout << format("the world was ending at {}", dec_21_2012) << endl;

  // Cpp 20 Time of Day
  auto alarm{7h + 50min + 30s};
  chrono::hh_mm_ss tod{alarm};
  cout << format("alarm is at {}, {} after midnight", tod, alarm) << endl;

  // Cpp Calander
  chrono::year_month_day startTheSteal{2020y, chrono::November, 3d};
  chrono::year_month_day stopTheSteal{2021y / chrono::January / 6d};
  chrono::year_month_day today{
      // what is the difference between this floor and the first one?
      chrono::floor<chrono::days>(chrono::system_clock::now())};
  cout << format("from {} to {}", startTheSteal, stopTheSteal) << endl;

  chrono::month_weekday_last charshanbeSoori{chrono::December /
                                             chrono::Wednesday[chrono::last]};
  cout << format("celebrate fire on {}",
                 chrono::year_month_day{2022y / charshanbeSoori})
       << endl;

  // Cpp 20 timezone
  // in bash run timedatectl list-timezones
  const auto &tzList{chrono::get_tzdb_list()};
  for (auto itr{tzList.cbegin()}; itr != tzList.cend(); advance(itr, 1)) {
    cout << format("{}", itr->current_zone()->name()) << endl;
  }

  const auto &tzdb{chrono::get_tzdb()};
  initializer_list<const chrono::time_zone *> locations{
      tzdb.locate_zone("Asia/Tehran"), tzdb.locate_zone("America/Chicago"),
      tzdb.locate_zone("Antarctica/South_Pole")};
  for (auto &&zone : locations) {
    chrono::zoned_time overThere{zone, chrono::system_clock::now()};
    cout << format("time in {} is {}", zone->name(), overThere.get_local_time())
         << endl;
  }
}
