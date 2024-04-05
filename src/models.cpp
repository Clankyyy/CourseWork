#include "models.h"

ListModel::ListModel() {}

void ListModel::Create(matrix_ptr m) {
  matrix_ = m;
}


matrix_ptr ListModel::GetData() { return matrix_; }

void ListModel::Deserialize(std::filesystem::path path) {
  std::ifstream ifs;
  ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);

  int students_count = 0;

  try {
    ifs.open(path);
    ifs >> students_count;
  } catch (const std::exception& e) {
    throw e;
  }

  for (int i = 0; i < students_count; i++) {
    try {
      //Create(surname, address, faculty, study_year);
    } catch (const std::invalid_argument& e) {
      // ifs.close();
      throw e;
    } catch (const std::exception& e) {
      ifs.close();
      throw e;
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
    for(const auto& num : row){
      ofs << num << " ";
    }
    ofs << std::endl;
  }
  ofs.close();
}

void ListModel::Clear() { matrix_->clear(); }
