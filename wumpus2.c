#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Name : yx
 * Simple Wumpus game in 2D
 */
 
 // ID's for things in our cave
 #define Empty 0
 #define Wumpus 1
 #define End 2
 #define Pit 3
 
 // Number of rooms in our Cave in each dimension
 #define Left 0
 #define Up 1
 #define Right 2
 #define Down 3
 
 #define CaveSize 10
 #define ArraySize (CaveSize + 2)
 
 void CreateWorld(int cave[ArraySize][ArraySize]);
 int *GetEmptyRoom(int cave[ArraySize][ArraySize]);
 void DisplayWorld(int cave[ArraySize][ArraySize], int *agent, int agentDir);
 int DifferenceByDirection(int dir);
 bool DisplayStatus(int cave[ArraySize][ArraySize], int *agent, int flag);

 
 int main()
 {
 	int *agentRoom;
 	int agentDirection;
 	char command[20];
 	int cave[ArraySize][ArraySize];
 	int d;
 	int flag = 1;
 	int *room;
 	
 	// Seed the random number generator
 	srand(time(NULL));
 	
 	CreateWorld(cave);
 	
 	agentRoom = GetEmptyRoom(cave);
 	agentDirection = rand() % 4;
 	
 	// The game loop
 	while(true)
 	{
 		printf("Plz enter help if you don't konw how to play the game.\n\n");
 		if(DisplayStatus(cave, agentRoom,flag))
 			break;
 		DisplayWorld(cave,agentRoom,agentDirection);
 		// Get the command
 		printf("Command: ");
 		scanf("%20s", command);
 		if(strcmp(command, "quit") == 0)
 		{
 			break;
 		}
 		 else if(strcmp(command, "move") == 0)
        {
        	d =DifferenceByDirection(agentDirection);
        	
        	if(*(agentRoom + d) != End)
        		agentRoom += d;
        }
        else if(strcmp(command, "turn") == 0)
        {
        	agentDirection ++;
        	if(agentDirection > Down)
        		agentDirection = Left;
        }
        
        else if(strcmp(command, "fire") == 0 && agentDirection == Left)
        {
        	room = agentRoom;
        	for(int i=0;i<3 && *room != End;i++)
        	{
        		room--;
        		if(*room == Wumpus)
        		{
        			*room = Empty;
        			flag = 0;
        		}
        	}
        }
        else if(strcmp(command, "fire") == 0 && agentDirection == Right)
        {
        	room = agentRoom;
        	for(int i=0;i<3 && *room != End;i++)
        	{
        		room++;
        		if(*room == Wumpus)
        		{
        			*room = Empty;
        			flag = 0;
        		}
        	}
        }
        else if(strcmp(command, "fire") == 0 && agentDirection == Up)
        {
        	room = agentRoom;
        	for(int i=0;i<3 && *room != End;i++)
        	{
        		room -= ArraySize;
        		if(*room == Wumpus)
        		{
        			*room = Empty;
        			flag = 0;
        		}
        	}
        }
        else if(strcmp(command, "fire") == 0 && agentDirection == Down)
        {
        	room = agentRoom;
        	for(int i=0;i<3 && *room != End;i++)
        	{
        		room += ArraySize;
        		if(*room == Wumpus)
        		{
        			*room = Empty;
        			flag = 0;
        		}
        	}
        }
        
        else if(strcmp(command, "help") == 0)
        {
        	printf("Help: \n");
        	printf("Here are these three commands:turn , move, fire.\n");
        	printf("turn: Change your turn.\n");
        	printf("move: Move forwrd one unit.\n");
        	printf("fire: Attack three units in your direction.\n");
        	printf("And quit to quit the game.\n\n");
        }
        
        else
        {
            printf("I don't know what you are talking about\n");
        }
    }
    
 	return 0;
 }
 
 void CreateWorld(int cave[ArraySize][ArraySize])
 {
 	int i,j;
 	int *room;
 	int *pit[10];
 	
 	for(i=0; i<ArraySize;i++)
 	{
 		for(j=0; j<ArraySize; j++)
 		{
 			if(i==0 || j==0 || i==ArraySize-1 || j==ArraySize-1)
 				cave[i][j] = End;
 			else
 				cave[i][j] = Empty;
 		}
 	}
 	room = GetEmptyRoom(cave);
 	*room = Wumpus;
 	for(i = 0;i<10;i++)
 	{
 		pit[i] = GetEmptyRoom(cave);
 		*pit[i] = Pit;
 	}
 }
 
int *GetEmptyRoom(int cave[ArraySize][ArraySize])
{
	int row, col;
	int *room;
	
	do
	{
		row = random() % ArraySize;
		col = random() % ArraySize;
		
		room = &cave[row][col];
	} while (*room != Empty);
	
	return room;
}

void DisplayWorld(int cave[ArraySize][ArraySize], int *agent, int agentDir)
{
	int row,col;
	int *room;
	
	for(row=1; row<=CaveSize + 1; row++)
	{
		for(col=1; col<=CaveSize;col++)
		{
			if(&cave[row][col] == agent && agentDir == Up)
				printf(" ^  ");
			else if(&cave[row-1][col] == agent && agentDir == Down)
				printf(" v  ");
			else
				printf("    ");
		}
		printf("\n");
		if(row > CaveSize)
			break;
			
		// This loop prints the agent ot the room contents
		for(col=1;col<=CaveSize;col++)
		{
			room = &cave[row][col];
			if(room == agent)
			{
				switch(agentDir)
				{
				case Left:
					printf("<A  ");
					break;
				case Right:
					printf(" A> ");
					break;
				default:
					printf(" A  ");
					break;
				}
				continue;
			}
			switch(*room)
			{
			case Wumpus:
				printf("-W- ");
				break;
			case Pit:
				printf(" 0  ");
				break;
			default:
				printf(" .  ");
				break;
			}
		}
		
		printf("\n");
	}
}

int DifferenceByDirection(int dir)
{
	switch(dir)
	{
	case Up:
		return -ArraySize;
	case Down:
		return ArraySize;
	case Left:
		return -1;
	case Right:
		return 1;
	}
}

bool DisplayStatus(int cave[ArraySize][ArraySize], int *agent, int flag)
{
	if(*agent == Wumpus)
	{
		printf("You are eaten by Wumpus.\n");
		return true;
	}
	if(*(agent-1) == Wumpus || *(agent+1) == Wumpus || *(agent-ArraySize) == Wumpus || *(agent+ArraySize) == Wumpus)
		printf("I smell a Wumpus.\n");
	if(!flag)
	{
		printf("You killed Wumpus and won the game.\n");
		return true;
	}
	if(*agent == Pit)
	{
		printf("You fell into a pit.\n");
		return true;
	}
	if(*(agent-1) == Pit || *(agent+1) == Pit || *(agent-ArraySize) == Pit || *(agent+ArraySize) == Pit)
		printf("I fell a draft.\n");
	
	return false;	
}	



