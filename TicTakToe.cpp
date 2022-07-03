#include<bits/stdc++.h>
using namespace std;
vector<vector<char>> board;

void setBoard(vector<vector<char>> &board) {
    for (int i = 0; i < 3; i++) {
        vector<char> b;
        b.push_back(' ');
        b.push_back(' ');
        b.push_back(' ');
        board.push_back(b);
    }
}

void showBoard(vector<vector<char>> &board) {
    system("cls");
    cout << "\n+---+---+---+" << endl;
    cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
    cout << "+---+---+---+" << endl;
    cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
    cout << "+---+---+---+" << endl;
    cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
    cout << "+---+---+---+" << endl;
}

pair<int, int> checkNextWinning(vector<vector<char>> &board, char s) {
    pair<int, int> p = make_pair(-1, -1);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0) {
				if (board[i][0] == ' ' and board[i][1] == s and board[i][2] == s)
					p = make_pair(i, 0);
            }
			if (j == 1) {
				if (board[i][0] == s and board[i][1] == ' ' and board[i][2] == s)
					p = make_pair(i, 1);
			}
			if (j == 2) {
				if (board[i][0] == s and board[i][1] == s and board[i][2] == ' ')
					p = make_pair(i, 2);
			}
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0) {
				if (board[0][i] == ' ' and board[1][i] == s and board[2][i] == s)
					p = make_pair(0, i);
            }
			if (j == 1) {
				if (board[0][i] == s and board[1][i] == ' ' and board[2][i] == s)
					p = make_pair(1, i);
			}
			if (j == 2) {
				if (board[0][i] == s and board[1][i] == s and board[2][i] == ' ')
					p = make_pair(2, i);
			}
        }
    }
    for (int i = 0; i < 3; i++) {
		if (i == 0) {
			if (board[0][0] == ' ' and board[1][1] == s and board[2][2] == s)
				p = make_pair(0, 0);
		} 
		else if (i == 1) {
			if (board[0][0] == s and board[1][1] == ' ' and board[2][2] == s)
				p = make_pair(1, 1);
		} 
		else if (i == 2) {
			if (board[0][0] == s and board[1][1] == s and board[2][2] == ' ')
				p = make_pair(2, 2);
		}
    }
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			if (board[0][2] == ' ' and board[1][1] == s and board[2][0] == s)
				p = make_pair(0, 2);
		}
		else if (i == 1) {
			if (board[0][2] == s and board[1][1] == ' ' and board[2][0] == s)
				p = make_pair(1, 1);
		} 
		else if (i == 2) {
			if (board[0][2] == s and board[1][1] == s and board[2][0] == ' ')
				p = make_pair(2, 0);
		}
    }
	return p;
}

bool isManCorner(vector<vector<char>> &board) {
    return (board[0][0] == 'X' or board[0][2] == 'X' or board[2][0] == 'X' or board[2][2] == 'X');
}

bool isManSide(vector<vector<char>> &board) {
    return (board[0][1] == 'X' or board[1][0] == 'X' or board[2][1] == 'X' or board[1][2] == 'X');
}

pair<int, int> GiveWinSidePos(vector<vector<char>> &board) {
    pair<int, int> p;
	if (board[1][0] == ' ' and board[1][2] == ' ')
		p = make_pair(1,0);
    else
        p = make_pair(0,1);
    return p;
}

pair<int, int> FirstEmpty(vector<vector<char>> &board) {
    pair<int, int> p = make_pair(-1, -1);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				p = make_pair(i,j);
				break;
			}
		}
	}
	return p;
}

bool CheckValidInput(vector<vector<char>> &board, int i, int j) {
	return (i > 0 and j > 0 and i <= 3 and j <= 3 and board[i - 1][j - 1] == ' ');
}

void CornerMovePlay(vector<vector<char>> &board, int &ct) {
	while (ct < 9) {
		ct += 1;
		if (ct % 2 == 1) {
			cout << "\n Enter Your Move : ";
			int x, y;
			cin >> x >> y;
			while (!CheckValidInput(board, x, y)) {
                cout << "\n Enter a valid input! ";
                cin >> x >> y;
            }
            board[x - 1][y - 1] = 'X';
        }
        else if (ct / 2 == 1) {
            board[1][1] = 'O';
        }
        else if (ct / 2 == 2) {
            pair<int, int> p = checkNextWinning(board, 'X');
            if (p.first == -1 and p.second == -1) {
                if (isManCorner(board)) {
                    board[0][1] = 'O';
                } 
                else {
                    p = GiveWinSidePos(board);
                    board[p.first][p.second] = 'O';
                }
            } 
            else {
                board[p.first][p.second] = 'O';
            }
        } 
        else if (ct / 2 == 3 or ct / 2 == 4) {
            pair<int, int> p = checkNextWinning(board, 'O');
            if (p.first == -1 and p.second == -1) {
                p = checkNextWinning(board, 'X');
                if (p.first == -1 and p.second == -1) {
                    p = FirstEmpty(board);
                    board[p.first][p.second] = 'O';
                } 
                else {
                    board[p.first][p.second] = 'O';
                }
            } 
            else {
                board[p.first][p.second] = 'O';
                showBoard(board);
                cout << "\nComputer Wins! " << endl;
                return;
            }
        }
        showBoard(board);
    }
    cout << "\nMatch Draw! " << endl;
}

