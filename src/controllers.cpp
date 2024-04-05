#include "controllers.h"

ModelController::ModelController(std::shared_ptr<ListModel>& model)
    : model_(model) {}



void ConsoleInputController::GetMatrix() {

  while (true) {
    try {
      // model_->Create();
      break;
    } catch (const std::invalid_argument&) {
      std::cout << "�� ������� ������� �������: "  << std::endl;
    }
  }
}

void ConsoleInputController::Execute() { GetMatrix(); }

std::string ConsoleInputController::RelatedName() { return "������ �������"; }

void ExitController::Execute() { exit(EXIT_SUCCESS); }

std::string ExitController::RelatedName() { return "��������� ������"; }

void ShowController::Execute() {
  // auto& persons = model_->GetData();
  // if (persons.size() == 0) {
  //   std::cout << "�� ������ ������ ������� �� ������" << std::endl;
  //   return;
  // }
  // for (const auto& person : persons) {
  //   //person->Show();
  // }
}

std::string ShowController::RelatedName() { return "������� �������"; }

void FileSystemController::GetAbsolutePath() {
  std::string path = "";
  std::string path_example = R"(C:\Users\UserName\Desktop\test.txt)";
  std::cout << "������� ���������� ����, ��������: " << path_example
            << std::endl
            << "����: ";
  std::getline(std::cin, path);
  path_ = path;
}

bool FileSystemController::IsPathConfirmed() {
  try {
    if (!IsPathExists()) return true;
  } catch (const std::exception&) {
    std::cout << "������������ ��� ��� �����" << std::endl;
    return false;
  }
  std::cout << std::endl
            << "���� ��� ����������"
            << "������ ������������ ����?" << std::endl;

  std::string input = "";
  while (true) {
    input = utils::get_string("������� [�]/[�]: ");
    if (input == "�") {
      return true;
    } else if (input == "�") {
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
    std::cout << "�������� ���� �� ����������" << std::endl << std::endl;
    return false;
  }
  if (path_.extension() != ".txt") {
    std::cout << "��������� ������������ ������ ����� � ����������� .txt"
              << std::endl
              << "��������� ����������: " << path_.extension();
    return false;
  }
  return true;
}

void ModelSerializeController::Execute() {
  if (model_->IsEmpty()) {
    std::cout << "������� �� ������, ���������� ����������" << std::endl;
    return;
  }

  GetPath();

  try {
    model_->Serialize(path_);
  } catch (const std::exception&) {
    std::cout << "�� ������� ������� ����" << std::endl << std::endl;
  }
}

std::string ModelSerializeController::RelatedName() {
  return "��������� �������";
}

void ModelDeserializeController::GetPath() {
  do {
    GetAbsolutePath();
    try {
      if (IsPathExists()) {
        if (IsPathValid()) break;
      } else
        std::cout << "��������� ���� �� ����������" << std::endl;
    } catch (...) {
      std::cout << "������������ ��� �����" << std::endl;
    }

  } while (true);
}

void ModelDeserializeController::Execute() {
  GetPath();

  try {
    model_->Deserialize(path_);
    std::cout << "������� ���������" << std::endl;
  } catch (const std::exception&) {
    std::cout << "�� ������� �������� ������� �� �����, ��������� ������ "
                 "������ � �����"
              << std::endl;
  }
}

std::string ModelDeserializeController::RelatedName() {
  return "�������� ������� �� �������� �����";
}

void ClearModelController::Execute() {
  if (model_->IsEmpty()) {
    std::cout << "������� �� �������"
              << std::endl;
    return;
  }

  model_->Clear();
  std::cout << "������� ���� �������"
            << std::endl;
}

std::string ClearModelController::RelatedName() {
  return "�������� �������";
}
