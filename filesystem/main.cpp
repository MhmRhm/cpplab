#include <filesystem>
#include <format>
#include <iostream>

int main() {
  using namespace std;
  // Cpp 17
  using namespace std::filesystem;

  path address{current_path()};
  cout << format("current_path(): {}", address.string()) << endl;

  address /= R"(sub)";
  address += R"(dir)";
  address.append(R"(repo)");
  address.concat(R"(sitory)");
  address /= R"(script.sh)";
  cout << address << endl;

  cout << format("path.extension(): {}", address.extension().string()) << endl;
  cout << format("path.stem(): {}", address.stem().string()) << endl;
  cout << format("path.filename(): {}", address.filename().string()) << endl;
  cout << format("path.is_absolute(): {}", address.is_absolute()) << endl;
  cout << format("path.is_relative(): {}", address.is_relative()) << endl;
  cout << format("path.parent_path(): {}", address.parent_path().string())
       << endl;
  cout << format("path.root_directory(): {}", address.root_directory().string())
       << endl;
  cout << format("path.root_name(): {}", address.root_name().string()) << endl;
  cout << format("path.root_path(): {}", address.root_path().string()) << endl;

  for (auto &&component : address) {
    cout << component << endl;
  }

  directory_entry entry = directory_entry{address.parent_path()};
  cout << format("entry.is_directory(): {}", entry.is_directory()) << endl;
  cout << format("entry.exists(): {}", entry.exists()) << endl;
  create_directories(entry.path()); // Recursive
  entry.refresh();
  cout << format("entry.exists(): {}", entry.exists()) << endl;
  cout << format("space(): {} GB", space(R"(/)").available / 1024 / 1024 / 1024)
       << endl;

  entry = directory_entry{R"(/dev/cdrom)"};
  cout << format("entry.is_block_file(): {}", entry.is_block_file()) << endl;
  entry = directory_entry{R"(/dev/stdin)"};
  cout << format("entry.is_symlink(): {}", entry.is_symlink()) << endl;
  entry = directory_entry{R"(filesystem)"};
  cout << format("entry.file_size(): {} Bytes", entry.file_size()) << endl;

  for (auto entry{recursive_directory_iterator{current_path()}};
       entry != recursive_directory_iterator{}; advance(entry, 1)) {
    cout << format("{0:->{1}}{2}", "", entry.depth() * 4 + 2,
                   entry->path().filename().string())
         << endl;
  }
}
