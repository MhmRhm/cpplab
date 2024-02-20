add_executable(modules translation_unit.cpp main.cpp)
target_sources(modules
  PUBLIC
    FILE_SET CXX_MODULES FILES
      tlp.cppm
)

Format(modules .)
