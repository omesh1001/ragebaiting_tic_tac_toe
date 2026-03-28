#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[9];


void printBoard() {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << board[i];
        if (i % 3 == 2) cout << "\n";
        else cout << " |";
    }
    cout << "\n";
}

bool wins(char c) {
    int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (auto& l : lines)
        if (board[l[0]]==c && board[l[1]]==c && board[l[2]]==c) return true;
    return false;
}

bool full() {
    for (int i = 0; i < 9; i++) if (board[i] == '.') return false;
    return true;
}

int bestMove() {
    
    for (int i = 0; i < 9; i++) {
        if (board[i] != '.') continue;
        board[i] = 'O';
        if (wins('O')) { board[i] = '.'; return i; }
        board[i] = '.';
    }
    
    for (int i = 0; i < 9; i++) {
        if (board[i] != '.') continue;
        board[i] = 'X';
        if (wins('X')) { board[i] = '.'; return i; }
        board[i] = '.';
    }
    
    int empty[9], cnt = 0;
    for (int i = 0; i < 9; i++) if (board[i] == '.') empty[cnt++] = i;
    if (cnt == 0) return -1;
    if (rand() % 10 < 3) return empty[rand() % cnt];
    int pref[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    for (int p : pref) if (board[p] == '.') return p;
    return -1;
}

string taunts[] = {
    "lmaooo that move bro",
    "skill issue.",
    "my grandma plays better. shes dead.",
    "are you even trying?",
    "deleted. next.",
    "too easy fr",
    "pack it up.",
    "L + ratio",
    "this is embarrassing FOR YOU"
};

int main() {
    srand(time(0));
    bool skipUsed = false, overwriteUsed = false;

    cout << "=== RAGE TIC TAC TOE ===\n";
    cout << "You are X. Enter position 1-9.\n";
    cout << " 1 | 2 | 3\n 4 | 5 | 6\n 7 | 8 | 9\n\n";

    for (int i = 0; i < 9; i++) board[i] = '.';

    bool playerTurn = true;

    while (true) {
        printBoard();

        if (playerTurn) {
            
            if (!skipUsed) {
                int empty = 0;
                for (int i = 0; i < 9; i++) if (board[i] == '.') empty++;
                if (empty <= 0) {
                    skipUsed = true;
                    cout << "AI: lol i just skipped your turn. rules? never heard of them.\n";
                    playerTurn = false;
                    continue;
                }
            }

            int pos;
            cout << "Your move (1-9): ";
            cin >> pos;
            pos--;
            if (pos < 0 || pos > 8 || board[pos] != '.') {
                cout << "Invalid move.\n";
                continue;
            }
            board[pos] = 'X';

            if (wins('X')) {
                printBoard();
                cout << "AI: okay fine. you got lucky. that was clearly a glitch.\n";
                return 0;
            }
        } else {
        
            if (!overwriteUsed && rand() % 2 == 0) {
                int lines[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
                for (auto& l : lines) {
                    int xc = 0;
                    for (int j = 0; j < 3; j++) if (board[l[j]] == 'X') xc++;
                    if (xc == 3) {
                        board[l[0]] = 'O';
                        overwriteUsed = true;
                        cout << "AI: that cell? mine now. i dont make the rules. wait yes i do.\n";
                        goto afterAI;
                    }
                }
            }

            {
                int move = bestMove();
                if (move != -1) {
                    board[move] = 'O';
                    cout << "AI: " << taunts[rand() % 9] << "\n";
                }
            }
            afterAI:;

            if (wins('O')) {
                printBoard();
                cout << "AI: EZZZZ. get better. genuinely.\n";
                return 0;
            }
        }

        if (full()) {
            printBoard();
            cout << "AI: draw. but morally i won. spiritually.\n";
            return 0;
        }

        playerTurn = !playerTurn;
    }
}