#include <stdio.h>
#include <stdlib.h>

char **board;   
int N;        

void initializeBoard();
void displayBoard();

int main() {
    printf("Enter grid size N (3 <= N <= 10): ");
    scanf("%d", &N);

    if (N < 3 || N > 10) {
        printf("Invalid size! Exiting.\n");
        return 1;
    }

    board = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++)
        board[i] = (char *)malloc(N * sizeof(char));

    initializeBoard();
    displayBoard();

    for (int i = 0; i < N; i++)
        free(board[i]);
    free(board);

    return 0;
}

void initializeBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
        printf("\n");
        if (i < N - 1) {
            for (int k = 0; k < N; k++) {
                printf("---");
                if (k < N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}
