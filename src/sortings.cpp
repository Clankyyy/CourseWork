#include "sortings.h"

MatrixSortStrategy::MatrixSortStrategy(
    std::vector<std::vector<double>> matrix) {
  matrix_ = matrix;
  swaps_ = 0;
  comparisons_ = 0;
}

void MatrixSortStrategy::Sort() {
  Prepare();
  for (auto& v : matrix_) {
    ExecuteSort(v);
  }
}

void MatrixSortStrategy::Sort(std::vector<std::vector<double>> matrix) {
  matrix_ = matrix;
  Prepare();
  for (auto& v : matrix_) {
    ExecuteSort(v);
  }
}

matrix_ptr MatrixSortStrategy::matrix() const {
  return std::make_shared<std::vector<std::vector<double>>>(matrix_);
}

int MatrixSortStrategy::swaps() const { return swaps_; }

int MatrixSortStrategy::comparisons() const { return comparisons_; }

void BubbleSort::Sort() {
  Prepare();
  for (auto& v : matrix_) {
    ExecuteSort(v);
  }
}

std::string BubbleSort::RelatedName() { return "Сортировка пузырьком"; }

void BubbleSort::ExecuteSort(std::vector<double>& arr) {
  bool swapped = false;

  for (size_t i = 0; i < arr.size() - 1; i++) {
    swapped = false;
    for (size_t j = 0; j < arr.size() - i - 1; j++) {
      comparisons_++;
      if (fabs(arr[j]) < fabs(arr[j + 1])) {
        swaps_++;
        std::swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }

    if (swapped == false) break;
  }
}

void BubbleSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}

std::string InsertionSort::RelatedName() { return "Сортировка вставками"; }

void InsertionSort::ExecuteSort(std::vector<double>& arr) {
  for (size_t i = 1; i < arr.size(); i++) {
    // double key = arr[i];
    int j = i - 1;

    while (j >= 0) {
      comparisons_++;
      if (fabs(arr[j]) < fabs(arr[j + 1])) {
        std::swap(arr[j], arr[j + 1]);
        swaps_++;
        j--;
      } else {
        break;
      }
    }
  }
}

void InsertionSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}

std::string SelectionSort::RelatedName() { return "Сортировка выбором"; }

void SelectionSort::ExecuteSort(std::vector<double>& arr) {
  for (size_t i = 0; i < arr.size() - 1; i++) {
    size_t max = i;
    for (size_t j = i + 1; j < arr.size(); j++) {
      comparisons_++;
      if (fabs(arr[j]) > fabs(arr[max])) max = j;
    }

    if (max != i) {
      swaps_++;
      std::swap(arr[max], arr[i]);
    }
  }
}

void SelectionSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}

std::string QuickSort::RelatedName() { return "Быстрая сортировка"; }

void QuickSort::StartSort(std::vector<double>& arr, int low, int high) {
  if (arr.size() < 2 || low >= high) return;

  int pivot = Partition(arr, low, high);

  StartSort(arr, low, pivot - 1);

  StartSort(arr, pivot + 1, high);
}

int QuickSort::Partition(std::vector<double>& arr, int low, int high) {
  double pivot = arr[high];  // should be mid
  int i = low - 1;

  for (int j = low; j < high; j++) {
    comparisons_++;
    if (fabs(arr[j]) >= fabs(pivot)) {
      i++;
      std::swap(arr[i], arr[j]);
      swaps_++;
    }
  }
  std::swap(arr[i + 1], arr[high]);
  swaps_++;
  return i + 1;
}

void QuickSort::ExecuteSort(std::vector<double>& arr) {
  StartSort(arr, 0, arr.size() - 1);
}

void QuickSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}

std::string ShellSort::RelatedName() { return "Сортировка Шелла"; }

void ShellSort::ExecuteSort(std::vector<double>& arr) {
  for (size_t gap = arr.size() / 2; gap > 0; gap /= 2) {
    for (size_t i = gap; i < arr.size(); i += 1) {
      double temp = arr[i];

      size_t j = i;
      while (j >= gap) {
        comparisons_++;
        if (fabs(arr[j - gap]) < fabs(temp)) {
          arr[j] = arr[j - gap];
          swaps_++;
          j -= gap;
        } else {
          break;
        }
      }
      swaps_++;
      arr[j] = temp;
    }
  }
}

void ShellSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}
