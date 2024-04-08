#include "src/controllers.h"
#include "src/models.h"
#include "src/sortings.h"
#include "src/views.h"

void StartApp() {
  std::shared_ptr<ListModel> model = std::make_shared<ListModel>();

  std::vector<std::unique_ptr<Controller>> controllers;
  // controllers.push_back(std::make_unique<ConsoleInputController>(model));
  // controllers.push_back(std::make_unique<ShowController>(model));
  // controllers.push_back(std::make_unique<ModelSerializeController>(model));
  // controllers.push_back(std::make_unique<ModelDeserializeController>(model));
  // controllers.push_back(std::make_unique<ClearModelController>(model));
  controllers.push_back(std::make_unique<ExitController>());

  ConsoleView view = ConsoleView(std::move(controllers));
  // view.Show();
}
void test() {
  StartApp();
  std::vector<std::vector<double>> m = {{4, 1, 3}, {-1, 5, 6}};
  fmt::MatrixConsoleFmt fmtr = fmt::MatrixConsoleFmt();
  MatrixSortStrategy *st = new InsertionSort(m);
  st->Sort();
  fmtr.SetSettings(st->matrix(), st->swaps(), st->comparisons());
  fmtr.Format(std::cout);
}
int main() { test(); }