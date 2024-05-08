#include "controllers.h"

ModelController::ModelController(std::shared_ptr<ListModel>& model)
    : model_(model) {}

void ExitController::Execute() { exit(EXIT_SUCCESS); }

std::string ExitController::RelatedName() { return "Выйти"; }

ShowController::ShowController(std::shared_ptr<ListModel>& model) {
  model_ = model;
  fmtr_ = std::make_unique<fmt::MatrixConsoleFmt>();
}

void ShowController::Execute() {
  matrix_ptr matrix = model_->GetData();
  if (matrix->empty()) {
    std::cout << "Матрица не задана" << std::endl;
    return;
  }

  fmtr_->SetSettings(matrix);
  fmtr_->Format(std::cout);
}

std::string ShowController::RelatedName() { return "Вывести исходную матрицу"; }

void FileSystemController::GetAbsolutePath() {
  std::string path = "";
  std::string path_example = R"(C:\Users\UserName\Desktop\test.txt)";
  std::cout << "Введите путь, например: " << path_example << std::endl
            << "Путь: ";
  std::getline(std::cin, path);
  path_ = path;
}

bool FileSystemController::IsPathConfirmed() {
  try {
    if (!IsPathExists()) return true;
  } catch (const std::exception&) {
    std::cout << "Недопустимое имя файла" << std::endl;
    return false;
  }
  std::cout
      << std::endl
      << "Такой файл уже существует, вы уверены что хотите перезаписать файл?"
      << std::endl;

  std::string input = "";
  while (true) {
    input = utils::get_string("Введите [да]/[нет]: ");
    if (input == "да") {
      return true;
    } else if (input == "нет") {
      return false;
    }
  }
}

bool FileSystemController::IsPathExists() const {
  bool exists = false;
  try {
    exists = std::filesystem::is_regular_file(path_);
  } catch (const std::exception& e) {
    throw e;
  }
  return exists;
}
void FileSystemController::GetPath() {
  do {
    GetAbsolutePath();
    if (IsPathValid()) {
      if (IsPathConfirmed()) break;
    }
  } while (true);
}

bool FileSystemController::IsPathValid() {
  if (path_.extension() != ".txt") {
    std::cout << "Программа поддерживает файлы с расширением .txt " << std::endl
              << "Указанное расширение: " << path_.extension();
    return false;
  }
  return true;
}

ModelSerializeController::ModelSerializeController(
    std::shared_ptr<ListModel>& model) {
  model_ = model;
}

void ModelSerializeController::Execute() {
  if (model_->IsEmpty()) {
    std::cout << "Матрица не задана, сохранение невозможно" << std::endl;
    return;
  }

  GetPath();

  try {
    model_->Serialize(path_);
  } catch (const std::exception&) {
    std::cout << "Неудалось открыть файл" << std::endl << std::endl;
  }
}

std::string ModelSerializeController::RelatedName() {
  return "Сохранить исходную матрицу в файл";
}

ModelDeserializeController::ModelDeserializeController(
    std::shared_ptr<ListModel>& model) {
  model_ = model;
}

void ModelDeserializeController::GetPath() {
  do {
    GetAbsolutePath();
    try {
      if (IsPathExists()) {
        if (IsPathValid()) break;
      } else
        std::cout << "Указаный файл не существует" << std::endl;
    } catch (...) {
      std::cout << "Недопустимое имя файла" << std::endl;
    }

  } while (true);
}

void ModelDeserializeController::Execute() {
  if (!model_->IsEmpty()) {
    std::cout << "Матрица уже задана, очистите, для того чтобы создать новую";
    return;
  }

  GetPath();

  try {
    model_->Deserialize(path_);
    std::cout << "Матрица добавлена" << std::endl;
  } catch (const std::exception&) {
    std::cout << "Не удалось добавить матрицу" << std::endl;
  }
}

std::string ModelDeserializeController::RelatedName() {
  return "Инициализировать матрицу из файла";
}

ClearModelController::ClearModelController(std::shared_ptr<ListModel>& model) {
  model_ = model;
}

void ClearModelController::Execute() {
  if (model_->IsEmpty()) {
    std::cout << "Матрица уже пуста" << std::endl;
    return;
  }

  model_->Clear();
  std::cout << "Матрица очищена" << std::endl;
}

std::string ClearModelController::RelatedName() { return "Очистить матрицу"; }

ModelSortController::ModelSortController(
    std::shared_ptr<ListModel>& model,
    std::shared_ptr<std::vector<std::shared_ptr<MatrixSortStrategy>>>
        sortings) {
  model_ = model;
  sortings_ = sortings;
  sortings_->push_back(std::make_shared<BubbleSort>(*model->GetData()));
  sortings_->push_back(std::make_shared<InsertionSort>(*model->GetData()));
  sortings_->push_back(std::make_shared<SelectionSort>(*model->GetData()));
  sortings_->push_back(std::make_shared<QuickSort>(*model->GetData()));
  sortings_->push_back(std::make_shared<ShellSort>(*model->GetData()));

  fmtr_ = std::make_shared<fmt::MatrixConsoleFmt>();
  stats_fmtr_ = std::make_unique<fmt::StatsTable>();
}

