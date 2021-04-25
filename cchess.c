#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define B_BORDER 0
#define B_INSIDE 1
#define B_VALUE 2

#define BG_WHITE 0
#define BG_BLACK 1

static char ** board;

void alloc_board();
void free_board();
void print_board();

/**
 * Prints either of the segments:
 * +---+---+---+---+---+---+---+---+
 * OR
 * |▓▓▓|░░░|▓▓▓|░░░|▓▓▓|░░░|▓▓▓|░░░|
 * OR
 * |▓R▓|░N░|▓B▓|░Q░|▓K▓|░B░|▓N▓|░R░|
 */
void print_board_line(size_t segment, size_t row);

// Black pieces are with ascii values > A and < Z
// White pieces are with ascii values > a and < z
int is_white(char piece);

// change the colors of the output
void set_red();
void set_cyan();
void reset_color();

// sets the color to either BG_BLACK or BG_WHITE
void set_BGcolor(size_t color);

int main() {
    alloc_board();
    print_board();
    free_board();
    return 0;
}

void alloc_board() {
    board = (char**) malloc(sizeof(char*) * 8);
    for (size_t i = 0; i < 8; i++) {
        board[i] = (char*) malloc(sizeof(char) * 8);
        for (size_t j = 0; j < 8; j++) {
            board[i][j] = 0;
            if (i == 0) {
                if (j == 0 || j == 7) {
                    board[i][j] = 'R';
                } else if (j == 1 || j == 6) {
                    board[i][j] = 'N';
                } else if (j == 2 || j == 5) {
                    board[i][j] = 'B';
                } else if (j == 3) {
                    board[i][j] = 'Q';
                }else if (j == 4) {
                    board[i][j] = 'K';
                }
            } else if (i == 1) {
                board[i][j] = 'P';
            } else if (i == 7) {
                if (j == 0 || j == 7) {
                    board[i][j] = 'r';
                } else if (j == 1 || j == 6) {
                    board[i][j] = 'n';
                } else if (j == 2 || j == 5) {
                    board[i][j] = 'b';
                } else if (j == 3) {
                    board[i][j] = 'q';
                }else if (j == 4) {
                    board[i][j] = 'k';
                }
            } else if (i == 6) {
                board[i][j] = 'p';
            }
        }
    }
}

void free_board() {
    for(size_t i = 0; i < 8; i++) {
        free(board[i]);
    }
    free(board);
}

void print_board() {
    system("clear");
    for (size_t i = 0; i < 8; i++) {
        print_board_line(B_INSIDE, i);
        print_board_line(B_VALUE, i);
        print_board_line(B_INSIDE, i);
    }
}

void print_board_line(size_t segment, size_t row) {
    char val;
    size_t color;

    for (size_t i = 0; i < 8; i++) {
        if (row % 2 == 0) {
            if (i % 2 == 0) {
                color = BG_WHITE;
            } else {
                color = BG_BLACK;
            }
        } else {
            if (i % 2 == 0) {
                color = BG_BLACK;
            } else {
                color = BG_WHITE;
            }
        }
        if (segment == B_INSIDE || board[row][i] == 0) {
            set_BGcolor(color);
            printf("       ");
            reset_color();
        } else if (segment == B_VALUE) {
            val = board[row][i];
            set_BGcolor(color);
            printf("   ");
            if (is_white(val)) {
                set_cyan();
                val -= 32;
            } else {
                set_red();
            }
            printf("%c", val);
            set_BGcolor(color);
            printf("   ");
            reset_color();
        }
    }
    printf("\n");
}

int is_white(char piece) {
    return (piece > 'a') && (piece < 'z');
}

void set_BGcolor(size_t color) {
    if (color == BG_WHITE) {
        printf("\x1b[47m");
    } else if (color == BG_BLACK) {
        printf("\x1b[40m");
    }
}

void set_red() {
    printf("\033[0;31m");
}

void set_cyan() {
    printf("\033[0;36m");
}

void reset_color() {
    printf("\033[0m");
}