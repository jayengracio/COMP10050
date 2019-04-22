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
    
    // setting up of variables
    srand(time(0));
    int col, row;
    int dice;
    int move;
    int x = 0;
    int bfield, bfield2, bfield3, bfield4, bfield5, bfield6;
    
    
    // the game begins
    printf("\n! THE GAME HAS COMMENCED !\n");
    
    
    for(int i=0;i<TURNS;i++)
    {
        for(int j=0;j<numPlayers;j++)
        { 
            // each run, the value of the dice is randomized between 0 and 5.
            dice = rand() % 6;
            
            
            // print to display to users that an obstacle square is active.
            if (board[0][3].stack > 0)
            {
                printf("\nObstacle (0,3) is active.\n");
                bfield = 1; // bfield is set to 0 to indicate that this specific square is active.
            }
            
            if (board[1][6].stack > 0)
            {
                printf("\nObstacle (1,6) is active.\n");
                bfield2 = 1;
            }
            
            if (board[2][4].stack > 0)
            {
                printf("\nObstacle (2,4) is active.\n");
                bfield3 = 1;
            }
            
            if (board[3][5].stack > 0)
            {
                printf("\nObstacle (3,5) is active.\n");
                bfield4 = 1;
            }
            
            if (board[4][2].stack > 0)
            {
                printf("\nObstacle (4,2) is active.\n");
                bfield5 = 1;
            }
            
            if (board[5][7].stack > 0)
            {
                printf("\nObstacle (5,7) is active.\n");
                bfield6 = 1;
            }
            // displaying of active obstacle ends here
            
            
            
            
            
            /* 1. THE DICE (the dice is rolled automatically each there is a new turn)*/
            printf("\n\n --- ( NEW TURN )  --- \n\n");
            printf("It is %s's turn.\n", players[j].name);
            printf("\n%s rolls the dice: %d\n", players[j].name, dice);
            
            
            
            /*2. THE SIDESTEP (a player chooses a token of his/hers and can choose to sidestep it or not)*/
            printf("\nSelect one of your tokens e.g. (8,5)\n-> ");
            scanf("%d,%d", &row, &col);
            
            
            // if the square is empty, ask for user input again.
            while (board[row][col].stack == NULL)
            {
                printf("\nERROR! This square is empty.\nIf there are no tokens in available input 9,9 to end-turn.\n-> ");
                scanf("%d,%d", &row, &col);
            }

            
            // if the player's color does not match the top token from user inputted (row,col), ask for user input again
            while (board[row][col].stack->col != players[j].col)
            {
                printf("\nERROR! The top token in (%d,%d) is not your piece.\n-> ", row,col);
                scanf("%d,%d", &row, &col);
            }
            
            
            // if player tries to pick a specific square that is currently set as an "OBSTACLE", ask for user input again
            while (row == 0 && col == 3 && bfield == 1)
            {
                printf("\nOBSTACLE! This square 0,3 is currently locked\nIf there are no tokens in available input 9,9 to end-turn.\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            
            while (row == 1 && col == 6 && bfield2 == 1)
            {
                printf("\nOBSTACLE! This square 1,6 is currently locked\nIf there are no tokens in available input 9,9 to end-turn.\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            
            while (row == 2 && col == 4 && bfield3 == 1)
            {
                printf("\nOBSTACLE! This square 2,4 is currently locked\nIf there are no tokens in available input 9,9 to end-turn.e\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            
            while (row == 3 && col == 5 && bfield4 == 1)
            {
                printf("\nOBSTACLE! This square 3,5 is currently locked\nIf there are no tokens in available input 9,9 to end-turn.\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            
            while (row == 4 && col == 2 && bfield5 == 1)
            {
                printf("\nOBSTACLE! This square 4,2 is currently locked\nIf there are no tokens in available input 9,9 to end-turn.\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            
            while (row == 5 && col == 7 && bfield6 == 1)
            {
                printf("\nOBSTACLE! This square 5,7 is currently locked\nIf there are no tokens in available input 9,9 to end-turn.\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            // end of specific obstacle square user-input.
            
            
            
            
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
                // if the user-inputted row is not between the values of 0 to 5 (the row size of the game table)
                if(row-1 < 1)
                {
                    printf("\nMove incomplete, inputted row goes beyond the table size of 0 to 5\n\n");
                }
                
                // if the user-input meets the right requirements
                else
                {
                    // using linked lists
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
            }
        
            // creates a new token for the lower row
            if (move == 2)
            {
                if (row+1 > NUM_ROWS)
                {
                    printf("\nMove incomplete, inputted row goes beyond the table size of 0 to 8\n\n");
                }
                
                else
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
            }
            
            // if the user does not wish to move his piece
            if (move == 3)
            {
                printf("\nSidestep skipped\n");
            }
            
            // display the game table with current updates.
            print_board(board);
            
            
            
            
            
            
            /*3. TOKEN MOVEMENT (a token based on the number row that the dice lands on moves 1 column to the right)*/
            printf("\nPick token from row %d to move e.g. (%d,3)\nIf there are no tokens from this row to move, input 9,9 to end-turn.\n-> ", dice, dice);
            scanf("%d,%d", &row, &col);       
            
            // in case of emergency, end player J's move.
            if (row == 9 && col == 9)
            break;    
            
            
            
            
            
            // OBSTACLE: when a player tries to move a token from an active obstacle square
            if (bfield == 1)
            {
                // if the requirements are met for an obstacle square to deactivate, their type is set to normal and tokens in that square can now move forward.
                if (board[0][0].stack == NULL && board[0][1].stack == NULL && board[0][2].stack == NULL &&
                        board[1][0].stack == NULL && board[1][1].stack == NULL && board[1][2].stack == NULL &&
                        board[2][0].stack == NULL && board[2][1].stack == NULL && board[2][2].stack == NULL &&
                        board[3][0].stack == NULL && board[3][1].stack == NULL && board[3][2].stack == NULL &&
                        board[4][0].stack == NULL && board[4][1].stack == NULL && board[4][2].stack == NULL &&
                        board[5][0].stack == NULL && board[5][1].stack == NULL && board[5][2].stack == NULL)
                {
                    printf("\nObstacle (0,3) has been deactivated\n-> ");
                    board[0][3].type = NORMAL; // sets the board type from OBSTACLE to NORMAL
                    bfield = 0; // sets the obstacle indicator to 0 which will render some loops useless.
                }
                
                while (row == 0 && col == 3 && bfield == 1)
                {
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until all squares prior to this column are empty."
                            "\nIf there are no other tokens outside of the obstacle, input 0,9 to end turn.\n-> ");
                    
                    scanf("%d,%d", &row, &col);
                    
                    if (row == 0 && col == 9)
                        break;
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                        
                        if (row == 0 && col == 9)
                        break;
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                        printf("\nERROR! This square is empty.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    
                        if (row == 0 && col == 9)
                        break;
                    }
                }
            }
            
            // obstacle in (1,6)
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
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until all squares prior to this column are empty."
                            "\nIf there are no other tokens outside of the obstacle, input 1,9 to end turn.\n-> ");
                    
                    scanf("%d,%d", &row, &col);
                    
                    if (row == 1 && col == 9)
                        break;
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                        
                        if (row == 1 && col == 9)
                        break;
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                        printf("\nERROR! This square is empty.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    
                        if (row == 1 && col == 9)
                        break;
                    }
                }
            }
            
            
            
            // obstacle in (2,4)
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
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until all squares prior to this column are empty."
                            "\nIf there are no other tokens outside of the obstacle, input 2,9 to end turn.\n-> ");
                    
                    scanf("%d,%d", &row, &col);
                    
                    if (row == 2 && col == 9)
                        break;
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                        
                        if (row == 2 && col == 9)
                        break;
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                        printf("\nERROR! This square is empty.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    
                        if (row == 2 && col == 9)
                        break;
                    }
                }
            }
            
            
            
            // obstacle in (3,5)
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
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until all squares prior to this column are empty."
                            "\nIf there are no other tokens outside of the obstacle, input 3,9 to end turn.\n-> ");
                    
                    scanf("%d,%d", &row, &col);
                    
                    if (row == 3 && col == 9)
                        break;
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                        
                        if (row == 3 && col == 9)
                        break;
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                        printf("\nERROR! This square is empty.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    
                        if (row == 3 && col == 9)
                        break;
                    }
                }
            }
            
            
            // obstacle in (4,2)
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
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until all squares prior to this column are empty."
                            "\nIf there are no other tokens outside of the obstacle, input 4,9 to end turn.\n-> ");
                    
                    scanf("%d,%d", &row, &col);
                    
                    if (row == 4 && col == 9)
                        break;
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                        
                        if (row == 4 && col == 9)
                        break;
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                        printf("\nERROR! This square is empty.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                        
                        if (row == 4 && col == 9)
                        break;
                    }
                }
            }
            
            
            
            // obstacle in (5,7)
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
                    printf("\nOBSTACLE ACTIVE: You cannot move this token until all squares prior to this column are empty."
                            "\nIf there are no other tokens outside of the obstacle, input 5,9 to end turn.\n-> ");
                    
                    scanf("%d,%d", &row, &col);
                    
                    if (row == 5 && col == 9)
                        break;
                    
                    // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
                    while (row != dice)
                    {
                        printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                        
                        if (row == 5 && col == 9)
                        break;
                    }
            
                    // if the the user tries to move an empty square, ask for user input again.
                    while (board[row][col].stack == NULL)
                    {
                        printf("\nERROR! This square is empty.\nTry again\n-> ");
                        scanf("%d,%d", &row, &col);
                    
                        if (row == 5 && col == 9)
                        break;
                    }
                }
            }           
            
            
            
            
            
            
            // if the user-inputted row is not equal to the value the dice lands on, as for user input again.
            while (row != dice)
            {
                printf("\nERROR! Input piece is not from the rolled row.\nTry again\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            
            // if the the user tries to move an empty square, ask for user input again.
            while (board[row][col].stack == NULL)
            {
                printf("\nERROR! This square is empty.\nTry again\n-> ");
                scanf("%d,%d", &row, &col);
                
                if (row == 9 && col == 9)
                break;
            }
            
            
            
            // a 'new' token is made in the next column based on the token behind it.
            board[row][col+1].curr = board[row][col+1].stack;
            board[row][col+1].stack = (token*)malloc(sizeof(token));
            board[row][col+1].stack->col = board[row][col].stack->col;
            board[row][col+1].stack->nextPtr = board[row][col+1].curr;
            
            // the top token is removed and replaced by the previous token before it in the old column.
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



