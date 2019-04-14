/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    // the min number of tokens placed on a square in the first column of the board
    struct token *top = NULL;
    struct token *curr = NULL;
    
    int minNumOfTokens = 0;
    int selectedSquare = 0;
    
    for(int i=0;i<4;i++)
    {
        for (int j=0;j<numPlayers;j++)
        {
            printf("\nPlayer %d please select a square\n", j+1);
            scanf("%d", &selectedSquare);
            
            // IMPLEMENT: if the square selected by the user has the minimum number of tokens
            // and whether it does not contain a token of the same color selected by the player
            
            struct token *push(int value, struct token *top)
            {
            board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
            board[selectedSquare][0].stack->col = players[j].col;
            board[selectedSquare][0].stack->nextPtr = curr;
            board[selectedSquare][0].numTokens++;
            
            return top;
            }
            
            /*struct token *push(int value, struct token *top)
            {
                struct token *curr = top;
                top = malloc(sizeof(token));
                top = board[selectedSquare][0].stack;
                top->col = players[j].col;
                top->nextPtr = curr;
                return top;
            }*/
            
            /*struct token * pop(struct token *top){
                struct token *curr = top;
                if(curr!=NULL){
                    top = curr->nextPtr;
                    printf("Stack Data POP: %d\n", top->col);
                    free(curr);
                }
                    return top;
            
            }*/
            
            top = push(2, top);
            printf("Stack Data PUSH: %d\n", top->col);
            
            top = push(3, top);
            printf("Stack Data PUSH: %d\n", top->col);
            
            top = push(4, top);
            printf("Stack Data PUSH: %d\n", top->col);
            
            //top = pop(top);
            //top = pop(top);
            //board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
            //board[selectedSquare][0].stack->col = players[j].col;
            //board[selectedSquare][0].numTokens++;
                
            //updates the minimum number of tokens
            if(((numPlayers*i)+j+1)%NUM_ROWS==0)
            minNumOfTokens++;
        }
    }

}


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    //TO BE IMPLEMENTED
    struct token *top;
    struct token *curr;
    
    
    srand(time(NULL));
    int dice;
    int sidestep;
    int col, row;
    int temp1, temp2;
    int move;
    
    printf("\nThe game has commenced.\n");
    
    // for loop is a placeholder
    for(int i=0;i<99;i++)
    {
        for(int j=0;j<numPlayers;j++)
        {
        dice = rand() % 5;
        printf("\nIt is %s's turn.\n", players[j].name);
        printf("\n%s rolled the dice and landed on: %d\n", players[j].name, dice);
        
        printf("\nSidestep 1 of your pieces?\n1. Yes\n2. No\n? ");
        scanf("%d", &sidestep);
        
        switch (sidestep)
        {
            case 1:
                printf("\nWhich piece? e.g (8,5)\n? ");
                scanf("%d,%d", &row, &col);
                while (board[row][col].stack->col != players[j].col)
                {
                    printf("\nYou do not have a piece in (%d,%d).\n? ", row,col);
                    scanf("%d,%d", &row, &col);
                }
                
                
                //board[row][col].stack = (token*)malloc(sizeof(token));
                //board[row][col].numTokens--;
                
                printf("\n1. Above or 2. Below?\n?");
                scanf("%d", &move);
                
                if (col < NUM_COLUMNS || col > 0)
                {
                    if(move == 1)
                    {
                        struct token * pop(struct token *top){
                            struct token *curr = top;
                            if(curr!=NULL){
                                top = curr->nextPtr;
                                printf("Stack Data POP: %d\n", top->col);
                                free(curr);
                            }
                            return top;
                          }
                        
                        board[row-1][col].stack = (token*)malloc(sizeof(token));
                        board[row-1][col].stack->col = players[j].col;
                        board[row-1][col].stack->nextPtr = curr;
                        board[row-1][col].numTokens++;
                        
                        
                        board[row][col].stack = (token*)malloc(sizeof(token));
                        board[row][col].stack->col = curr->col;
                        board[row][col].numTokens--;
                    }
                    
                    if (move == 2)
                    {
                        board[row+1][col].stack = (token*)malloc(sizeof(token));
                        board[row+1][col].stack->col = players[j].col;
                        board[row+1][col].numTokens++;
                    }
                }
                
                break;
                
            case 2:
                printf("\nThe top token from column %d has been moved 1 space.", dice);
                break;
        }
        
        print_board(board);
        }
    }
}



