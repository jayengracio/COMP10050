/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
            board[i][j].curr = NULL;
            board[i][j].numTokens = 0;
        }
    }
}
    
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){
    int nPlayers=0;
    
    printf("\nHow many players? (MAX 6): ");
    scanf("%d", &nPlayers);
    
    while (nPlayers < 2 || nPlayers > 6)
    {
        printf("\nERROR! Only 2 to 6 Players.\nTry Again: ");
        scanf("%d", &nPlayers);
    }
    
    for(int i=0;i<nPlayers;i++)
    {
        printf("\nEnter Player %d's Name: ", i+1);
        scanf("%s", &players[i].name);
        players[i].col = i;
        //printf("%s is set as color %d\n\n", players[i].name, players[i].col);
    }
    
    return nPlayers;
    }
    
   
     

