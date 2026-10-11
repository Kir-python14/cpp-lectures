#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

const int cRows = 5;
const int cColumns = 10;

bool IsInside(int x, int y) {
  return x >= 0 && x < cColumns && y >= 0 && y < cRows;
}

void Clear(char board[][cColumns]) {
  for (int y = 0; y < cRows; ++y) {
    for (int x = 0; x < cColumns; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool Put(char board[][cColumns], int x, int y, char symbol) {
  if (!IsInside(x, y)) {
    return false;
  }
  board[y][x] = symbol;
  return true;
}

bool Text(char board[][cColumns], int x, int y, const char* word) {
  int length = static_cast<int>(std::strlen(word));
  if (!IsInside(x, y) || length > cColumns - x) {
    return false;
  }
  for (int i = 0; i < length; ++i) {
    Put(board, x + i, y, word[i]);
  }
  return true;
}

void Print(const char board[][cColumns]) {
  for (int y = 0; y < cRows; ++y) {
    for (int x = 0; x < cColumns; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

int main() {
  const int cCommandSize = 64;
  const int cWordSize = cColumns + 2;
  char board[cRows][cColumns];
  Clear(board);

  char command[cCommandSize] = {};
  while (std::cin >> std::setw(cCommandSize) >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }
    if (std::strcmp(command, "clear") == 0) {
      Clear(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x = 0;
      int y = 0;
      char symbol = '\0';
      if (!(std::cin >> x >> y >> symbol)) {
        return 1;
      }
      if (!Put(board, x, y, symbol)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x = 0;
      int y = 0;
      char word[cWordSize] = {};
      if (!(std::cin >> x >> y >> std::setw(cWordSize) >> word)) {
        return 1;
      }
      if (!Text(board, x, y, word)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "print") == 0) {
      Print(board);
    } else {
      std::cout << "error\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
