#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <thread>
using namespace std;

void bjDraw(int playerCard[2], int dealerCard[2], int &playerTotal,
            int &dealerTotal, mt19937 &seed) {

  uniform_int_distribution<int> card(2, 11);

  playerCard[0] = card(seed);
  playerCard[1] = card(seed);
  if (playerCard[0] == 11 && playerCard[1] == 11) {
    playerCard[0] = 1;
  }
  playerTotal = playerCard[0] + playerCard[1];
  dealerCard[0] = card(seed);
  dealerCard[1] = card(seed);
  if (dealerCard[0] == 11 && dealerCard[1] == 11) {
    dealerCard[0] = 1;
  }
  dealerTotal = dealerCard[0] + dealerCard[1];
}

void bjAction(int playerHit, int &playerTotal, mt19937 &seed, bool &fold,
              bool &playerBust, int playerCard[2]) {
  int menu = 0;
  uniform_int_distribution<int> card(2, 11);
  do {
    cout << "\nAction : \n 1. Hit \n 2. Fold \n 3. Stay \n";
    cin >> menu;
    switch (menu) {
    case 1:
      playerHit = card(seed);
      if (playerHit == 11 && playerTotal + 11 > 21) {
        playerHit = 1;
      }
      if (playerCard[0] == 11 && playerTotal + playerHit > 21) {
        playerCard[0] = 1;
        playerTotal = playerCard[1] + 1;
      }
      if (playerCard[1] == 11 && playerTotal + playerHit > 21) {
        playerCard[1] = 1;
        playerTotal = playerCard[0] + 1;
      }
      playerTotal += playerHit;
      cout << "\nYou Hit For " << playerHit << "\nTotal : " << playerTotal
           << "\n";
      break;

    case 2:
      fold = true;
      return;
    case 3:
      return;
    default:
      cout << "\nInvalid Choice\n";
      break;
    }
  } while (playerTotal < 21);
  if (playerTotal > 21) {
    playerBust = true;
  }
  return;
}

void blackJack(int balance, mt19937 seed) {
  int playerCard[2];
  int dealerCard[2];
  int playerTotal;
  int dealerTotal;
  int playerHit;
  int dealerHit;
  bool fold = false;
  bool playerBust = false;
  bool dealerBust = false;
  int bet;
  int menu;
  cout << "\nPlay BlackJack?\n1. Play\n2. Quit\n";
  cin >> menu;
  switch (menu) {
  case 1:
    cout << "\nMoney Left : " << balance << "\nInput Bet : ";
    cin >> bet;
    while (bet < 0 || bet > balance) {
      cout << "\nInvalid Bet\nMoney Left : " << balance << "\nInput Bet : ";
      cin >> bet;
    }
    bjDraw(playerCard, dealerCard, playerTotal, dealerTotal, seed);
    cout << "Your Hand : \n"
         << "1. " << playerCard[0] << "\n2. " << playerCard[1]
         << "\nTotal : " << playerTotal << "\nDealer Hand : \n"
         << "1. " << dealerCard[0] << "\n2. \n";
    bjAction(playerHit, playerTotal, seed, fold, playerBust, playerCard);
    cout << "\nDealer Hand : \n"
         << "1. " << dealerCard[0] << "\n2. " << dealerCard[1]
         << "\nTotal : " << dealerTotal << "\n";

    if (!fold && !playerBust) {
      while (dealerTotal <= 17) {
        uniform_int_distribution<int> card(2, 11);
        dealerHit = card(seed);
        if (dealerHit == 11 && dealerTotal + 11 > 21) {
          dealerHit = 1;
        }
        if (dealerCard[0] == 11 && dealerTotal + dealerHit > 21) {
          dealerCard[0] = 1;
          dealerTotal = dealerCard[1] + 1;
        }
        if (dealerCard[1] == 11 && dealerTotal + dealerHit > 21) {
          dealerCard[1] = 1;
          dealerTotal = dealerCard[1] + 1;
        }
        dealerTotal += dealerHit;
        cout << "\nDealer Hit For " << dealerHit << "\nTotal : " << dealerTotal
             << "\n";
      }
      if (dealerTotal > 21) {
        dealerBust = true;
      }
    }

    if (fold == 1) {
      cout << "\nYou Folded\n";
      bet = 0;
    } else if (playerBust == 1) {
      cout << "\nYou Busted\n";
      bet = 0;
    } else if (dealerBust == 1) {
      cout << "\nDealer Busted\n";
      balance += bet * 2;
    } else if (dealerTotal > playerTotal) {
      cout << "\nDealer Has The Bigger Hand\n";
      bet = 0;
    } else if (dealerTotal < playerTotal) {
      cout << "\nYou Have The Bigger Hand\n";
      balance += bet * 2;
    } else if (dealerTotal == playerTotal) {
      cout << "\nTie\n";
      balance += bet;
    }
    break;
  case 2:
    return;
    break;
  default:
    cout << "\nInvalid Choice\n";
    break;
  }
  return;
}

