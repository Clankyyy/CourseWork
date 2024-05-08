#pragma once
#include <filesystem>
#include <iostream>
#include <string>

#include "models.h"
#include "sortings.h"
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

class SortingsSerializeController : public FileSystemController {
 public:
  SortingsSerializeController(
      std::shared_ptr<ListModel>& model,
      std::shared_ptr<std::vector<std::shared_ptr<MatrixSortStrategy>>>
          sortings);
  void Execute() override;
  std::string RelatedName() override;

 private:
  void Serialize();
  bool IsSortingsEmpty();
  void WriteStats(std::ostream& os);
  std::unique_ptr<fmt::StatsTable> stats_fmtr_;
  std::shared_ptr<std::vector<std::shared_ptr<MatrixSortStrategy>>> sortings_;
  std::shared_ptr<fmt::MatrixConsoleFmt> fmtr_;
};

class ModelSortController : public ModelController {
 public:
  ModelSortController(
      std::shared_ptr<ListModel>& model,
      std::shared_ptr<std::vector<std::shared_ptr<MatrixSortStrategy>>>
          sortings);
  void Execute() override;
  std::string RelatedName() override;

 private:
  void StartSortings(matrix_ptr m);

  std::unique_ptr<fmt::StatsTable> stats_fmtr_;
  std::shared_ptr<std::vector<std::shared_ptr<MatrixSortStrategy>>> sortings_;
  std::shared_ptr<fmt::MatrixConsoleFmt> fmtr_;
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
  ModelSerializeController(std::shared_ptr<ListModel>& model);
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

class FillRandomController : public ModelController {
 public:
  FillRandomController(std::shared_ptr<ListModel>& model);
  void Execute() override;
  std::string RelatedName() override;

 private:
  std::unique_ptr<fmt::MatrixConsoleFmt> fmtr_;
};

class ConsoleInputController : public ModelController {
 public:
  ConsoleInputController(std::shared_ptr<ListModel>& model);
  void Execute() override;
  std::string RelatedName() override;

 private:
  std::pair<size_t, size_t> GetDimensions();
  std::unique_ptr<fmt::MatrixConsoleFmt> fmtr_;
};

class ClearModelController : public ModelController {
 public:
  ClearModelController(std::shared_ptr<ListModel>& model);
  void Execute() override;
  std::string RelatedName() override;
};

class ExitController : public Controller {
 public:
  ExitController() = default;
  void Execute() override;
  std::string RelatedName() override;
};