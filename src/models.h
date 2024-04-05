#pragma once
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>

#include "student.h"

using matrix_ptr = std::shared_ptr<std::vector<std::vector<double>>>;
class ListModel {
 public:
  ListModel();
  void Create(matrix_ptr m);
  matrix_ptr GetData();
  void Serialize(std::filesystem::path path);
  void Deserialize(std::filesystem::path path);
  bool IsEmpty();
  void Clear();

 private:
  matrix_ptr matrix_;
};
