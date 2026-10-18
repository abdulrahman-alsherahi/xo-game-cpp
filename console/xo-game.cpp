#include <iostream>
#include <limits>
using namespace std;

bool checkWin(char b[9]) {
    return
        (b[0]==b[1] && b[1]==b[2]) ||
        (b[3]==b[4] && b[4]==b[5]) ||
        (b[6]==b[7] && b[7]==b[8]) ||
        (b[0]==b[3] && b[3]==b[6]) ||
        (b[1]==b[4] && b[4]==b[7]) ||
        (b[2]==b[5] && b[5]==b[8]) ||
        (b[0]==b[4] && b[4]==b[8]) ||
        (b[2]==b[4] && b[4]==b[6]);
}

int main() {

    char board[9] = {'1','2','3','4','5','6','7','8','9'};
    char currentPlayer = 'X';

    for (int turn = 0; turn < 9; turn++) {

        cout << "\nAktueller Spieler: " << currentPlayer << "\n";
        cout << board[0] << " | " << board[1] << " | " << board[2] << "\n";
        cout << board[3] << " | " << board[4] << " | " << board[5] << "\n";
        cout << board[6] << " | " << board[7] << " | " << board[8] << "\n";

        int choice;

        while (true) {
            cout << "\nWähl eine Nummer von 1 bis 9: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Deine Wahl ist falsch\n";
            }
            else if (choice < 1 || choice > 9) {
                cout << "Deine Wahl ist falsch\n";
            }
            else if (board[choice - 1] == 'X' || board[choice - 1] == 'O') {
                cout << "Diese Box ist nicht frei!\n";
            }
            else {
                board[choice - 1] = currentPlayer;

                if (checkWin(board)) {
                    cout << "\nGewinner: " << currentPlayer << "!\n";
                    cout << board[0] << " | " << board[1] << " | " << board[2] << "\n";
                    cout << board[3] << " | " << board[4] << " | " << board[5] << "\n";
                    cout << board[6] << " | " << board[7] << " | " << board[8] << "\n";
                    return 0;
                }

                break;
            }
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
    }

    cout << "\nUnentschieden!\n";
    return 0;
}
