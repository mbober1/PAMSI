#include <stdio.h>
#include <iostream>
#include <string>
#include <bits/stdc++.h> 


#define PLAYER 4
#define AI 1
#define END_GAME 2
#define DRAW 3

class Move {
    public:
    int i, j;

    Move(int i, int j) {
        this->i = i;
        this->j = j;
    }
};

class Board {
    int *r,*c;
    int d=0, ad=0;
    
    public:
    char** matrix;
    int rows, cols, pointsToWin, turns_count = 0;

    Board(int size, int pointsToWin) {
        this->rows = size;
        this->cols = size;
        this->pointsToWin = pointsToWin;
        
        matrix = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) matrix[i] = new char[this->cols];

        r = new int[this->rows];
        for (int i = 0; i < this->rows; ++i) r[i] = 0;

        c = new int[this->cols];
        for (int i = 0; i < this->cols; ++i) c[i] = 0;

        this->reset();
    }

    ~Board() {
        for (int i = 0; i < this->rows; ++i)
            delete [] matrix[i];
        delete [] matrix;
    }

    Board(const Board& a) : Board(a.cols, a.pointsToWin) {
        this->cols = a.cols;
        this->rows = a.rows;
        this->turns_count = a.turns_count;
        this->d = a.d;
        this->ad = a.ad;
        this->pointsToWin = a.pointsToWin;
        for (int i = 0; i < this->rows; ++i) this->r[i] = a.r[i];
        for (int i = 0; i < this->cols; ++i) this->c[i] = a.c[i];

        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                this->matrix[i][j] = a.matrix[i][j];
            }
        }
    }

    void reset() {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                this->matrix[i][j] = ' ';
            }
        }
        
    }

    void draw() {
        printf("    ");
        for (int i=0; i < this->cols; ++i) printf(" %c  ", 'A'+i);
        printf("\n");

        printf("   ┌───");
        for (int i=1; i < this->rows; ++i) printf("┬───");
        printf("┐\n");
        for (int j = 0; j < (2*this->rows)-1; ++j) {
            if (j % 2 == 1) {
                printf("   ├───");
                for (int i = 1; i < this->cols; ++i) printf("┼───");
                printf("┤\n");
            }
            else {
                printf("%2d ", (j/2));
                for (int i = 0; i < this->cols; ++i) {
                    char c;
                    switch (matrix[i][j/2]) {
                        case AI: c = 'X'; break;
                        case PLAYER: c = 'O'; break;
                        default: c = ' ';
                    }
                    printf("│ %c ", c);
                }
                printf("│\n");
            }
        }
        printf("   └───");
        for (int i=1; i < this->cols; ++i) printf("┴───");
        printf("┘\n");
    }

    int getWinner() const {
        int x = this->pointsToWin;
        if(this->turns_count == this->cols*this->cols) {
            return DRAW;
        }
        
        // wygrana w kolumnach
        for (int i = 0; i < this->rows; ++i) {
            for (int start = 0; start <= this->cols - x; ++start) {
                int ai = 0;
                int pl = 0;
                int last = 0;
                for (int j = start; j < start + x; ++j) {
                    if (this->matrix[i][j] == AI) {
                        ai = (last == AI) ? ai+1 : 1;
                        last = AI;
                    }
                    else if (this->matrix[i][j] == PLAYER) {
                        pl = (last == PLAYER) ? pl+1 : 1;
                        last = PLAYER;
                    }
                    else last = 0;

                    if (ai >= x) return AI;
                    else if (pl >= x) return PLAYER;
                }
            }
        }

        // // wygrana w wierszach
        for (int j = 0; j < this->cols; ++j) {
            for (int start = 0; start <= this->rows - x; ++start) {
                int ai = 0;
                int pl = 0;
                int last = 0;
                for (int i = start; i < start + x; ++i) {
                    if (this->matrix[i][j] == AI) {
                        ai = (last == AI) ? ai+1 : 1;
                        last = AI;
                    }
                    else if (this->matrix[i][j] == PLAYER) {
                        pl = (last == PLAYER) ? pl+1 : 1;
                        last = PLAYER;
                    }
                    else last = 0;

                    if (ai >= x) return AI;
                    else if (pl >= x) return PLAYER;
                }
            }
        }

        // // wygrana po przekątnej
        for (int colStart = 0; colStart < this->cols; ++colStart) {
            for (int rowStart = 0; rowStart <= this->rows - x; ++rowStart) {
                int ai = 0;
                int pl = 0;
                int last = 0;
                for (int i = rowStart, j = colStart; i < rowStart + x, j < colStart + x; ++i, ++j) {
                    if (this->matrix[i][j] == AI) {
                        ai = (last == AI) ? ai+1 : 1;
                        last = AI;
                    }
                    else if (this->matrix[i][j] == PLAYER) {
                        pl = (last == PLAYER) ? pl+1 : 1;
                        last = PLAYER;
                    }
                    else last = 0;

                    if (ai >= x) return AI;
                    else if (pl >= x) return PLAYER;
                }
            }
        }

        // // wygrana po antyprzekątnej
        for (int colStart = this->cols; colStart >= this->rows - x; --colStart) {
            for (int rowStart = 0; rowStart <= this->rows - x; ++rowStart) {
                int ai = 0;
                int pl = 0;
                int last = 0;
                for (int i = rowStart, j = colStart; i < rowStart + x, j > colStart - x; ++i, --j) {
                    if (this->matrix[i][j] == AI) {
                        ai = (last == AI) ? ai+1 : 1;
                        last = AI;
                    }
                    else if (this->matrix[i][j] == PLAYER) {
                        pl = (last == PLAYER) ? pl+1 : 1;
                        last = PLAYER;
                    }
                    else last = 0;

                    if (ai >= x) return AI;
                    else if (pl >= x) return PLAYER;
                }
            }
        }

        return 0;
    }


    bool do_turn(int col, int row, int state) {
        if(col < 0 || col >= this->cols) {
            printf("Nie ma takiej kolumny\n"); 
            return false;
        }
        if(row < 0 || row >= this->rows) {
            printf("Nie ma takiego rzędu\n"); 
            return false;
        }

        if(this->matrix[col][row] != ' ') {
            printf("To pole jest już zajęte\n"); 
            return false;
        }
        
        this->matrix[col][row] = state;
        int score = state == AI ? 1 : -1;
        this->r[row] += score;
        this->c[col] += score;
        if(col==row) {
            if(col<this->cols/2) {
                if(row<=this->rows/2) this->d += score;
                if(row>=this->rows/2) this->ad += score;
            }
            else if(col>this->cols/2) {
                if(row<=this->rows/2) this->d += score;
                if(row>=this->rows/2) this->ad += score;
            }
            else if(col == this->cols/2) this->d += score; this->ad += score;
        }
        this->turns_count++;
        return true;
    }
};

