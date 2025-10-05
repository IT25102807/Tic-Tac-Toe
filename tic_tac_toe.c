/*
 * Programming Methodology
 * Tic-Tac-Toe Game
 * Author: Perera B.D.S
 * IT25102807
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Board Variables */
char **board; 
int N;

/* Player Symbols */ 
char symbols[3] = {'X','O','Z'}; /*X for human. O and Z for Computers */

/* Functions */
void initializeBoard();
void displayBoard(int showNumbers);
int validateMove(int row, int col);
void userMove(char symbol);
void computerMove(char symbol);
int checkWin();
int isFull();
void logBoard(FILE *f);

int main(void) {
    srand(time(NULL));

    int mode;
    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d",&N);
    if (N<3 || N>10) {
        printf("Invalid size.\n");
        return 1;
    }

    /* Allocate board */
    board=(char**)malloc(N*sizeof(char*));
    for(int i=0;i<N;i++)
        board[i]=(char*)malloc(N*sizeof(char));

    initializeBoard();

    printf("\nSelect Game Mode:\n");
    printf("1. Two Players (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("3. Three Players\n");
    printf("Enter choice (1-3): ");
    scanf("%d",&mode);

    FILE *logFile=fopen("tictactoe_log.txt","w");
    if(!logFile){
	    printf("Could not open log file.\n");
	    return 1;}

    int gameOver = 0;
    int current = 0; /* track which player */

    /* main game loop */
    while(!gameOver) {
        displayBoard(1);

        if(mode==1){ /* two players X/O */
            char symbol = (current==0)?'X':'O';
            printf("Player %c, enter row and col (0..%d): ",symbol,N-1);
            userMove(symbol);
        }
        else if(mode==2){ /* user vs computer */
            if(current==0){
                printf("Player X, enter row and col (0..%d): ",N-1);
                userMove('X');
            } else {
                printf("Computer (O) is moving...\n");
                computerMove('O');
            }
        }
        else if(mode==3){ /* three players */
            char symbol=symbols[current];
            if(current==0){
                printf("Player X, enter row and col (0..%d): ",N-1);
                userMove(symbol);
            } else {
                printf("Computer Player %d (%c) moving...\n",current+1,symbol);
                computerMove(symbol);
            }
        }

        logBoard(logFile);

        if(checkWin()){
            displayBoard(1);
            if(mode==1){
                printf("Player %c wins!\n",(current==0)?'X':'O');
                fprintf(logFile,"Player %c wins!\n",(current==0)?'X':'O');
            } else if(mode==2){
                if(current==0){
                    printf("You win!\n");
                    fprintf(logFile,"User wins!\n");
                } else {
                    printf("Computer wins!\n");
                    fprintf(logFile,"Computer wins!\n");
                }
            } else {
                printf("Player %c wins!\n",symbols[current]);
                fprintf(logFile,"Player %c wins!\n",symbols[current]);
            }
            gameOver=1;
        } else if(isFull()){
            displayBoard(1);
            printf("It's a draw!\n");
            fprintf(logFile,"It's a draw!\n");
            gameOver=1;
        } else {
            /* switch player */
            if(mode==1)
                current=(current+1)%2;
            else if(mode==2)
                current=(current+1)%2;
            else
                current=(current+1)%3;
        }
    }

    /* free Memory */
    for(int i=0;i<N;i++) free(board[i]);
    free(board);
    fclose(logFile);
    return 0;
}

/* Functions Definitions */

void initializeBoard(){
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            board[i][j]=' ';
}

void displayBoard(int showNumbers){
    printf("\n");
    if(showNumbers){
        printf("   ");
        for(int j=0;j<N;j++) printf("%d ",j);
        printf("\n");
    }
    for(int i=0;i<N;i++){
        if(showNumbers) printf("%d ",i);
        for(int j=0;j<N;j++){
            printf("|%c",board[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

int validateMove(int row,int col){
    if(row<0||row>=N||col<0||col>=N) return 0;
    if(board[row][col]!=' ') return 0;
    return 1;
}

void userMove(char symbol){
    int row,col;
    scanf("%d %d",&row,&col);
    while(!validateMove(row,col)){
        printf("Invalid move! Enter again: ");
        scanf("%d %d",&row,&col);
    }
    board[row][col]=symbol;
}

void computerMove(char symbol){
    int row,col;
    do{
        row=rand()%N;
        col=rand()%N;
    }while(!validateMove(row,col));
    board[row][col]=symbol;
}

int checkWin(){
    for(int i=0;i<N;i++){
        char rowChar=board[i][0];
        if(rowChar!=' '){
            int win=1;
            for(int j=1;j<N;j++)
                if(board[i][j]!=rowChar) win=0;
            if(win) return 1;
        }
        char colChar=board[0][i];
        if(colChar!=' '){
            int win=1;
            for(int j=1;j<N;j++)
                if(board[j][i]!=colChar) win=0;
            if(win) return 1;
        }
    }
    char diagChar=board[0][0];
    if(diagChar!=' '){
        int win=1;
        for(int i=1;i<N;i++)
            if(board[i][i]!=diagChar) win=0;
        if(win) return 1;
    }
    char antiChar=board[0][N-1];
    if(antiChar!=' '){
        int win=1;
        for(int i=1;i<N;i++)
            if(board[i][N-i-1]!=antiChar) win=0;
        if(win) return 1;
    }
    return 0;
}

int isFull(){
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(board[i][j]==' ')
                return 0;
    return 1;
}

void logBoard(FILE *f){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fprintf(f," %c ",board[i][j]);
            if(j<N-1) fprintf(f,"|");
        }
        fprintf(f,"\n");
    }
    fprintf(f,"\n");
}
