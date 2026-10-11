#include <iomanip>
#include <iostream>
#include <limits>

struct Source {
  int height;
  int width;
  char type;
  void* pixels;
};

int main() {
  // Импорт изображений разных размеров из двух форматов и расчёт яркости.
  // int*** images хранит изображения -> строки -> целочисленные пиксели.
  // Размеры задаются при вводе, поэтому фиксированный трёхмерный массив
  // не подходит. Каждое изображение и каждая его строка выделяются отдельно.
  // void* в Source хранит сырой буфер int[] или char[]: формат известен
  // только после ввода. Все буферы сохраняются в общей таблице источников,
  // затем приводятся к типу по метке и преобразуются в целые яркости.

  const int cMaxBrightness = 255;
  const int cMiddleBrightness = 127;
  int image_count = 0;
  if (!(std::cin >> image_count) || image_count <= 0) {
    std::cout << "error\n";
    return 1;
  }

  Source* sources = new Source[image_count]{};
  int*** images = new int** [image_count] {};
  bool input_ok = true;

  for (int i = 0; i < image_count && input_ok; ++i) {
    Source& source = sources[i];
    if (!(std::cin >> source.height >> source.width >> source.type) ||
        source.height <= 0 || source.width <= 0 ||
        source.height > std::numeric_limits<int>::max() / source.width ||
        (source.type != 'I' && source.type != 'C')) {
      input_ok = false;
      break;
    }

    int pixel_count = source.height * source.width;
    if (source.type == 'I') {
      source.pixels = new int[pixel_count];
      int* values = static_cast<int*>(source.pixels);
      for (int j = 0; j < pixel_count; ++j) {
        if (!(std::cin >> values[j]) || values[j] < 0 ||
            values[j] > cMaxBrightness) {
          input_ok = false;
          break;
        }
      }
    } else {
      source.pixels = new char[pixel_count];
      char* symbols = static_cast<char*>(source.pixels);
      for (int j = 0; j < pixel_count; ++j) {
        if (!(std::cin >> symbols[j]) ||
            (symbols[j] != '.' && symbols[j] != '+' && symbols[j] != '#')) {
          input_ok = false;
          break;
        }
      }
    }
  }

  if (input_ok) {
    std::cout << std::fixed << std::setprecision(1);
    for (int i = 0; i < image_count; ++i) {
      const Source& source = sources[i];
      images[i] = new int*[source.height];
      long long sum = 0;

      for (int y = 0; y < source.height; ++y) {
        images[i][y] = new int[source.width];
        for (int x = 0; x < source.width; ++x) {
          int index = y * source.width + x;
          if (source.type == 'I') {
            images[i][y][x] = static_cast<const int*>(source.pixels)[index];
          } else {
            char symbol = static_cast<const char*>(source.pixels)[index];
            if (symbol == '.') {
              images[i][y][x] = 0;
            } else if (symbol == '+') {
              images[i][y][x] = cMiddleBrightness;
            } else {
              images[i][y][x] = cMaxBrightness;
            }
          }
        }
      }

      for (int y = 0; y < source.height; ++y) {
        for (int x = 0; x < source.width; ++x) {
          sum += images[i][y][x];
        }
      }
      double average =
          static_cast<double>(sum) / (source.height * source.width);
      std::cout << i + 1 << ' ' << average << '\n';
    }
  } else {
    std::cout << "error\n";
  }

  for (int i = 0; i < image_count; ++i) {
    if (images[i] != nullptr) {
      for (int y = 0; y < sources[i].height; ++y) {
        delete[] images[i][y];
      }
      delete[] images[i];
    }
    if (sources[i].type == 'I') {
      delete[] static_cast<int*>(sources[i].pixels);
    } else if (sources[i].type == 'C') {
      delete[] static_cast<char*>(sources[i].pixels);
    }
  }
  delete[] images;
  delete[] sources;
  return input_ok ? 0 : 1;
}
