#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Name : yx
 *
 * Simple Wumpus game in 1D
 */

// ID's for things in the cave
#define Empty 0
#define Wumpus 1
#define End 2
#define CaveSize 20
#define ArraySize (CaveSize + 2)
// Directions i can face
#define Left 0
#define Right 1

void CreateWorld(int cave[]);
int *GetEmptyRoom(int cave[]);
void DisplayWorld(int cave[], int *agent, int agentDir);
int DifferenceByDirection(int dir);
bool DisplayStatus(int cave[], int *agent,int flag);

int main()
{
	int cave[ArraySize];
	int *agentRoom;
	int agentDirection;
	char command[20];
	int direction;
	int *room;
	
	int flag = 1;
	
	srand(time(NULL));

	CreateWorld(cave);	
	
	agentRoom = GetEmptyRoom(cave);
	agentDirection = rand() % 2;
	
	// The game loop
	while(true)
	{
		if(DisplayStatus(cave, agentRoom,flag))
			break;
		DisplayWorld(cave, agentRoom, agentDirection);
		//Get the command
		printf("Command: ");
		scanf("%20s", command);
		
		if(strcmp(command, "quit") == 0)
		{
			break;
		}
		else if(strcmp(command, "move") == 0)
		{
			// Move command,and what way we need to go?
			direction = DifferenceByDirection(agentDirection);
			if( *(agentRoom + direction) != End)
				agentRoom += direction;
		}
		else if(strcmp(command, "turn") == 0)
		{
			agentDirection = !agentDirection;
		}
		else if(strcmp(command, "fire") == 0 && agentDirection == Right)
		{
			room = agentRoom;
			for(int i = 0; i<3 && *room != End; i++)
			{
				room++;
				if(*room == Wumpus)
				{
					*room = Empty;
					flag = 0;
				}
			}
		}
		else if(strcmp(command, "fire") == 0 && agentDirection == Left)
		{
			room = agentRoom;
			for(int i = 0; i<3 && *room != End; i++)
			{
				room--;
				if(*room == Wumpus)
				{
					*room = Empty;
					flag = 0;
				}
			}
		}
		else
		{
			printf("I don't know what you are talking about.\n");
		}
	}
	return 0;
}

void CreateWorld(int cave[])
{
	int *room;
	
	// Initialize cave to empty
	for(int i =0;i<ArraySize; i++)
	{
		cave[i] = Empty;
	}
	
	// Set the ends
	cave[0] = End;
	cave[ArraySize-1] = End;
	
	// Get a random empty room and put the Wumpus in it
	room = GetEmptyRoom(cave);
	*room = Wumpus;
}

int *GetEmptyRoom(int cave[])
{
	int room;
	
	do
	{
		room = rand() % ArraySize;
	} while(cave[room] != Empty);
	
	return &cave[room];
}

void DisplayWorld(int cave[], int *agent, int agentDir)
{
	int *room;
	
	for(room = cave +1; *room != End; room++)
	{
		if(room == agent)
		{
			switch(agentDir)
			{
			case Left:
				printf("<A  ");
				break;
			case Right:
				printf(" A> ");
			}
			continue;
		}
		
		switch(*room)
		{
		case Wumpus:
			printf("-W- ");
			break;
			
		default:
			printf(" .  ");
			break;
		}
	}
	printf("\n");
}

int DifferenceByDirection(int dir)
{
	if(dir == Left)
		return -1;
	else 
		return 1;
}

bool DisplayStatus(int cave[], int *agent,int flag)
{
	if(*agent == Wumpus)
	{
		printf("You have been eaten by the Wumpus.\n");
		return true;
	}
	if(*(agent-1) == Wumpus || *(agent+1) == Wumpus)
	{
		printf("I smell a Wumpus.\n");
	}
	if(!flag)
	{
		printf("You killed Wumpus and won the game.\n");
		return true;
	}
	return false;
}



