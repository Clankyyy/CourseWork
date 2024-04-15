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
      std::cout << "Произошла ошибка, повторите ввод, ";
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    } else {
      std::cout << "ОШИБКА!!!" << std::endl;
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
      std::cout << "Введите целое положительное число: ";
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
      continue;
    } else {
      std::cout << "ОШИБКА!!!" << std::endl;
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    }

    if (input < 1) {
      std::cout << "Пожалуйста, введите целое положительное число: ";
      continue;
    }
    return input;
  }
}

void fmt::MatrixConsoleFmt::Format(std::ostream& os) {
  if (matrix_ == nullptr) return;
  FindMaxWidth();
  for (auto& row : *matrix_) {
    os << "{";
    for (auto& num : row) {
      os << std::setw(max_width_) << num << ";";
    }
    os << "}" << std::endl;
  }
  if (swaps_ != 0 && comparisons_ != 0) {
    os << "сравнений: " << comparisons_ << " "
       << "замен: " << swaps_ << std::endl;
  }
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
      std::string num_str = std::to_string(num);
      size_t delim = num_str.find(",");
      size_t after_delim = num_str.find_first_of("123456789", delim + 1);

      size_t num_width = 0;
      if (after_delim != std::string::npos) {
        num_width = num_str.substr(0, after_delim + 2).size();
      } else {
        num_width = num_str.substr(0, delim).size();
      }
      if (max_width_ < num_width) max_width_ = num_width;
    }
  }
}
