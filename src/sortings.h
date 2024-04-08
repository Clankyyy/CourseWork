#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using matrix_ptr = std::shared_ptr<std::vector<std::vector<double>>>;
class MatrixSortStrategy {
 public:
  MatrixSortStrategy(std::vector<std::vector<double>> matrix);
  virtual ~MatrixSortStrategy() = default;

  virtual void Sort();
  virtual void Sort(std::vector<std::vector<double>> matrix);

  matrix_ptr matrix() const;
  int swaps() const;
  int comparisons() const;

 protected:
  virtual void ExecuteSort(std::vector<double>& arr) = 0;
  virtual void Prepare() = 0;

  std::vector<std::vector<double>> matrix_;
  int swaps_;
  int comparisons_;
};

// best:???; worst, mid: O(n**2)
class BubbleSort final : public MatrixSortStrategy {
 public:
  using MatrixSortStrategy::MatrixSortStrategy;

  void Sort() override;

 private:
  void ExecuteSort(std::vector<double>& arr) override;
  void Prepare() override;
};

class InsertionSort final : public MatrixSortStrategy {
 public:
  using MatrixSortStrategy::MatrixSortStrategy;

 private:
  void ExecuteSort(std::vector<double>& arr) override;
  void Prepare() override;
};