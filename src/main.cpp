#include <filesystem>
#include <fmt/format.h>

#include <fstream>
#include <filesystem>
#include <random>
#include <string>

std::string getExecutableDir() {
  return std::filesystem::canonical("/proc/self/exe").parent_path();
}
std::string pickRandomQuote() {
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution<std::streamsize> distrib;
  using paramType = decltype(distrib)::param_type;

  std::string quote;
  std::filesystem::path path = getExecutableDir() + "/quotes.txt";
  if (std::ifstream file{path}) {
    std::streamsize linesRead = 0;
    std::string line;

    while (std::getline(file, line)) {
      // initially pick the first line as the selected line
      // replace the selected line with the second line with a probability of
      // 1/2 replace the selected line with the third line with a probability of
      // 1/3 etc.
      distrib.param(paramType(0, linesRead));
      ++linesRead;
      if (distrib(rng) == 0) {
        quote = line;
      }
    }
  } else {
    return "Couldnt open quotes.txt";
  }
  return quote;
}

int main() {

  fmt::print("{}", pickRandomQuote());

  return EXIT_SUCCESS;
}
