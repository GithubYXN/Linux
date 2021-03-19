#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "transistors.h"

/* 
 * Name : yx
 * Description : Simple transistor description example proogram
 */

int main()
{
	int i;
	Tran *trans;
	int numTrans = 0;
	char status[10];

	printf("transistors!\n");

	// Allocate space for one transistor
	trans = malloc(sizeof(Tran));
	numTrans = 1;

	trans[0] = InputTransistor();

	printf("Would you like to enter another transistor (Y/N)?\n");

	scanf("%1s", status);

	getchar();

	while(strcmp(status,"Y") == 0 )
	{
	trans = realloc(trans,sizeof(Tran)*(numTrans +1));
	numTrans++;
	printf("\n");
	trans[numTrans-1] = InputTransistor();

	printf("Would you like to enter another transistor (Y/N)?\n");

	scanf("%1s", status);
	
	getchar();
	}

	printf("\nThe transistors:\n");

	for(i=0; i<numTrans; i++)
	{
		DisplayTransistor(trans[i]);
	}

	free(trans);

	return 0;
}
