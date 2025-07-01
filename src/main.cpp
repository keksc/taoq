#include <filesystem>

#include <filesystem>
#include <fstream>
#include <print>
#include <random>
#include <string>

std::string pickRandomQuote() {
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution<std::streamsize> distrib;
  using paramType = decltype(distrib)::param_type;

  std::string quote;
  std::filesystem::path path = std::getenv("HOME");
  path += "/quotes.txt";
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
    return "";
  }
  return quote;
}

int main() {
  std::println("{}", pickRandomQuote());
  return EXIT_SUCCESS;
}
