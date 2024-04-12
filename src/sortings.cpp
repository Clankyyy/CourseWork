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

void BubbleSort::ExecuteSort(std::vector<double>& arr) {
  for (size_t i = 0; i < arr.size() - 1; i++) {
    for (size_t j = 0; j < arr.size() - i - 1; j++) {
      comparisons_++;
      if (fabs(arr[j]) < fabs(arr[j + 1])) {
        std::swap(arr[j], arr[j + 1]);
        swaps_++;
      }
    }
  }
}

void BubbleSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}

void InsertionSort::ExecuteSort(std::vector<double>& arr) {
  for (int i = 1; i < arr.size(); i++) {
    // double key = arr[i];
    int j = i - 1;

    while (j >= 0 && fabs(arr[j]) < fabs(arr[j + 1])) {
      std::swap(arr[j], arr[j + 1]);
      swaps_++;
      j--;
    }
  }
}

void InsertionSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}

void SelectionSort::ExecuteSort(std::vector<double>& arr) {
  for (size_t i = 0; i < arr.size() - 1; i++) {
    size_t min = i;
    for (size_t j = i + 1; j < arr.size(); j++) {
      comparisons_++;
      if (fabs(arr[j]) > fabs(arr[min])) min = j;
    }

    if (min != i) {
      swaps_++;
      std::swap(arr[min], arr[i]);
    }
  }
}

void SelectionSort::Prepare() {
  swaps_ = 0;
  comparisons_ = 0;
}

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
