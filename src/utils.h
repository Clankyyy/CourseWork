#pragma once
#include <stdio.h>
#include <windows.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "conio.h"

namespace fmt {

using matrix_ptr = std::shared_ptr<std::vector<std::vector<double>>>;
class MatrixFormater {
 public:
  virtual void Format(std::ostream& os) = 0;
  virtual ~MatrixFormater() = default;
};

class MatrixConsoleFmt : public MatrixFormater {
 public:
  MatrixConsoleFmt() = default;

  virtual void Format(std::ostream& os) override;
  void SetSettings(matrix_ptr m);

 private:
  void FindMaxWidth();

  matrix_ptr matrix_;
  size_t max_width_;
};

class StatsTable {
 public:
  StatsTable();
  void Format(std::ostream& os);
  void AddInfo(std::string name, int swaps, int comparisons);

 private:
  std::pair<size_t, size_t> FindIndexes();
  void ChangeColor();
  void ResetColor();
  void PrintTemplate(std::ostream& os);
  size_t FindMaxNameWidth();

  CONSOLE_SCREEN_BUFFER_INFO csb_info;
  std::vector<std::string> names_;
  std::vector<std::pair<int, int>> stats_;
};

}  // namespace fmt
namespace utils {
std::string get_string(const std::string& msg);
int get_positive_int(const std::string& msg);
}  // namespace utils
