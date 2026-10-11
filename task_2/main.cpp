#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

void Deposit(long long& balance) {
  long long amount = 0;
  if (!(std::cin >> amount)) {
    std::cin.clear();
    std::cout << "error\n";
    return;
  }
  if (amount <= 0 || amount > std::numeric_limits<long long>::max() - balance) {
    std::cout << "error\n";
    return;
  }
  balance += amount;
}

void Withdraw(long long& balance) {
  long long amount = 0;
  if (!(std::cin >> amount)) {
    std::cin.clear();
    std::cout << "error\n";
    return;
  }
  if (amount <= 0 || amount > balance) {
    std::cout << "error\n";
    return;
  }
  balance -= amount;
}

void PrintBalance(long long& balance) { std::cout << balance << '\n'; }

void Reset(long long& balance) { balance = 0; }

void Increment(long long& balance) {
  if (balance == std::numeric_limits<long long>::max()) {
    std::cout << "error\n";
    return;
  }
  ++balance;
}

struct Command {
  const char* name;
  void (*operation)(long long&);
};

int main() {
  const int cCommandSize = 64;
  const Command commands[] = {{"deposit", Deposit},
                              {"withdraw", Withdraw},
                              {"balance", PrintBalance},
                              {"reset", Reset},
                              {"inc", Increment}};
  const int cCommandCount = sizeof(commands) / sizeof(commands[0]);

  long long balance = 0;
  char command[cCommandSize] = {};
  while (std::cin >> std::setw(cCommandSize) >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }

    bool found = false;
    for (int i = 0; i < cCommandCount; ++i) {
      if (std::strcmp(command, commands[i].name) == 0) {
        commands[i].operation(balance);
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "error\n";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