void CenterMovePlay(vector<vector<char>> &board, int &ct) {
	while (ct < 9) {
		ct += 1;
		if (ct % 2 == 1) {
			cout << "\n Enter Your Move : ";
			int x, y;
			cin >> x >> y;
			while (!CheckValidInput(board, x, y)) {
                cout << "\n Enter a valid input! ";
                cin >> x >> y;
            }
            board[x - 1][y - 1] = 'X';
        } 
        else if (ct / 2 == 1) {
            board[0][0] = 'O';
        } 
        else if (ct / 2 == 2) {
            if (board[2][2] == 'X') {
				board[2][0] = 'O';
            } 
            else {
                pair<int, int> p = checkNextWinning(board, 'X');
                board[p.first][p.second] = 'O';
            }
        } 
        else if (ct / 2 == 3 or ct / 2 == 4) {
            pair<int, int> p = checkNextWinning(board, 'O');
            if (p.first == -1 and p.second == -1) {
                p = checkNextWinning(board, 'X');
                if (p.first == -1 and p.second == -1) {
                    p = FirstEmpty(board);
                    board[p.first][p.second] = 'O';
                } 
                else {
                    board[p.first][p.second] = 'O';
                }
            } 
            else {
                board[p.first][p.second] = 'O';
                showBoard(board);
                cout << "\n Computer Wins! ";
                return;
            }
        }
        showBoard(board);
    }
	cout << "\nMatch Draw!" << endl;
}

pair<int, int> CheckAdjSide(vector<vector<char>> &board) {
    pair<int, int> p = make_pair(-1, -1);
	if (board[1][0] == 'X' and board[0][1] == 'X') {
		p = make_pair(0, 0);
	} 
	else if (board[0][1] == 'X' and board[1][2] == 'X') {
		p = make_pair(0, 2);
	}
	else if (board[1][2] == 'X' and board[2][1] == 'X') {
        p = make_pair(2, 2);
	}
	else if (board[2][1] == 'X' and board[1][0] == 'X') {
		p = make_pair(2, 0);
	}
	return p;
}

void SideMovePlay(vector<vector<char>> &board, int &ct) {
    while (ct < 9) {
		ct += 1;
		if (ct % 2 == 1) {
			cout << "\n Enter Your Move : ";
			int x, y;
			cin >> x >> y;
			while (!CheckValidInput(board,x,y)) {
                cout << "\n Enter a valid input! ";
                cin >> x >> y;
            }
            board[x - 1][y - 1] = 'X';
        } 
        else if (ct / 2 == 1)
            board[1][1] = 'O';
        else if (ct / 2 == 2) {
            pair<int, int> p = CheckAdjSide(board);
            if (p.first == -1 and p.second == -1) {
                p = checkNextWinning(board,'X');
                if (p.first == -1 and p.second == -1) {
                    p = GiveWinSidePos(board);
                    board[p.first][p.second] = 'O';
                } 
                else {
                    board[p.first][p.second] = 'O';
                }
            } 
            else {
                 board[p.first][p.second] = 'O';
            }
        } 
        else if (ct / 2 == 3 or ct / 2 == 4) {
            pair<int, int> p = checkNextWinning(board, 'O');
            if (p.first == -1 and p.second == -1) {
                p = checkNextWinning(board, 'X');
                if (p.first == -1 and p.second == -1) {
                    p = FirstEmpty(board);
                    board[p.first][p.second] = 'O';
                } 
                else
                    board[p.first][p.second] = 'O';
            } 
            else {
                board[p.first][p.second] = 'O';
                showBoard(board);
                cout << "\n Computer Wins! ";
                return;
            }
        }
        showBoard(board);
    }
	cout << "\nMatch Draw." << endl;
}

void Play() {
    int ct = 1;
    cout << "\n Enter Your Move : ";
    int i, j;
    cin >> i >> j;
    while (!CheckValidInput(board, i, j)) {
        cout << "\n Enter a valid input! ";
        cin >> i >> j;
    }
    board[i - 1][j - 1] = 'X';
    showBoard(board);
    if ((i == 1 or i == 3) and (j == 1 or j == 3)) {
		CornerMovePlay(board, ct);
    } 
    else if (i == 2 and j == 2) {
		CenterMovePlay(board, ct);
	} 
	else {
		SideMovePlay(board, ct);
	}
}

int main() {
    setBoard(board);
    showBoard(board);
    Play();
}
