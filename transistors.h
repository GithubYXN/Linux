#ifndef TRANSISTORS_H
#define TRANSISTORS_H

#define NPN 1
#define PNP 2

#define TO18 1
#define TO92A 2
#define TO92C 3
#define TO220 4
#define TO39 5

typedef struct Transistor
{
	char number[10];
	int type;
	int caseStyle;
	double pmax;
	double icmax;
} Tran;

void DisplayTransistor(Tran tran);
Tran InputTransistor();
void InputString(char *str, int max);
double InputPositiveValue(char *prompt);
int InputTransistorType(char *prompt);
int InputCaseStyle(char *pormpt);

#endif
