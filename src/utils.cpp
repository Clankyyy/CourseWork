#include "utils.h"

std::string utils::get_string(const std::string& msg) {
  constexpr auto max_size = std::numeric_limits<std::streamsize>::max();
  std::string input = "";
  while (true) {
    std::cout << msg;
    if (std::cin >> input) {
      std::cin.ignore(max_size, '\n');
      break;
    } else if (std::cin.fail()) {
      std::cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ, "
                   "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ "
                   "пїЅпїЅпїЅпїЅ";
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    } else {
      std::cout
          << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ"
          << std::endl;
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    }
  }
  return input;
}

int utils::get_positive_int(const std::string& msg) {
  int input = 0;
  constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

  std::cout << msg;
  while (true) {
    if (std::cin >> input) {
      std::cin.ignore(max_size, '\n');
      std::cout << std::endl;
    } else if (std::cin.fail()) {
      std::cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅ "
                   "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ "
                   "пїЅпїЅпїЅпїЅпїЅ: ";
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
      continue;
    } else {
      std::cout
          << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ"
          << std::endl;
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    }

    if (input < 1) {
      std::cout << "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅ "
                   "пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ "
                   "пїЅпїЅпїЅпїЅпїЅ: ";
      continue;
    }
    return input;
  }
}

void fmt::MatrixConsoleFmt::Format(std::ostream& os) {
  if (matrix_ == nullptr) return;
  std::cout << std::setprecision(2);
  FindMaxWidth();
  for (auto& row : *matrix_) {
    os << "{";
    for (auto& num : row) {
      os << std::setw(max_width_) << num << ";";
    }
    os << "}" << std::endl;
  }
  os << "сравнений: " << comparisons_ << " "
     << "замен: " << swaps_ << std::endl;
}

void fmt::MatrixConsoleFmt::SetSettings(matrix_ptr m, int swaps,
                                        int comparisons) {
  swaps_ = swaps;
  comparisons_ = comparisons;
  matrix_ = m;
}

void fmt::MatrixConsoleFmt::FindMaxWidth() {
  for (auto& row : *matrix_) {
    for (auto& num : row) {
      std::string num_text = std::to_string(num);
      std::string num_strip = num_text.substr(0, num_text.find(",") + 3);
      size_t num_width = num_strip.size();
      //std::cout << num_strip << " ";
      if (max_width_ < num_width) max_width_ = num_width;
    }
  }
}
