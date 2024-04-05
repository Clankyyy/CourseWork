#include "views.h"

ConsoleView::ConsoleView(std::vector<std::unique_ptr<Controller>> controllers) {
  for (size_t i = 0; i < controllers.size(); i++) {
    this->controllers_[std::to_string(i + 1)] = std::move(controllers[i]);
  }
  this->SetOptions();
}

void ConsoleView::Show() { this->StartLoop(); }

void ConsoleView::ChooseController() {
  std::string choice = "";

  while (true) {
    ShowMenu();
    constexpr auto max_size = (std::numeric_limits<std::streamsize>::max)();
    std::cout << "Выберите действие: ";
    std::cin >> choice;
    std::cout << std::endl;

    if (controllers_.find(choice) == controllers_.end()) {
      std::cout << "Пункта меню с идентификатором: " << choice
                << " не существует" << std::endl;
      std::cin.ignore(max_size, '\n');
      continue;
    } else
      std::cin.ignore(max_size, '\n');
    controllers_[choice]->Execute();
  }
}
void ConsoleView::StartLoop() { ChooseController(); }

void ConsoleView::SetOptions() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  SetLocale();
  ShowGreetings();
}
void ConsoleView::SetLocale() { setlocale(LC_ALL, "RU"); }

void ConsoleView::ShowGreetings() {
  std::string name = "Кузнецов Марк";
  std::string info = "";
  std::string task =
      "";

  std::cout << name << std::endl
            << info << std::endl
            << task << std::endl
            << std::endl;
}

void ConsoleView::ShowMenu() {
  std::cout << std::endl;
  for (const auto& [k, v] : controllers_)
    std::cout << k << ". " << v->RelatedName() << std::endl;
  std::cout << std::endl;
}