int minmax(const Board &board, int player, int depth = 0) {
    switch (board.getWinner()) {
        case AI: return 1;
        case PLAYER: return -1;
        case DRAW: return 0;
    }
    
    if (board.rows < 10) {
        if (depth == 5) return 0;
    } else if (depth == 3) return 0;
    

    int score = player == AI ? INT_MIN : INT_MAX;

    for (int i = 0; i < board.cols; ++i) {
        for (int j = 0; j < board.rows; ++j) {
            if (board.matrix[i][j] == ' ') {
                Board tmp_board = board;
                tmp_board.do_turn(i, j, player);
                int result = minmax(tmp_board, (player == AI ? PLAYER : AI), depth+1);
                score = player == AI ? std::max(score, result) : std::min(score, result);
            } 
        }
    }
    return score;
}

void doAITurn(Board &board) {
    int score = INT_MIN;
    Move m(-1, -1);

    for (int i = 0; i < board.cols; ++i) {
        for (int j = 0; j < board.rows; ++j) {
            if (board.matrix[i][j] == ' ') {
                Board tmp_board = board;
                tmp_board.do_turn(i, j, AI);
                int result = minmax(tmp_board, PLAYER);
                
                if(result > score) {
                    score = result;
                    m.i = i;
                    m.j = j;
                }
            } 
        }
    }

    board.do_turn(m.i, m.j, AI);
}

void doPlayerTurn(Board &board) {
    int score = INT_MIN;
    Move m(-1, -1);

    for (int i = 0; i < board.cols; ++i) {
        for (int j = 0; j < board.rows; ++j) {
            if (board.matrix[i][j] == ' ') {
                Board tmp_board = board;
                tmp_board.do_turn(i, j, PLAYER);
                int result = minmax(tmp_board, AI);
                
                if(result > score) {
                    score = result;
                    m.i = i;
                    m.j = j;
                }
            } 
        }
    }

    board.do_turn(m.i, m.j, PLAYER);
}

int main() {
    int gameSize, pointsToWin;
    std::cout << "Podaj wielkość planszy: ";
    std::cin >> gameSize;
    std::cout << "Podaj ilość znaków w rzędzie: ";
    std::cin >> pointsToWin;
    Board board(gameSize, pointsToWin);
    int state = PLAYER;
    while(state != END_GAME) {
        printf("\nTura %s\n\n", state == AI ? "AI" : "gracza");
        char col, row;
        board.draw();
        bool good;
        do {
            if(state == PLAYER) {
                std::cout << "Podaj pole: ";
                std::cin >> col;
                std::cin >> row;
                col = col - 'A';
                row = row - '0';
                good = board.do_turn(col, row, state);
            } else {
                doAITurn(board);
            }
                
        } while(!good);
        
        state = state == AI ? PLAYER : AI;
        if(board.getWinner() != 0) state = END_GAME;
        printf("\n");
    }

    board.draw();

    switch (board.getWinner()) {
        case AI: printf("\nPrzykro mi, przegrałeś.\n"); break;
        case PLAYER: printf("\nGratulacje wygrałeś!\n"); break;
        case DRAW: printf("\nRemis!\n"); break;
    }

    return 0;
}

