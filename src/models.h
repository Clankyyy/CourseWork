#pragma once
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>

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
  void FillMatrix(size_t cols, size_t rows);
  void Clear();

 private:
  matrix_ptr matrix_;
};
