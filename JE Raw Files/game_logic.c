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
            // ask for user-input for which square to place his/her token(s)
            printf("\n%s, please select a square\n-> ", players[j].name);
            scanf("%d", &selectedSquare);
            
            
            // if user-input is not between the table row size (0 to 5).
            while (selectedSquare > 5 || selectedSquare < 0)
            {
                printf("\nERROR! Must be between 0 and 5.\nPlayer %d please select another square\n-> ", j+1);
                scanf("%d", &selectedSquare);
            }
            
            // loop: if a square is not equal to the minimum number of tokens
            while (board[selectedSquare][0].numTokens != 0 &&
                    board[selectedSquare][0].numTokens != minNumOfTokens)
                {
                    printf("\nERROR! This square currently exceeds the minimum amount of tokens.\nPlayer %d please select another square\n-> ", j+1);
                    scanf("%d", &selectedSquare);
                }
            
            // loop: a player cannot stack his/her token on top of each other
            while (board[selectedSquare][0].numTokens != 0 && players[j].col == board[selectedSquare][0].stack->col && board[selectedSquare][0].numTokens == minNumOfTokens)
            {
                printf("\nERROR! You cannot stack a token on top of yours.\nPlayer %d please select another square\n-> ", j+1);
                scanf("%d", &selectedSquare);   
            }
            
            // if there is more than 1 token in a square, it stacks.
            board[selectedSquare][0].curr = board[selectedSquare][0].stack;
            board[selectedSquare][0].stack = (token*)malloc(sizeof(token));
            board[selectedSquare][0].stack->col = players[j].col;
            board[selectedSquare][0].stack->nextPtr = board[selectedSquare][0].curr;
            
            // updates the number of tokens in the selected square
            board[selectedSquare][0].numTokens++;
                
            // updates the minimum number of tokens
            if(((numPlayers*i)+j+1)%NUM_ROWS==0)
            minNumOfTokens++;

            // display the game table with current updates.
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
    srand(time(NULL));
    int col, row;
    int dice;
    int move;
    int x = 0;
    
    int bfield, bfield2, bfield3, bfield4, bfield5, bfield6;
    
    printf("\n! THE GAME HAS COMMENCED !\n");
    
    for(int i=0;i<TURNS;i++)
    {
        for(int j=0;j<numPlayers;j++)
        { 
            dice = rand() % + 5;
            
            if (board[0][3].stack > 0)
            {
                printf("\nObstacle (0,3) has been activated.\n");
                bfield = 1;
            }
            
            if (board[1][6].stack > 0)
            {
                printf("\nObstacle (1,6) has been activated.\n");
                bfield2 = 1;
            }
            
            if (board[2][4].stack > 0)
            {
                printf("\nObstacle (2,4) has been activated.\n");
                bfield3 = 1;
            }
            
            if (board[3][5].stack > 0)
            {
                printf("\nObstacle (3,5) has been activated.\n");
                bfield4 = 1;
            }
            
            if (board[4][2].stack > 0)
            {
                printf("\nObstacle (4,2) has been activated.\n");
                bfield5 = 1;
            }
            
            if (board[5][7].stack > 0)
            {
                printf("\nObstacle (5,7) has been activated.\n");
                bfield6 = 1;
            }
            
            /* DICE ROLLS AUTOMATIC (makes thing easier) */
            printf("\n\n --- ( NEW TURN )  --- \n\n");
            printf("It is %s's turn.\n", players[j].name);
            printf("\n%s rolls the dice: %d\n", players[j].name, dice);
            
            
            /* SIDESTEP */
            printf("\nSelect one of your tokens e.g. (8,5)\n-> ");
            scanf("%d,%d", &row, &col);
            
            // if the square is empty, ask for user input again.
            while (board[row][col].stack == NULL)
            {
                printf("\nERROR! This square is empty.\n-> ");
                scanf("%d,%d", &row, &col);
            }
            
            // if the player's color does not match the top token from user inputted (row,col)
            while (board[row][col].stack->col != players[j].col)
            {
                printf("\nERROR! The top token in (%d,%d) is not your piece.\n-> ", row,col);
                scanf("%d,%d", &row, &col);
            }
            
            // user-input: if user wants to sidepiece his/her piece up or down or not at all
            printf("\n1 -> Move Up\n2 -> Move Down\n3 -> Skip Sidestep\n\n-> ");
            scanf("%d", &move);
            
            // if the user-input value is not 1, 2 or 3
            while (move != 1 && move != 2 && move != 3)
            {
                printf("\nERROR! Incorrect Input.");
                printf("\n1 -> Move Up\n2 -> Move Down\n3 -> Skip Sidestep\n\n-> ");
                scanf("%d", &move);
            }
            
            // creates a new token for the upper row
            if(move == 1)
            {   
                    board[row-1][col].curr = board[row-1][col].stack;
                    board[row-1][col].stack = (token*)malloc(sizeof(token));
                    board[row-1][col].stack->col = board[row][col].stack->col;
                    board[row-1][col].stack->nextPtr = board[row-1][col].curr;
                
                    // the square that the token: the top value is 'popped' and replaced by the token below it
                    board[row][col].curr = board[row][col].stack;
                    if(board[row][col].curr != NULL)
                    {
                        board[row][col].stack = board[row][col].curr->nextPtr;
                        free(board[row][col].curr);
                    }
            }
        
            // creates a new token for the lower row
            if (move == 2)
            {
                    board[row+1][col].curr = board[row+1][col].stack;
                    board[row+1][col].stack = (token*)malloc(sizeof(token));
                    board[row+1][col].stack->col = board[row][col].stack->col;
                    board[row+1][col].stack->nextPtr = board[row+1][col].curr;
                
                    // the square that the token: the top value is 'popped' and replaced by the token below it
                    board[row][col].curr = board[row][col].stack;
                    if(board[row][col].curr != NULL)
                    {
                        board[row][col].stack = board[row][col].curr->nextPtr;
                        free(board[row][col].curr);
                    }
            }
            
            // if the user does not wish to move his piece
            if (move == 3)
            {
                printf("\nSidestep skipped\n");
            }
            
            // display the game table with current updates.
            print_board(board);
            
            /* THE DICE LANDS & A TOKEN MOVES */
            printf("\nPick token from row %d to move e.g. (%d,3)\n\n? ", dice, dice);
            scanf("%d,%d", &row, &col);
            
            // in the case that an entire column doesn't contain a single token, the dice is re-rolled (for safety measures).
            /*if (board[row][0].stack == NULL && board[row][1].stack == NULL && board[row][2].stack == NULL &&
                board[row][3].stack == NULL && board[row][4].stack == NULL && board[row][5].stack == NULL &&
                board[row][6].stack == NULL && board[row][7].stack == NULL && board[row][8].stack == NULL)
            {
                printf("\nColumn %d appears to be empty, the dice has been re-rolled.\n", col);
                dice = rand() % + 5;
                printf("\nPick token from row %d to move e.g. (%d,3)\n\n-> ", dice, dice);
                scanf("%d,%d", &row, &col);
            }*/
            
            
            
            if (bfield == 1)
            {
                if (board[0][0].stack == NULL && board[0][1].stack == NULL && board[0][2].stack == NULL &&
                        board[1][0].stack == NULL && board[1][1].stack == NULL && board[1][2].stack == NULL &&
                        board[2][0].stack == NULL && board[2][1].stack == NULL && board[2][2].stack == NULL &&
                        board[3][0].stack == NULL && board[3][1].stack == NULL && board[3][2].stack == NULL &&
                        board[4][0].stack == NULL && board[4][1].stack == NULL && board[4][2].stack == NULL &&
                        board[5][0].stack == NULL && board[5][1].stack == NULL && board[5][2].stack == NULL)
                {
                    printf("\nObstacle (0,3) has been deactivated\n-> ");
                    board[0][3].type = NORMAL;
                    bfield = 0;
                }
                
                while (row == 0 && col == 3 && bfield == 1)
                {
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until column 0 and 1 are empty.\n-> ");
                    scanf("%d,%d", &row, &col);
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                    printf("\nERROR! This square is empty.\nTry again\n-> ");
                    scanf("%d,%d", &row, &col);
                    }
                }
            }
            
            
            if (bfield2 == 1)
            {
                if (board[0][0].stack == NULL && board[0][1].stack == NULL && board[0][2].stack == NULL && board[0][3].stack == NULL && board[0][4].stack == NULL && board[0][5].stack == NULL &&
                    board[1][0].stack == NULL && board[1][1].stack == NULL && board[1][2].stack == NULL && board[1][3].stack == NULL && board[1][4].stack == NULL && board[1][5].stack == NULL &&
                    board[2][0].stack == NULL && board[2][1].stack == NULL && board[2][2].stack == NULL && board[2][3].stack == NULL && board[2][4].stack == NULL && board[2][5].stack == NULL &&
                    board[3][0].stack == NULL && board[3][1].stack == NULL && board[3][2].stack == NULL && board[3][3].stack == NULL && board[3][4].stack == NULL && board[3][5].stack == NULL &&
                    board[4][0].stack == NULL && board[4][1].stack == NULL && board[4][2].stack == NULL && board[4][3].stack == NULL && board[4][4].stack == NULL && board[4][5].stack == NULL &&
                    board[5][0].stack == NULL && board[5][1].stack == NULL && board[5][2].stack == NULL && board[5][3].stack == NULL && board[5][4].stack == NULL && board[5][5].stack == NULL)
                {
                    printf("\nObstacle (1,6) has been deactivated\n-> ");
                    board[1][6].type = NORMAL;
                    bfield2 = 0;
                }
                
                while (row == 1 && col == 6 && bfield2 == 1)
                {
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until column 0 and 1 are empty.\n-> ");
                    scanf("%d,%d", &row, &col);
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                    printf("\nERROR! This square is empty.\nTry again\n-> ");
                    scanf("%d,%d", &row, &col);
                    }
                }
            }
            
            
            
            if (bfield3 == 1)
            {
                if (board[0][0].stack == NULL && board[0][1].stack == NULL && board[0][2].stack == NULL && board[0][3].stack == NULL &&
                    board[1][0].stack == NULL && board[1][1].stack == NULL && board[1][2].stack == NULL && board[1][3].stack == NULL &&
                    board[2][0].stack == NULL && board[2][1].stack == NULL && board[2][2].stack == NULL && board[2][3].stack == NULL &&
                    board[3][0].stack == NULL && board[3][1].stack == NULL && board[3][2].stack == NULL && board[3][3].stack == NULL &&
                    board[4][0].stack == NULL && board[4][1].stack == NULL && board[4][2].stack == NULL && board[4][3].stack == NULL &&
                    board[5][0].stack == NULL && board[5][1].stack == NULL && board[5][2].stack == NULL && board[5][3].stack == NULL)
                {
                    printf("\nObstacle (2,4) has been deactivated\n-> ");
                    board[2][4].type = NORMAL;
                    bfield3 = 0;
                }
                
                while (row == 2 && col == 4 && bfield3 == 1)
                {
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until column 0 and 1 are empty.\n-> ");
                    scanf("%d,%d", &row, &col);
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                    printf("\nERROR! This square is empty.\nTry again\n-> ");
                    scanf("%d,%d", &row, &col);
                    }
                }
            }
            
            
            if (bfield4 == 1)
            {
                if (board[0][0].stack == NULL && board[0][1].stack == NULL && board[0][2].stack == NULL && board[0][3].stack == NULL && board[0][4].stack == NULL &&
                    board[1][0].stack == NULL && board[1][1].stack == NULL && board[1][2].stack == NULL && board[1][3].stack == NULL && board[1][4].stack == NULL &&
                    board[2][0].stack == NULL && board[2][1].stack == NULL && board[2][2].stack == NULL && board[2][3].stack == NULL && board[2][4].stack == NULL &&
                    board[3][0].stack == NULL && board[3][1].stack == NULL && board[3][2].stack == NULL && board[3][3].stack == NULL && board[3][4].stack == NULL &&
                    board[4][0].stack == NULL && board[4][1].stack == NULL && board[4][2].stack == NULL && board[4][3].stack == NULL && board[4][4].stack == NULL &&
                    board[5][0].stack == NULL && board[5][1].stack == NULL && board[5][2].stack == NULL && board[5][3].stack == NULL && board[5][4].stack == NULL)
                {
                    printf("\nObstacle (3,5) has been deactivated\n-> ");
                    board[3][5].type = NORMAL;
                    bfield4 = 0;
                }
                
                while (row == 3 && col == 5 && bfield4 == 1)
                {
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until column 0 and 1 are empty.\n-> ");
                    scanf("%d,%d", &row, &col);
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                    printf("\nERROR! This square is empty.\nTry again\n-> ");
                    scanf("%d,%d", &row, &col);
                    }
                }
            }
            
            if (bfield5 == 1)
            {
                if (board[0][0].stack == NULL && board[0][1].stack == NULL &&
                    board[1][0].stack == NULL && board[1][1].stack == NULL &&
                    board[2][0].stack == NULL && board[2][1].stack == NULL &&
                    board[3][0].stack == NULL && board[3][1].stack == NULL &&
                    board[4][0].stack == NULL && board[4][1].stack == NULL &&
                    board[5][0].stack == NULL && board[5][1].stack == NULL)
                {
                    printf("\nObstacle (4,2) has been deactivated\n-> ");
                    board[4][2].type = NORMAL;
                    bfield5 = 0;
                }
                
                while (row == 4 && col == 2 && bfield5 == 1)
                {
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until column 0 and 1 are empty.\n-> ");
                    scanf("%d,%d", &row, &col);
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                    printf("\nERROR! This square is empty.\nTry again\n-> ");
                    scanf("%d,%d", &row, &col);
                    }
                }
            }
            
            if (bfield6 == 1)
            {
                if (board[0][0].stack == NULL && board[0][1].stack == NULL && board[0][2].stack == NULL && board[0][3].stack == NULL && board[0][4].stack == NULL && board[0][5].stack == NULL && board[0][6].stack == NULL &&
                    board[1][0].stack == NULL && board[1][1].stack == NULL && board[1][2].stack == NULL && board[1][3].stack == NULL && board[1][4].stack == NULL && board[1][5].stack == NULL && board[1][6].stack == NULL &&
                    board[2][0].stack == NULL && board[2][1].stack == NULL && board[2][2].stack == NULL && board[2][3].stack == NULL && board[2][4].stack == NULL && board[2][5].stack == NULL && board[2][6].stack == NULL &&
                    board[3][0].stack == NULL && board[3][1].stack == NULL && board[3][2].stack == NULL && board[3][3].stack == NULL && board[3][4].stack == NULL && board[3][5].stack == NULL && board[3][6].stack == NULL &&
                    board[4][0].stack == NULL && board[4][1].stack == NULL && board[4][2].stack == NULL && board[4][3].stack == NULL && board[4][4].stack == NULL && board[4][5].stack == NULL && board[4][6].stack == NULL &&
                    board[5][0].stack == NULL && board[5][1].stack == NULL && board[5][2].stack == NULL && board[5][3].stack == NULL && board[5][4].stack == NULL && board[5][5].stack == NULL && board[5][6].stack == NULL)
                {
                    printf("\nObstacle (5,7) has been deactivated\n-> ");
                    board[5][7].type = NORMAL;
                    bfield6 = 0;
                }
                
                while (row == 5 && col == 7 && bfield6 == 1)
                {
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until column 0 and 1 are empty.\n-> ");
                    scanf("%d,%d", &row, &col);
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                    printf("\nERROR! This square is empty.\nTry again\n-> ");
                    scanf("%d,%d", &row, &col);
                    }
                }
            }
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
            while (row != dice)
            {
                printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                scanf("%d,%d", &row, &col);
            }
            
            // if the the user tries to move an empty square, ask for user input again.
            while (board[row][col].stack == NULL)
            {
                printf("\nERROR! This square is empty.\nTry again\n-> ");
                scanf("%d,%d", &row, &col);
            }
            
            
            
            // a new token is made in the next column based on the previous column.
            board[row][col+1].curr = board[row][col+1].stack;
            board[row][col+1].stack = (token*)malloc(sizeof(token));
            board[row][col+1].stack->col = board[row][col].stack->col;
            board[row][col+1].stack->nextPtr = board[row][col+1].curr;
            
            // the top token is removed and replaced by the token that was below it.
            board[row][col].curr = board[row][col].stack;
            if(board[row][col].curr != NULL)
            {
                board[row][col].stack = board[row][col].curr->nextPtr;
                free(board[row][col].curr);
            }    
            
            
            /* END-GAME */
            if (board[row][8].stack != NULL)
            {
                // checks if the player moving the token is the owner or not
                while (j < numPlayers)
                {    
                    // if the player owns the token that recently reached the end-line
                    if (players[j].col == board[row][8].stack->col)
                    {
                        // the number of tokens in the last-col increases
                        players[j].numTokensLastCol++;
                        break;
                    }
                    
                    // if player does not own the token, it will loop through the colors of each player
                    else
                        j++;
                }
                
                
                // the first player that has 3 tokens go to the end-line wins the session & the program exits.
                if (players[j].numTokensLastCol == 3)
                {
                    printf("\n\nGAME OVER: %s WINS! \n\n", players[j].name);
                    exit(0);
                }
            }
            
            print_board(board);
        }
    }
}



