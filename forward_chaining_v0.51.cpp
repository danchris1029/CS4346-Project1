/*Enclosed a program, which comprises the inference engine based on Forward chaining.You need it for your
project #1.  The program contains some errors and it is not designed to be efficient.
Modify the program to make it better and efficient.Explain in your report how you have modified the
program to make it better.*/

/*** FORWARD CHAINING ***/
/************************/
/* Install your IF clauses in squence in the middle of
the program within the first case statement.
EXAMPLE: IF ((A1==2) && (A2==6) || (A3 == 'YES')) S-1;
IF (J=='NO') S-1;

The THEN part of the above construction always contains
S-1. Install your THEN clauses in sequence in the middle
of the program within the second case statement. */

/*

10: IF WorkingNetwork == True AND
	ViableNetworkExplanation == TRUE
	THEN SlowInternet == TRUE              // Note we hit a final conclusion

20: IF WorkingNetwork == True AND
	ViableNetworkExplanation == False
	WebsiteNoAccess == True

30: IF WorkingNetwork == False AND
	ValuableData == True
	THEN NotificationDataBreach == True

*/

#include <iostream>
#include <stdio.h>
#include "string.h"

const int numRules = 15; /* number of rules */
const int charLength = 20;

/* instantiated list*/
char workingNetwork[charLength], viableNetworkExplanation[charLength], slowInternet[charLength], notificationDataBreach[charLength], websiteNoAccess[charLength], valuableData[charLength], var[charLength];

void check_instantiation(int* index, char v[], char(&varlt)[numRules][charLength], int instlt[]);
void search(int* flag, int* sn, int* f, int* fp, char(&clvarlt)[60][charLength], char(&cndvar)[numRules][charLength], int* cn, int* k);
void instantiate(int* index, char v[], char(&varlt)[numRules][charLength], int instlt[], char(&cndvar)[numRules][charLength], int* bp);

