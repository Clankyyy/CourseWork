#include "controllers.h"

ModelController::ModelController(std::shared_ptr<ListModel>& model)
    : model_(model) {}

void ConsoleInputController::GetMatrix() {
  while (true) {
    try {
      // model_->Create();
      break;
    } catch (const std::invalid_argument&) {
      std::cout << "�� ������� ������� �������" << std::endl;
    }
  }
}

void ConsoleInputController::Execute() { GetMatrix(); }

std::string ConsoleInputController::RelatedName() { return "������ �������"; }

void ExitController::Execute() { exit(EXIT_SUCCESS); }

std::string ExitController::RelatedName() { return "�����"; }

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
    std::cout << "������� �� ������" << std::endl;
    return;
  }

  fmtr_->SetSettings(matrix);
  fmtr_->Format(std::cout);
}

std::string ShowController::RelatedName() { return "������� �������� �������"; }

void FileSystemController::GetAbsolutePath() {
  std::string path = "";
  std::string path_example = R"(C:\Users\UserName\Desktop\test.txt)";
  std::cout << "������� ����, ��������" << path_example << std::endl
            << "����: ";
  std::getline(std::cin, path);
  path_ = path;
}

bool FileSystemController::IsPathConfirmed() {
  try {
    if (!IsPathExists()) return true;
  } catch (const std::exception&) {
    std::cout << "������������ ��� �����" << std::endl;
    return false;
  }
  std::cout
      << std::endl
      << "����� ���� ��� ����������, �� ������� ��� ������ ������������ ����?"
      << std::endl;

  std::string input = "";
  while (true) {
    input = utils::get_string("������� [��]/[���]: ");
    if (input == "��") {
      return true;
    } else if (input == "���") {
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
    std::cout << "��������� ������������ ����� � ����������� .txt " << std::endl
              << "��������� ����������: .txt" << path_.extension();
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
    std::cout << "������� �� ������, ���������� ����������" << std::endl;
    return;
  }

  GetPath();

  try {
    model_->Serialize(path_);
  } catch (const std::exception&) {
    std::cout << "��������� ������� ����" << std::endl << std::endl;
  }
}

std::string ModelSerializeController::RelatedName() {
  return "��������� ������� � ����";
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
        std::cout << "�������� ���� �� ����������" << std::endl;
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
    std::cout << "�� ������� �������� �������" << std::endl;
  }
}

std::string ModelDeserializeController::RelatedName() {
  return "���������������� ������� �� �����";
}

ClearModelController::ClearModelController(std::shared_ptr<ListModel>& model) {
  model_ = model;
}

void ClearModelController::Execute() {
  if (model_->IsEmpty()) {
    std::cout << "������� ��� �����" << std::endl;
    return;
  }

  model_->Clear();
  std::cout << "������� �������" << std::endl;
}

std::string ClearModelController::RelatedName() { return "�������� �������"; }

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
    std::cout << "������� �� ������, ���������� ����������" << std::endl;
    return;
  }
  StartSortings(m);
}

std::string ModelSortController::RelatedName() { return "����������� �������"; }

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
