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
    auto pair = GetDimensions(ifs);
    m_cols = pair.first;
    m_rows = pair.second;
  } catch (const std::exception& e) {
    throw e;
  }
  if (m_cols < 1 || m_rows < 1) {
    throw std::invalid_argument("dimensions must be greater than 0");
  }

  Clear();
  matrix_->resize(m_rows, std::vector<double>(m_cols, 0));

  for (size_t i = 0; i < m_rows; i++) {
    for (size_t j = 0; j < m_cols; j++) {
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

void ListModel::FillMatrix(size_t cols, size_t rows, double min, double max) {
  matrix_->resize(rows, std::vector<double>(cols, 0));

  rnd::RandDouble double_gen{min, max};
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      matrix_->at(i).at(j) = double_gen();
    }
  }
}

void ListModel::Serialize(std::filesystem::path path) {
  std::ofstream ofs;
  ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
  try {
    ofs.open(path);
    ofs << matrix_->front().size() << " " << matrix_->size() << std::endl
        << std::endl;
  } catch (const std::exception& e) {
    ofs.close();
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

void ListModel::Clear() {
  for (auto& row : *matrix_) {
    row.clear();
  };
  matrix_->clear();
}

std::pair<size_t, size_t> ListModel::GetDimensions(std::ifstream& ifs) {
  std::string dimensions;
  std::getline(ifs, dimensions);
  std::vector<std::string> result;
  std::stringstream ss(dimensions);
  std::string token;
  while (std::getline(ss, token, ' ')) {
    if (!token.empty()) {
      result.push_back(token);
    }
  }

  if (result.size() != 2) {
    throw std::invalid_argument("");
  }

  size_t cols = std::stoi(result[0]);
  size_t rows = std::stoi(result[1]);

  return std::make_pair(cols, rows);
}