int main()
{
	bool jump = false;

	int instlt[numRules];
	int flag;
	int f, i, j, k, s, fp   /* front pointer */;
	int  bp  /* back pointer */, gr /* grade */, sn; /* statement number */
	int cn;  /* clause number */
	char cndvar[numRules][charLength];
	char varlt[numRules][charLength], /* variable list*/ clvarlt[60][charLength]; /* clause var list */ // 4 * 15 =  60
	char c[charLength], vp[charLength], /* condition variable */  v[charLength]; /*variable */

	/******** INITIALIZATION SECTION ***********/
	fp = 1;
	bp = 1;

	for (i = 1; i < 60; i++)
		strcpy(clvarlt[i], "");
	for (i = 0; i < numRules; i++)
	{
		strcpy(cndvar[i], "");
		strcpy(varlt[i], "");
		instlt[i] = 0;
	}

	/* enter variables which are in the IF part, 1 at a time in
	the exact order that they occur. Up to 3 variables per
	IF statement. Do not duplicate any variable names. Any
	name is used only once. If no more variables left, just
	hit return key */
	/****** comment 367 *************/								// Variable list
	strcpy(varlt[1], "WN");
	strcpy(varlt[2], "VNE");
	strcpy(varlt[3], "VD");

	printf("*** VARIABLE LIST ***\n");
	for (i = 1; i < numRules; i++)
		printf("ENTER VARIABLE   %d   %s\n", i, varlt[i]);
	printf("HIT RETURN TO CONTINUE");
	getchar();

	/* enter variables as they appear in the IF clauses, Up to 3
	variables per IF statement. If no more variables left, just
	hit return key */
	/****** comment 407, 408 *************/							// Clause variable list
	strcpy(clvarlt[1], "WN");
	strcpy(clvarlt[2], "VNE");
	strcpy(clvarlt[5], "WN");
	strcpy(clvarlt[6], "VNE");
	strcpy(clvarlt[9], "WN");
	strcpy(clvarlt[10], "VD");

	printf("*** CLAUSE-VARIABLE LIST ***\n");
	for (i = 1; i < numRules; i++)
	{
		printf("** CLAUSE %d\n", i);
		for (j = 1; j < 5; j++)
		{
			k = 4 * (i - 1) + j;
			printf("VARIABLE %d  %s\n", j, clvarlt[k]);
		}

		if (i == 4)
		{
			printf("HIT RETURN TO CONTINUE");
			getchar();
		}
	}

	/****** INFERENCE SECTION *****************/
	printf("ENTER CONDITION VARIABLE? ");
	std::cin >> c;
	/* place condition variable c on condition var queue cndvar */
	strcpy(cndvar[bp], c);
	/* move backpointer (bp) to back */
	bp = bp + 1;
	/* set the condition variable pointer consisting of the
	statement number (sn) and the clause number (cn) */
	sn = 1; cn = 1;
	/* find the next statement number containing the condition variable
	which is in front of the queue (cndvar), this statement number
	is located in the clause variable list (clvarlt) */
	/* start at the beginning */
	f = 1;
	do { // b496
		jump = false;
		search(&flag, &sn, &f, &fp, clvarlt, cndvar, &cn, &k);
		/* point to first clause in statement */
		cn = 1;
		if (sn != 0) {
			/* more statements */
			/* locate the clause */
			i = 4 * (sn - 1) + cn;
			/* clause variable */
			strcpy(v, clvarlt[i]);
			/* are there any more clauses for this statement */
			while (strcmp(v, ""))
				/* more clauses */
			{
				/* check instantiation of this clause */
				check_instantiation(&i, v, varlt, instlt);
				cn = cn + 1;
				/* check next clause */
				i = 4 * (sn - 1) + cn;
				strcpy(v, clvarlt[i]);
			}

			/* no more clauses - check IF part of statement */
			s = 0;
			/* sample IF-THEN statements from the position knowledge base */
			switch (sn)
			{
				/* statement 1 */
				/***** comment 1500 *****/
			case 1: if (strcmp(workingNetwork, "TRUE") == 0 && strcmp(viableNetworkExplanation, "TRUE") == 0) s = 1;
				break;
				/* statement 2 */
				/***** comment 1510 *****/
			case 2: if (strcmp(workingNetwork, "TRUE") == 0 && strcmp(viableNetworkExplanation, "FALSE") == 0) s = 1;
				break;
				/* statement 3 */
				/***** comment 1540 *****/
			case 3: if (strcmp(workingNetwork, "FALSE") == 0 && strcmp(valuableData, "TRUE") == 0) s = 1;
				break;
				/* statement 4 */
				/***** comment 1550 *****/
			case 4: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 5 */
			case 5: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 6 */
			case 6: if (strcmp(var, "") == 0) s = 1;
				break;
				/***** comment 1610 *****/					// Ghost statements
				/* statement 7 */
			case 7: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 8 */
			case 8: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 9 */
			case 9: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 10 */
			case 10: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 11 */
			case 11: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 12 */
			case 12: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 13 */
			case 13: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 14 */
			case 14: if (strcmp(var, "") == 0) s = 1;
				break;
				/* statement 15 */
			case 15: if (strcmp(var, "") == 0) s = 1;
				break;
			}

			/* see if the THEN part should be inovked, i.e., s=1 */
			if (s != 1)
			{
				f = sn + 1;
				jump = true;
			}

			/* invoke THEN part */
			switch (sn && !jump)
			{
				/*********** comment 1500 ***********/
				/* put variable on the conclusion variable queue */
			case 1:
				strcpy(slowInternet, "TRUE");
				printf("SI=TRUE\n");
				strcpy(v, "SI");
				instantiate(&i, v, varlt, instlt, cndvar, &bp);
				break;
				/*********** comment 1510 ***********/
				/* put variable on the conclusion variable queue */
			case 2:
				strcpy(websiteNoAccess, "TRUE");
				printf("WNA=TRUE\n");
				strcpy(v, "WNA");
				instantiate(&i, v, varlt, instlt, cndvar, &bp);
				break;
				/*********** comment 1540 ***********/
				/* put variable on the conclusion variable queue */
			case 3:
				strcpy(notificationDataBreach, "TRUE");
				printf("NDB=TRUE\n");
				strcpy(v, "NDB");
				instantiate(&i, v, varlt, instlt, cndvar, &bp);
				break;
				/*********** comment 1550 ***********/
				/* put variable on the conclusion variable queue */
			case 4:
				break;
				/* put variable on the conclusion variable queue */
			case 5:
				break;
			case 6:
				break;
				/*********** comment 1610 ***********/
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;
			}
			f = sn + 1;
			jump = true;
		}

		/* no more clauses in the clause variable list (clvarlt)
		containing the variable in front of the queue (cndvar(fp))
		then remove front variable (cndvar(fp)) and replace it by
		the next variable (cndvar(fp+1)). If no more variables are
		at the front of the queue, stop. */
		/* next queue variable */
		if (jump == false) {
			fp = fp + 1;
			if (fp < bp)
			{
				/* check out the condition variable */
				f = 1;
				jump = true;
			}
			/* no more conclusion variables on queue */
		}

	} while (jump == true);
	std::cout << "\nEnd of forward chaining part\n";
	std::cin.get();
	return 0;
}

