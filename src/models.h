#pragma once
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>

#include "utils.h"

using matrix = std::vector<std::vector<double>>;
using matrix_ptr = std::shared_ptr<matrix>;

class ListModel {
 public:
  ListModel();
  void Create(matrix_ptr m);
  matrix_ptr GetData();
  void Serialize(std::filesystem::path path);
  void Deserialize(std::filesystem::path path);
  bool IsEmpty();
  void FillMatrix(size_t cols, size_t rows, double min, double max);
  void Clear();

 private:
  std::pair<size_t, size_t> GetDimensions(std::ifstream &ifs);
  matrix_ptr matrix_;
};