void slotMachine(int &balance, mt19937 &seed) {
  uniform_int_distribution<int> roll(1, 7);
  int number[3] = {0, 0, 0};
  int bet;
  int menu;
  cout << "Play Slot Machine? \n3 Same Numbers = 2×Bet\n2 Same Numbers = "
          "Money Back\n1. Play\n2. Quit\n";
  cin >> menu;
  switch (menu) {
  case 1:
    cout << "\nMoney Left : " << balance << "\nInput Bet : ";
    cin >> bet;
    while (bet < 0 || bet > balance) {
      cout << "\nInvalid Bet\nMoney Left : " << balance << "\nInput Bet : ";
      cin >> bet;
    }
    balance -= bet;
    cout << "\nBalance Now : " << balance << "\n";
    for (int a = 1; a <= 10; a++) {
      for (int a = 0; a <= 2; a++) {
        number[a] = roll(seed);
      }
      system("clear");
      for (int a = 0; a <= 2; a++) {
        cout << "| " << number[a] << " |";
      }
      cout << "\n";
      this_thread::sleep_for(chrono::milliseconds(600));
    }
    if (number[0] == number[1] && number[1] == number[2]) {
      balance += bet * 2;
      cout << "\nYou Doubled Your Money\nYour Balance Now : " << balance
           << "\n";
    } else if (number[0] == number[1] || number[0] == number[2] ||
               number[1] == number[2]) {
      balance += bet;
      cout << "\nYou Got Your Money Back\nYour Balance Now : " << balance
           << "\n";
    } else {
      cout << "\nYou Lost\n";
    }
    break;
  case 2:
    return;
  }
  return;
}

void drawBoard(int fakeBoard[5][5]) {
  cout << "\n";
  for (int a = 0; a <= 4; a++) {
    for (int b = 0; b <= 4; b++) {
      cout << "| " << fakeBoard[a][b] << " |";
    }
    cout << "\n";
  }
}

void setBoard(int board[5][5], int bombAmount, mt19937 &seed) {
  uniform_int_distribution<int> randomBomb(1, 5);
  int bombPlaced = 0;
  while (bombPlaced < bombAmount) {
    int bombRow = randomBomb(seed);
    int bombColumn = randomBomb(seed);
    if (board[bombRow - 1][bombColumn - 1] != 2) {
      board[bombRow - 1][bombColumn - 1] = 2;
      bombPlaced++;
    }
  }
  return;
}
void playerInput(int board[5][5], int fakeBoard[5][5], int &correctTile) {
  int column;
  int row;
  int menu = 0;
  while (menu != 2) {

    cout << "\nWhat Will You Do?\n1. Check A Tile\n2. Stop\n";
    cin >> menu;
    while (menu > 2 || menu < 1) {
      cout << "Invalid input. Try again.\n1. Check A Tile\n2. Stop\n";
      cin >> menu;
    }
    switch (menu) {
    case 1:
      cout << "\nInput Column(1-5) : ";
      cin >> column;
      cout << "Input Row(1-5) : ";
      cin >> row;
      if (column >= 1 && column <= 5 && row >= 1 && row <= 5 &&
          board[row - 1][column - 1] != 1) {
        if (board[row - 1][column - 1] != 2) {
          board[row - 1][column - 1] = 1;
          fakeBoard[row - 1][column - 1] = 1;
          correctTile++;
          cout << "\nCorrect Tile : " << correctTile << "\n";
        } else {
          cout << "\nYou Hit A Bomb\n";
          correctTile = 0;
          drawBoard(board);
          return;
        }
      } else if (column < 1 || column > 5 || row < 1 || row > 5 ||
                 board[row - 1][column - 1] == 1) {
        cout << "Invalid input Or Already Filled. Try again.\n";
      }
      drawBoard(fakeBoard);
      break;
    case 2:
      return;
    default:
      cout << "\nInvalid Input\n";
      break;
    }
  }
}