//==========================================================================
/* Routine to instantiate a variable (v) if it isn't already.
The instantiate indication (instlt) is a 0 if not, a 1 if it is.
The vriable list (varlt) contains the variable (v) */
void check_instantiation(int* index, char v[], char(&varlt)[numRules][charLength], int instlt[])
{
	int i = *index;

	i = 1;

	/* find variable in the variable list */
	while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i = i + 1;

	/* check if already instantiated */
	if (instlt[i] != 1)
	{
		/* mark instantiated */
		instlt[i] = 1;
		/* the designer of this knowledge base places the input
		statements to instantiate the variables in this case
		statement */

		switch (i)
		{
			/* input statements for sample position knowledge base */
		case 1:
			printf("TRUE OR FALSE FOR WORKING NETWORK? ");
			std::cin >> workingNetwork;
			break;
		case 2:
			printf("TRUE OR FALSE FOR VIABLE NETWORK EXPLANATION? ");
			std::cin >> viableNetworkExplanation;
			break;
		case 3:
			printf("TRUE OR FALSE FOR VALUABLE DATA? ");
			std::cin >> valuableData;
			break;
		}
	}
	/* end of input statements for the position knowledge base */

	*index = i;
}

//==========================================================================
/* Search clause variable list for a variable (clvarlt) equal to the
one in front of the conclusion queue (cndvar). Return the statement
number (sn). If there is no match, i.e., sn=0, the first statement
for the space is f. */
void search(int* flag, int* sn, int* f, int* fp, char(&clvarlt)[60][charLength], char(&cndvar)[numRules][charLength], int* cn, int* k)
{
	*flag = 0;
	*sn = *f;

	while ((*flag == 0) && (*sn <= 10))
	{
		*cn = 1;
		*k = (*sn - 1) * 4 + *cn;
		while ((strcmp(clvarlt[*k], cndvar[*fp]) != 0) && (*cn < 4))	// if variable in Conclusion variable queue is not equal to Clause variable
		{
			*cn = *cn + 1;
			*k = (*sn - 1) * 4 + *cn;
		}

		if (strcmp(clvarlt[*k], cndvar[*fp]) == 0) *flag = 1;
		if (*flag == 0) *sn = *sn + 1;
	}
	if (*flag == 0) *sn = 0;
}

//==========================================================================
/* Routine to instantiate a varialbe (v) and then place it on the
back of the queue (cndvar[bp]), if it is not already there. */
void instantiate(int* index, char v[], char(&varlt)[numRules][charLength], int instlt[], char(&cndvar)[numRules][charLength], int* bp)
{
	int i = *index;
	i = 1;
	/* find varialbe in the varialbe list (varlt) */
	while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i = i + 1;

	/* instantiate it */
	instlt[i] = 1;
	i = 1;

	/* determine if (v) is or already has been on the queue (cndvar) */
	while ((strcmp(v, cndvar[i]) != 0) && (i <= 10)) i = i + 1;
	/* variable has not been on the queue. Store it in the back of the queue */
	if (strcmp(v, cndvar[i]) != 0)
	{
		strcpy(cndvar[*bp], v);
		*bp = *bp + 1;
	}

	*index = i;
}