void ModelSortController::Execute() {
  matrix_ptr m = model_->GetData();
  if (m->empty()) {
    std::cout << "Матрица не задана, сортировка невозможна" << std::endl;
    return;
  }
  stats_fmtr_->Clear();
  StartSortings(m);
}

std::string ModelSortController::RelatedName() { return "Сортировать матрицу"; }

void ModelSortController::StartSortings(matrix_ptr m) {
  for (auto& s : *sortings_) {
    s->Sort(*m);
    std::string sort_name = s->RelatedName();
    std::cout << sort_name << ": " << std::endl;
    fmtr_->SetSettings(s->matrix());
    stats_fmtr_->AddInfo(sort_name, s->swaps(), s->comparisons());
    fmtr_->Format(std::cout);
  }
  stats_fmtr_->Format(std::cout);
}

SortingsSerializeController::SortingsSerializeController(
    std::shared_ptr<ListModel>& model,
    std::shared_ptr<std::vector<std::shared_ptr<MatrixSortStrategy>>>
        sortings) {
  model_ = model;
  sortings_ = sortings;
  fmtr_ = std::make_shared<fmt::MatrixConsoleFmt>();
  stats_fmtr_ = std::make_unique<fmt::StatsTable>();
}

void SortingsSerializeController::Execute() {
  if (IsSortingsEmpty()) {
    std::cout << "Матрица не была отсортирована, сохранение невозможно"
              << std::endl;
    return;
  }
  GetPath();
  Serialize();
}

std::string SortingsSerializeController::RelatedName() {
  return "Сохранить результат сортировок";
}

void SortingsSerializeController::Serialize() {
  std::ofstream ofs;
  ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
  try {
    ofs.open(path_);
    WriteStats(ofs);

  } catch (...) {
    std::cout << "Не удалось сохранить результаты сортировок в указанный файл"
              << std::endl;
  }
}

void SortingsSerializeController::WriteStats(std::ostream& os) {
  for (auto& s : *sortings_) {
    std::string sort_name = s->RelatedName();
    os << sort_name << ": " << std::endl;
    fmtr_->SetSettings(s->matrix());
    stats_fmtr_->AddInfo(sort_name, s->swaps(), s->comparisons());
    fmtr_->Format(os);
  }
  stats_fmtr_->Format(os);
}

bool SortingsSerializeController::IsSortingsEmpty() {
  if (sortings_->front()->comparisons() == 0 &&
      sortings_->front()->swaps() == 0) {
    return true;
  }
  return false;
}

FillRandomController::FillRandomController(std::shared_ptr<ListModel>& model) {
  model_ = model;
  fmtr_ = std::make_unique<fmt::MatrixConsoleFmt>();
}

void FillRandomController::Execute() {
  if (!model_->IsEmpty()) {
    std::cout << "Матрица уже задана, очистите, для того чтобы создать новую";
    return;
  }
  size_t cols =
      static_cast<size_t>(utils::get_positive_int("Введите число столбцов: "));
  size_t rows =
      static_cast<size_t>(utils::get_positive_int("Введите число строчек: "));
  double min = utils::get_double("Введите нижнюю границу: ");
  double max = utils::get_double("Введите верхнюю границу: ");
  if (min > max) {
    std::swap(min, max);
    std::cout << "Значения границ были переставлены!" << std::endl;
  }

  model_->FillMatrix(cols, rows, min, max);

  matrix_ptr new_matrix = model_->GetData();

  fmtr_->SetSettings(new_matrix);
  fmtr_->Format(std::cout);
}

std::string FillRandomController::RelatedName() {
  return "Заполнить матрицу случайными числами";
}

ConsoleInputController::ConsoleInputController(
    std::shared_ptr<ListModel>& model) {
  model_ = model;
  fmtr_ = std::make_unique<fmt::MatrixConsoleFmt>();
}

void ConsoleInputController::Execute() {
  if (!model_->IsEmpty()) {
    std::cout << "Очистите матрицу для ввода новой" << std::endl;
    return;
  }

  auto [cols, rows] = GetDimensions();
  std::vector<std::vector<double>> m(rows, std::vector<double>(cols));

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      std::cout << "Элемент " << i + 1 << " строку " << j + 1 << " столбец: ";
      m[i][j] = utils::get_double("");
    }
  }

  model_->Create(std::make_shared<matrix>(m));
}

std::string ConsoleInputController::RelatedName() {
  return "Ручной ввод матрицы";
}

std::pair<size_t, size_t> ConsoleInputController::GetDimensions() {
  size_t cols =
      static_cast<size_t>(utils::get_positive_int("Введите число столбцов: "));
  size_t rows =
      static_cast<size_t>(utils::get_positive_int("Введите число строчек: "));

  return std::make_pair(cols, rows);
}
