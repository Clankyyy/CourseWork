#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

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
  void SetSettings(matrix_ptr m, int swaps, int comparisons);
  
 private:
  void FindMaxWidth();

  matrix_ptr matrix_;
  size_t max_width_;
  int swaps_;
  int comparisons_;
};
}  // namespace fmt
namespace utils {
std::string get_string(const std::string& msg);
int get_positive_int(const std::string& msg);
}  // namespace utils
