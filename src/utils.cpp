#include "utils.h"

std::string utils::get_string(const std::string& msg) {
  constexpr auto max_size = (std::numeric_limits<std::streamsize>::max)();
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
  constexpr auto max_size = (std::numeric_limits<std::streamsize>::max)();

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
  os << std::endl;
}

void fmt::MatrixConsoleFmt::SetSettings(matrix_ptr m) { matrix_ = m; }

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

fmt::StatsTable::StatsTable() {
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  GetConsoleScreenBufferInfo(h, &csb_info);
}

void fmt::StatsTable::Format(std::ostream& os) {
  size_t name_width = FindMaxNameWidth();
  auto [swaps_index, comparisons_index] = FindIndexes();

  PrintTemplate(os);
  for (size_t i = 0; i < names_.size(); i++) {
    os.setf(std::ios::left);
    os << std::setw(name_width) << names_[i] << "|";
    os.unsetf(std::ios::left);

    if (i == swaps_index) {
      ChangeColor();
      os << std::setw(5) << stats_[i].first;
      ResetColor();
    } else {
      os << std::setw(5) << stats_[i].first;
    }
    os << "|";

    if (i == comparisons_index) {
      ChangeColor();
      os << std::setw(9) << stats_[i].second;
      ResetColor();
    } else {
      os << std::setw(9) << stats_[i].second;
    }
    os << "|";

    os << std::endl;
  }
}

void fmt::StatsTable::AddInfo(std::string name, int swaps, int comparisons) {
  names_.push_back(name);
  stats_.push_back(std::make_pair(swaps, comparisons));
}

std::pair<size_t, size_t> fmt::StatsTable::FindIndexes() {
  size_t min_swaps_index = 0;
  size_t min_comparisons_index = 0;
  int min_swaps = stats_[0].first;
  int min_comparisons = stats_[0].second;
  for (size_t i = 0; i < stats_.size(); i++) {
    if (stats_[i].first < min_swaps) {
      min_swaps = stats_[i].first;
      min_swaps_index = i;
    }
    if (stats_[i].second < min_comparisons) {
      min_comparisons = stats_[i].second;
      min_comparisons_index = i;
    }
  }

  return std::make_pair(min_swaps_index, min_comparisons_index);
}

void fmt::StatsTable::ChangeColor() {
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(h, FOREGROUND_GREEN);
}

void fmt::StatsTable::ResetColor() {
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  SetConsoleTextAttribute(h, csb_info.wAttributes);
}

void fmt::StatsTable::PrintTemplate(std::ostream& os) {
  size_t name_width = FindMaxNameWidth();
  std::string swaps = "замен";
  std::string comparisons = "сравнений";
  os << std::setw(name_width) << "сортировка"
     << "|";
  os << std::setw(swaps.size()) << swaps << "|";
  os << std::setw(comparisons.size()) << comparisons << "|" << std::endl;
}

size_t fmt::StatsTable::FindMaxNameWidth() {
  size_t max = 0;
  for (auto& name : names_) {
    if (name.size() > max) max = name.size();
  }

  return max;
}
