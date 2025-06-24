#include <fmt/format.h>

#include <fstream>
#include <random>
#include <string>

std::string getExecutableDir() {
  std::ifstream exe("/proc/self/exe");
  if (!exe.is_open()) {
    return "";
  }
  // /proc/self/exe is a symlink, so read its target
  char buffer[1024];
  exe.read(buffer, sizeof(buffer) - 1);
  std::streamsize len = exe.gcount();
  if (len <= 0) {
    return "";
  }
  buffer[len] = '\0';
  // Find the last '/' to get the directory
  std::string path(buffer);
  std::size_t last_slash = path.find_last_of('/');
  if (last_slash == std::string::npos) {
    return "";
  }
  return path.substr(0, last_slash);
}
std::string pickRandomQuote() {
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution<std::streamsize> distrib;
  using paramType = decltype(distrib)::param_type;

  std::string quote;
  if (std::ifstream file{getExecutableDir() + "quotes.txt"}) {
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
