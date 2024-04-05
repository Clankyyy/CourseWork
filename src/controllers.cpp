#include "controllers.h"

ModelController::ModelController(std::shared_ptr<ListModel>& model)
    : model_(model) {}



void ConsoleInputController::GetMatrix() {

  while (true) {
    try {
      // model_->Create();
      break;
    } catch (const std::invalid_argument&) {
      std::cout << "Не удалось создать матрицу: "  << std::endl;
    }
  }
}

void ConsoleInputController::Execute() { GetMatrix(); }

std::string ConsoleInputController::RelatedName() { return "Ввести матрицу"; }

void ExitController::Execute() { exit(EXIT_SUCCESS); }

std::string ExitController::RelatedName() { return "Завершить работу"; }

void ShowController::Execute() {
  // auto& persons = model_->GetData();
  // if (persons.size() == 0) {
  //   std::cout << "На данный момент матрица не задана" << std::endl;
  //   return;
  // }
  // for (const auto& person : persons) {
  //   //person->Show();
  // }
}

std::string ShowController::RelatedName() { return "Вывести матрицу"; }

void FileSystemController::GetAbsolutePath() {
  std::string path = "";
  std::string path_example = R"(C:\Users\UserName\Desktop\test.txt)";
  std::cout << "Введите абсолютный путь, например: " << path_example
            << std::endl
            << "Путь: ";
  std::getline(std::cin, path);
  path_ = path;
}

bool FileSystemController::IsPathConfirmed() {
  try {
    if (!IsPathExists()) return true;
  } catch (const std::exception&) {
    std::cout << "Недопустимое имя для файла" << std::endl;
    return false;
  }
  std::cout << std::endl
            << "Файл уже существует"
            << "Хотите перезаписать файл?" << std::endl;

  std::string input = "";
  while (true) {
    input = utils::get_string("Введите [д]/[н]: ");
    if (input == "д") {
      return true;
    } else if (input == "н") {
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
  if (!path_.is_absolute()) {
    std::cout << "Введённый путь не абсолютный" << std::endl << std::endl;
    return false;
  }
  if (path_.extension() != ".txt") {
    std::cout << "Программа поддерживает только файлы с расширением .txt"
              << std::endl
              << "Введенное расширение: " << path_.extension();
    return false;
  }
  return true;
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
    std::cout << "Не удалось открыть файл" << std::endl << std::endl;
  }
}

std::string ModelSerializeController::RelatedName() {
  return "Сохранить матрицу";
}

void ModelDeserializeController::GetPath() {
  do {
    GetAbsolutePath();
    try {
      if (IsPathExists()) {
        if (IsPathValid()) break;
      } else
        std::cout << "Указанный файл не существует" << std::endl;
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
    std::cout << "Не удалось добавить матрицу из файла, проверьте формат "
                 "данных в файле"
              << std::endl;
  }
}

std::string ModelDeserializeController::RelatedName() {
  return "Добавить матрицу из внешнего файла";
}

void ClearModelController::Execute() {
  if (model_->IsEmpty()) {
    std::cout << "Матрица не создана"
              << std::endl;
    return;
  }

  model_->Clear();
  std::cout << "Матрица была очищена"
            << std::endl;
}

std::string ClearModelController::RelatedName() {
  return "Очистить матрицу";
}