void mineSweeper(int &balance, mt19937 &seed) {
  int board[5][5] = {{0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0}};
  int fakeBoard[5][5] = {{0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};

  int bet;
  int menu;
  int correctTile = 0;
  int bombAmount;
  do {
    for (int a = 0; a <= 4; a++) {
      for (int b = 0; b <= 4; b++) {
        board[a][b] = 0;
        fakeBoard[a][b] = 0;
      }
    }
    correctTile = 0;
    cout << "Play MineSweeper? \n0 = Undiscovered Tile\n1 = Discovered Tile\n2 "
            "= Bomb\n1. Play\n2. Quit\n";
    cin >> menu;
    while (menu > 2 || menu < 1) {
      cout << "\nInvalid Option\n";
      cout << "Play MineSweeper? \n0 = Undiscovered Tile\n1 = Discovered "
              "Tile\nn1. Play\n2. Quit\n";
      cin >> menu;
    }
    switch (menu) {
    case 1:
      cout << "\nMoney Left : " << balance << "\nInput Bet : ";
      cin >> bet;
      while (bet < 0 || bet > balance) {
        cout << "\nInvalid Bet\nMoney Left : " << balance << "\nInput Bet : ";
        cin >> bet;
      };
      balance -= bet;
      cout << "\nBalance Now : " << balance << "\nHow Many Bombs? (3-5) : ";
      cin >> bombAmount;
      while (bombAmount > 5 || bombAmount < 3) {
        cout << "\nInvalid Number!\nHow Many Bombs (3-5) : ";
        cin >> bombAmount;
      };
      setBoard(board, bombAmount, seed);
      playerInput(board, fakeBoard, correctTile);
      bet = (bet / (8 - bombAmount)) * correctTile;
      cout << "\nYou Won " << bet << "\n";
      balance += bet;
      break;
    case 2:
      break;
    default:
      cout << "\nInvalid Choice\n";
      break;
    }
  } while (menu != 2);
}
void saveData(int balance, bool hasPlayed, string username) {
  ofstream outFile("data.txt");
  if (outFile.is_open()) {
    outFile << balance << " " << hasPlayed << "\n" << username;
    outFile.close();
    cout << "Data Written\n\n";
  } else {
    cout << "Data Write Failed\n\n";
  }
  return;
}

int main() {
  int menu;
  int balance = 1000;
  bool hasPlayed;
  string username;
  int bet;
  mt19937 seed(time(NULL));
  ifstream inFile("data.txt");
  if (inFile.is_open()) {
    inFile >> balance >> hasPlayed;
    getline(inFile, username);
    getline(inFile, username);
    inFile.close();
    cout << "Data Read\n\n";
  } else {
    cout << "Data Read Failed\n\n";
  }

  if (!hasPlayed) {
    cout << "What is Your Name : ";
    getline(cin, username);
    hasPlayed = true;
    saveData(balance, hasPlayed, username);
  }
  do {
    cout << "Hi! " << username << "\nMoney Left : " << balance
         << "\n1. Play\n2. Quit\n";
    cin >> menu;
    switch (menu) {
    case 1:
      do {
        cout << "\nWhich Game Do You Want To Play\n1. BlackJack\n2. Slot "
                "Machine\n3. Minesweeper\n4. Back\n ";
        cin >> menu;
        switch (menu) {
        case 1:
          blackJack(balance, seed);
          saveData(balance, hasPlayed, username);
          break;
        case 2:
          slotMachine(balance, seed);
          saveData(balance, hasPlayed, username);
          break;
        case 3:
          mineSweeper(balance, seed);
          saveData(balance, hasPlayed, username);
          break;
        case 4:
          cout << "";
          break;
        default:
          cout << "\nInvalid Choice\n";
          break;
        }
      } while (menu != 4);
    case 2:
      break;
    default:
      cout << "\nInvalid Choice\n";
      break;
    }

  } while (menu != 2);
  saveData(balance, hasPlayed, username);
}
