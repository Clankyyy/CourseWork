#include "models.h"

ListModel::ListModel() { matrix_ = std::make_shared<matrix>(); }

void ListModel::Create(matrix_ptr m) { matrix_ = m; }

matrix_ptr ListModel::GetData() { return std::make_shared<matrix>(*matrix_); }

void ListModel::Deserialize(std::filesystem::path path) {
  std::ifstream ifs;
  ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);

  size_t m_cols = 0;
  size_t m_rows = 0;

  try {
    ifs.open(path);
    ifs >> m_cols;
    ifs >> m_rows;
  } catch (const std::exception& e) {
    throw e;
  }

  matrix_->resize(m_cols, std::vector<double>(m_rows, 0));

  for (size_t i = 0; i < m_cols; i++) {
    for (size_t j = 0; j < m_rows; j++) {
      try {
        double tmp = 0;
        ifs >> tmp;
        matrix_->at(i).at(j) = tmp;
      } catch (const std::exception& e) {
        ifs.close();
        throw e;
      }
    }
  }
  ifs.close();
}

bool ListModel::IsEmpty() { return matrix_->empty(); }

void ListModel::Serialize(std::filesystem::path path) {
  std::ofstream ofs;
  ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
  try {
    ofs.open(path);
    std::cout << std::filesystem::is_regular_file(path);
  } catch (const std::exception& e) {
    throw e;
  }

  try {
    ofs << matrix_->size() << matrix_->front().size() << std::endl << std::endl;
  } catch (const std::exception& e) {
    throw e;
  }

  for (const auto& row : *matrix_) {
    for (const auto& num : row) {
      ofs << num << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}

void ListModel::Clear() { matrix_->clear(); }
