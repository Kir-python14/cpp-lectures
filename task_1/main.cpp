#include <iomanip>
#include <iostream>

struct MinMax {
  int minimum;
  int maximum;
};

double Average(const int* temperatures, int size) {
  long long sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += temperatures[i];
  }
  return static_cast<double>(sum) / size;
}

MinMax FindMinMax(const int* temperatures, int size) {
  MinMax result{temperatures[0], temperatures[0]};
  for (int i = 1; i < size; ++i) {
    if (temperatures[i] < result.minimum) {
      result.minimum = temperatures[i];
    }
    if (temperatures[i] > result.maximum) {
      result.maximum = temperatures[i];
    }
  }
  return result;
}

int CountFrostDays(const int* temperatures, int size) {
  int count = 0;
  for (int i = 0; i < size; ++i) {
    if (temperatures[i] < 0) {
      ++count;
    }
  }
  return count;
}

int main() {
  int size = 0;
  if (!(std::cin >> size) || size <= 0) {
    return 1;
  }

  int* temperatures = new int[size];
  for (int i = 0; i < size; ++i) {
    if (!(std::cin >> temperatures[i])) {
      delete[] temperatures;
      return 1;
    }
  }

  double average = Average(temperatures, size);
  MinMax extremes = FindMinMax(temperatures, size);
  int frost_days = CountFrostDays(temperatures, size);

  std::cout << std::fixed << std::setprecision(1) << average << '\n';
  std::cout << extremes.minimum << ' ' << extremes.maximum << '\n';
  std::cout << frost_days << '\n';

  delete[] temperatures;
}
