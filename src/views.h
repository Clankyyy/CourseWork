#pragma once

#include <Windows.h>

#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <unordered_map>

#include "controllers.h"

class View {
 public:
  virtual void Show() = 0;
};

class ConsoleView : public View {
 public:
  ConsoleView(std::vector<std::unique_ptr<Controller>> controllers);
  void Show() override;

 private:
  std::unordered_map<std::string, std::unique_ptr<Controller>>
      controllers_;  // to smart pointer

  void StartLoop();

  void SetOptions();
  void SetLocale();
  void ShowGreetings();
  void ShowMenu();
  void ChooseController();
};
