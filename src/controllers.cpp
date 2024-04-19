#include "controllers.h"

ModelController::ModelController(std::shared_ptr<ListModel>& model)
    : model_(model) {}

void ConsoleInputController::GetMatrix() {
  while (true) {
    try {
      // model_->Create();
      break;
    } catch (const std::invalid_argument&) {
      std::cout << "Не удалось создать матрицу" << std::endl;
    }
  }
}

void ConsoleInputController::Execute() { GetMatrix(); }

std::string ConsoleInputController::RelatedName() { return "Ввести матрицу"; }

void ExitController::Execute() { exit(EXIT_SUCCESS); }

std::string ExitController::RelatedName() { return "Выйти"; }

// ShowController::ShowController(std::shared_ptr<ListModel>& model) {
//   model = model_;
//   fmtr_ = std::make_unique<fmt::MatrixConsoleFmt>();
// }

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
  std::cout << "Введите путь, например" << path_example << std::endl
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
              << "Указанное расширение: .txt" << path_.extension();
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
  return "Сохранить матрицу в файл";
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
