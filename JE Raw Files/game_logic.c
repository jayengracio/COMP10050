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
    int minNumOfTokens = 0;
    int selectedSquare = 0;
    
    for(int i=0;i<4;i++)
    {
        for (int j=0;j<numPlayers;j++)
        {
            printf("\nPlayer %d please select a square\n? ", j+1);
            scanf("%d", &selectedSquare);
            
            /* Loop: The first column must be fully filled. */
            /*while (board[selectedSquare][0].numTokens != 0 &&
                    board[selectedSquare][0].numTokens != minNumOfTokens)
                {
                    printf("\nERROR! Must be an empty square.\nPlayer %d please select another square\n? ", j+1);
                    scanf("%d", &selectedSquare);
                }*/
            
            /* Loop: To not allow player to stack a token on top of his/hers. */
            while (board[selectedSquare][0].numTokens != 0 && players[j].col == board[selectedSquare][0].stack->col)
            {
                printf("\nERROR! You cannot stack a token on top of yours.\nPlayer %d please select another square\n? ", j+1);
                scanf("%d", &selectedSquare);   
            }
            
            /* Token adding/stacking */
            board[selectedSquare][0].curr = board[selectedSquare][0].stack;
            board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
            board[selectedSquare][0].stack->col = players[j].col;
            board[selectedSquare][0].stack->nextPtr = board[selectedSquare][0].curr;
            
            // updates the number of tokens in the selected square
            board[selectedSquare][0].numTokens++;
                
            // updates the minimum number of tokens
            if(((numPlayers*i)+j+1)%NUM_ROWS==0)
            minNumOfTokens++;

            // display the updated board.
            print_board(board);
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
    
    srand(time(NULL));
    int col, row;
    int dice;
    int move;
    
    printf("\n! THE GAME HAS COMMENCED !\n");
    
    // for loop is a placeholder
    for(int i=0;i<99;i++)
    {
        for(int j=0;j<numPlayers;j++)
        {
            //dice = rand() % + 5;
            dice = 5;
        
            // indicating which player's turn it is
            printf("\n\n --- NEW TURN --- \n\n");
            printf("It is %s's turn.\n", players[j].name);
            printf("\n%s's dice landed on: %d\n", players[j].name, dice);
           
            // user input: ask which piece to sidestep 
            printf("\nPick one of your piece to sidestep e.g. (8,5)\n\n? ");
            scanf("%d,%d", &row, &col);
        
            // if the player's color does not match the top token from user inputted (row,col)
            while (board[row][col].stack->col != players[j].col || board[row][col].stack == NULL)
            {
                printf("\nYou do not have a piece in (%d,%d).\n\n? ", row,col);
                scanf("%d,%d", &row, &col);
            }
                
            // user input: if the token is to be moved up/down a column
            printf("\n1 -> Move Up\n3 -> Move Down\n3 -> Skip Sidestep\n\n? ");
            scanf("%d", &move);
                
            while (move != 1 && move != 2 && move != 3)
            {
                printf("\nERROR: Incorrect Input.");
                printf("\n1 -> Move Up\n3 -> Move Down\n3 -> Skip Sidestep\n\n? ");
                scanf("%d", &move);
            }
        
            // token placement for up
            if(move == 1)
            {   
                board[row-1][col].curr = board[row-1][col].stack;
                board[row-1][col].stack = (token*)malloc(sizeof(token));
                board[row-1][col].stack->col = board[row][col].stack->col;
                board[row-1][col].stack->nextPtr = board[row-1][col].curr;
                
                // the top token is replaced by user input (popped out from stack)
                board[row][col].curr = board[row][col].stack;
                if(board[row][col].curr != NULL)
                {
                    board[row][col].stack = board[row][col].curr->nextPtr;
                    free(board[row][col].curr);
                }
            }
        
            // token placement for down
            if (move == 2)
            {
                board[row+1][col].curr = board[row+1][col].stack;
                board[row+1][col].stack = (token*)malloc(sizeof(token));
                board[row+1][col].stack->col = board[row][col].stack->col;
                board[row+1][col].stack->nextPtr = board[row+1][col].curr;
                
                // the top token is replaced by user input (popped out from stack)
                board[row][col].curr = board[row][col].stack;
                if(board[row][col].curr != NULL)
                {
                    board[row][col].stack = board[row][col].curr->nextPtr;
                    free(board[row][col].curr);
                }
            }
            
            if (move == 3)
            {
                printf("\nSidestep skipped\n");
            }
            
            print_board(board);
            
            // DICE
            printf("\nPick token from row %d to move e.g. (%d,3)\n\n? ", dice, dice);
            scanf("%d,%d", &row, &col);
            
            while (row != dice)
            {
                printf("\nERROR! Input piece is not from the rolled row.\nTry again\n? ");
                scanf("%d,%d", &row, &col);
            }
            
            while (board[row][col].stack == NULL)
            {
                printf("\nERROR! This square is empty.\nTry again\n? ");
                scanf("%d,%d", &row, &col);
            }
            
            board[row][col+1].curr = board[row][col+1].stack;
            board[row][col+1].stack = (token*)malloc(sizeof(token));
            board[row][col+1].stack->col = board[row][col].stack->col;
            board[row][col+1].stack->nextPtr = board[row][col+1].curr;
                
            // the top token is replaced by user input (popped out from stack)
            board[row][col].curr = board[row][col].stack;
            if(board[row][col].curr != NULL)
            {
                board[row][col].stack = board[row][col].curr->nextPtr;
                free(board[row][col].curr);
            }
        
            // display the board with the new updates
            print_board(board);
        }
    }
}



