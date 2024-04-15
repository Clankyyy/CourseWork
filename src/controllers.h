#pragma once
#include <filesystem>
#include <iostream>
#include <string>

#include "models.h"
#include "utils.h"

class Controller {
 public:
  Controller() = default;
  virtual void Execute() = 0;  // Naming still sucks. Maybe Handle better?
  virtual std::string RelatedName() = 0;
  virtual ~Controller() = default;
};

class ModelController : public Controller {
 public:
  ModelController() = default;
  ModelController(std::shared_ptr<ListModel>& model);

  virtual ~ModelController() = default;

 protected:
  std::shared_ptr<ListModel> model_;
};

class FileSystemController : public ModelController {
 public:
  using ModelController::ModelController;
  virtual std::string RelatedName() = 0;
  virtual void Execute() = 0;

 protected:
  virtual void GetPath();
  bool IsPathValid();
  bool IsPathExists() const;
  void GetAbsolutePath();
  bool IsPathConfirmed();
  std::filesystem::path path_;
};

class ModelDeserializeController : public FileSystemController {
 public:
  ModelDeserializeController(std::shared_ptr<ListModel>& model);
  void GetPath() override;
  void Execute() override;
  std::string RelatedName() override;
};

class ModelSerializeController : public FileSystemController {
 public:
  using FileSystemController::FileSystemController;
  void Execute() override;
  std::string RelatedName() override;
  ~ModelSerializeController() = default;
};

class ShowController : public ModelController {
 public:
  ShowController(std::shared_ptr<ListModel>& model);
  void Execute() override;
  std::string RelatedName() override;

 private:
  std::unique_ptr<fmt::MatrixConsoleFmt> fmtr_;
};

class ClearModelController : public ModelController {
 public:
  using ModelController::ModelController;
  void Execute() override;
  std::string RelatedName() override;
};

class ExitController : public Controller {
 public:
  ExitController() = default;
  void Execute() override;
  std::string RelatedName() override;
};

class ConsoleInputController : public ModelController {
 public:
  using ModelController::ModelController;
  void Execute() override;
  std::string RelatedName() override;

 private:
  void GetMatrix();
};