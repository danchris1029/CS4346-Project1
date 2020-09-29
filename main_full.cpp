/*
	// NOTE: Compile using: g++ -std=c++11

	By: KirkWade Polasek, José Mayorga, Christian Guardiola

	Description:
*/


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cctype>
#include <queue>
#include "string.h"
#include <string> 
#include <unordered_map>

using namespace std;

typedef unordered_map<string, string> stringMap;

//void forward_chaining(stringMap& backVarList);
//stringMap backward_chaining();
void forward_chaining();
void backward_chaining();
const int numRules = 15; /* number of rules */
const int charLength = 20;

char var[charLength];
char access[charLength], downloaded[charLength], virus[charLength], breach[charLength], unexplained[charLength], sys[charLength], network[charLength],
explanation[charLength], logIn[charLength], device[charLength], normal[charLength], backdoor[charLength], trojan[charLength], credit[charLength], charges[charLength],
unusually[charLength], inability[charLength], malicious[charLength], basic[charLength], idAttack[charLength], idLeak[charLength], slow[charLength], ddos[charLength],
solution[charLength], valuable[charLength];


int main(int argc, char** argv) {

	cout << "Performing backward chaining to identify the type of attack.\n";

	// backVarList = backward_chaining();

	backward_chaining();

	cout << "Performing forward chaining to recommend possible preventions.\n";

	//forward_chaining(backVarList);

	forward_chaining();

	return 0;
}




/* instantiated list*/

// removed some global variables
void check_instantiation(int* index, char v[], char(&varlt)[11][charLength], int instlt[]);
void search(int* flag, int* sn, int* f, int* fp, char(&clvarlt)[91][charLength], char(&cndvar)[11][charLength], int* cn, int* k);
void instantiate_forward(int* index, char v[], char(&varlt)[11][charLength], int instlt[], char(&cndvar)[11][charLength], int* bp);

void forward_chaining()
{

	// Implementation: Produce the following; Knowledge base, clause variable list, variable list, conclusion variable queue and clause variable pointer.
   // Follow through using the results from backward_chaining(), meaning a variable must be passed in order to process the rules.
   // Traverse through the rules.

	queue <double> conclVarQue;

	/*
	BACKDOOR = BKD
	TROJAN = TRJ
	NORMAL = NRM
	DEVICE = DV
	CHARGES = CHG
	DROPPING = DRP
	SLOW = SL
	RESTARTED = RST
	INABILITY = INY
	SOLUTION = SLT
	*/

	string defaultVal = "UIN"; // uninitialized

	stringMap variableList;

	variableList = { {"BKD", defaultVal}, {"TRJ", defaultVal}, {"NRM", defaultVal}, {"DV", defaultVal}, \
	{"CHG", defaultVal}, {"DRP", defaultVal}, {"SL", defaultVal}, {"RST", defaultVal}, {"INY", defaultVal}, \
	{"SLT", defaultVal} }; // Created as a hash table with uninitialized values as default


	bool jump = false;

	int instlt[11];
	int flag;
	int f, i, j, k, s, fp   /* front pointer */;
	int  bp  /* back pointer */, gr /* grade */, sn; /* statement number */
	int cn;  /* clause number */
	char cndvar[11][charLength];
	char varlt[11][charLength], /* variable list*/ clvarlt[91][charLength]; /* clause var list */ // 4 * 15 =  60
	char c[charLength], vp[charLength], /* condition variable */  v[charLength]; /*variable */

	fp = 1;
	bp = 1;

	printf("HIT RETURN TO CONTINUE");
	getchar();

	// clause variables are inserted into clvarlt from the file "forward_clvarlt.txt"
	fstream clvarltFile;
	clvarltFile.open("forward_clvarlt.txt", fstream::in);
	string clauseVar;

	for (int i = 1; i <= 91; i++) {
		getline(clvarltFile, clauseVar);
		strcpy(clvarlt[i], clauseVar.c_str());
	}

	clvarltFile.close();

	for (i = 1; i <= 24; i++) {
		printf("** CLAUSE %d\n", i);
		for (j = 1; j < 4 + 1; j++)
		{
			k = 4 * (i - 1) + j;
			printf("VARIABLE %d  %s\n", j, clvarlt[k]);
		}
		// removed waiting at i = 4
	}

	printf("*** CLAUSE-VARIABLE LIST ***\n");
	for (i = 1; i < 24; i++)
	{
		printf("** CLAUSE %d\n", i);
		for (j = 1; j < 5; j++)
		{
			k = 4 * (i - 1) + j;
			printf("VARIABLE %d  %s\n", j, clvarlt[k]);
		}
		// removed waiting at i = 4
	}

	/****** INFERENCE SECTION *****************/
	printf("ENTER CONDITION VARIABLE? ");
	cin >> c;
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
			case 1: if (strcmp(backdoor, "NO") == 0) s = 1;
				break;
				/* statement 2 */
				/***** comment 1510 *****/
			case 2:
				break;
				/* statement 3 */
				/***** comment 1540 *****/
			case 3:
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
			}


			/* see if the THEN part should be inovked, i.e., s=1 */
			if (s != 1)
			{
				f = sn + 1;
				jump = true;
			}

			/* invoke THEN part */
			if (!jump) {
				switch (sn)
				{
					/*********** comment 1500 ***********/
					/* put variable on the conclusion variable queue */
				case 1:
					strcpy(solution, "TRUE");
					printf("SOLUTION = TRUE\n");
					strcpy(v, "SOLUTION");
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
					/*********** comment 1510 ***********/
					/* put variable on the conclusion variable queue */
				case 2:
					break;
					/*********** comment 1540 ***********/
					/* put variable on the conclusion variable queue */
				case 3:
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

				}

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
	cout << "\nEnd of forward chaining part\n";
}


//==========================================================================
/* Routine to instantiate a variable (v) if it isn't already.
The instantiate indication (instlt) is a 0 if not, a 1 if it is.
The vriable list (varlt) contains the variable (v) */
void check_instantiation(int* index, char v[], char(&varlt)[11][charLength], int instlt[])
{
	int i = *index;

	i = 1;

	/* find variable in the variable list */
	while ((strcmp(v, varlt[i]) != 0) && (i <= 11)) i = i + 1;

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
			printf("YES OR NO FOR BACKDOOR? ");
			cin >> backdoor;
			break;
		case 2:
			printf("YES OR NO FOR VAR? ");
			cin >> var;
			break;
		case 3:
			printf("YES OR NO FOR VAR? ");
			cin >> var;
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
void search(int* flag, int* sn, int* f, int* fp, char(&clvarlt)[91][charLength], char(&cndvar)[11][charLength], int* cn, int* k)
{
	*flag = 0;
	*sn = *f;

	while ((*flag == 0) && (*sn <= 11))
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
void instantiate_forward(int* index, char v[], char(&varlt)[11][charLength], int instlt[], char(&cndvar)[11][charLength], int* bp)
{
	int i = *index;
	i = 1;
	/* find varialbe in the varialbe list (varlt) */
	while ((strcmp(v, varlt[i]) != 0) && (i <= 11)) i = i + 1;

	/* instantiate it */
	instlt[i] = 1;
	i = 1;

	/* determine if (v) is or already has been on the queue (cndvar) */
	while ((strcmp(v, cndvar[i]) != 0) && (i <= 11)) i = i + 1;
	/* variable has not been on the queue. Store it in the back of the queue */
	if (strcmp(v, cndvar[i]) != 0)
	{
		strcpy(cndvar[*bp], v);
		*bp = *bp + 1;
	}

	*index = i;
}




//*********************************************************************************************************************
/*****backward chaining *******/
/* Enclosed a program, which comprises the inference engine based on backward chaining.You need it for your
project #1.  The program contains some errors and it is not designed to be efficient.
Modify the program to make it better and efficient.Explain in your report how you have modified the
program to make it better. */

/* Install your IF clauses in sequence in the first case
   statement of the main program
   example: if((a1==2) && (a2==6)) s=1;
					  if(strcmp(j,NO") != 0) s=1;
   the then part of the above construction always
   contains s=1;
   install your the clauses in sequence in the second
   case statement of the main program
   example strcpy(po,"YES");
 */

const int back_conclt_size = 24;
const int back_varlt_size = 18;

void determine_member_concl_list(int* index, int* f, int* sn, char varble[], char(&conclt)[back_conclt_size + 1][charLength]);
void push_on_stack(int* sp, int* sn, int statsk[], int clausk[]);
void instantiate_backward(int* index, char varble[], char varlt[][charLength], int instlt[]);

void backward_chaining()
{
	bool b520 = true;
	bool b545 = true;
	bool jump = false;

	/*  conclusion list */
	char conclt[back_conclt_size + 1][charLength];					// [number of elements in list][length of string]
	/*  variable list */
	char varlt[back_varlt_size + 1][charLength];
	/*  clause vairable list */
	char clvarlt[241][charLength];	// 4 * 15 =  60
	char varble[charLength];
	char buff[128];

	/* instantiated list */
	int instlt[back_varlt_size + 1];
	/* statement stack */
	int statsk[back_varlt_size + 1];
	int /* clause stack */ clausk[back_varlt_size + 1], sn, f, i, j, s, k, /*stack pointer */ sp;


	/***** initialization section ******/
	/* stack space is 10 we initially place stack space at 10+1 */
	sp = 11;
	sn = 0;
	for (i = 0; i <= back_conclt_size; i++)
	{
		strcpy(conclt[i], "");
		statsk[i] = 0;
		clausk[i] = 0;
	}
	for (i = 0; i <= back_varlt_size; i++)
	{
		strcpy(varlt[i], "");
		instlt[i] = 0;
	}


	for (i = 1; i <= 240; i++)  strcpy(clvarlt[i], "");
	/* enter conclusions which are the variables in the then part,
1 at
		a time.  enter the conclusions in exact order starting at the 1st
		if-then.  after last conclusion hit return key for rest of
		conclusions */

		/*** comment 305 *****/
	std::fstream conclusionListF;
	conclusionListF.open("backward_conclusionlist.txt", std::fstream::in);
	std::string c;

	for (int i = 1; i <= 24; i++) {
		getline(conclusionListF, c);
		strcpy(conclt[i], c.c_str());
	}

	conclusionListF.close();


	printf("*** CONCLUSION LIST ***\n");
	for (i = 1; i <= 24; i++) printf("CONCLUSION %d %s\n", i, conclt[i]);

	printf("HIT RETURN TO CONTINUE");
	fgets(buff, sizeof(buff), stdin);
	/* enter variables which are in the if part, 1 at a time in the
exact
		order that they occur, up to 3 variables per if statement.  do not
		duplicate any variable names.  any name is used only once.  if no
		more variables left just hit return key. */
	printf("*** VARIABLE LIST *\n");
	/**** comment 367 *****/
	fstream variableListF;
	variableListF.open("backward_variablelist.txt", std::fstream::in);

	for (int i = 1; i <= 18; i++) {
		getline(variableListF, c);
		strcpy(varlt[i], c.c_str());
	}

	variableListF.close();


	for (i = 1; i <= back_varlt_size; i++) printf("VARIABLE %d %s\n", i, varlt[i]);
	printf("HIT RETURN KEY TO CONTINUE");
	fgets(buff, sizeof(buff), stdin);
	/* enter variables as they appear in the if clauses.  a maximum
of 3
		variables per if statement.  if no more variables hit return
key. */
	printf("*** CLAUSE VARIABLE LIST ***\n");
	/***** comment 407 through 409 ***/
	/*
	strcpy(clvarlt[1], "SYSTEM");
	strcpy(clvarlt[2], "VIRUS");
	strcpy(clvarlt[3], "DOWNLOADED");
	strcpy(clvarlt[4], "BACKDOOR");
	strcpy(clvarlt[5], "TROJAN");

	strcpy(clvarlt[11], "SYSTEM");
	strcpy(clvarlt[12], "VIRUS");
	strcpy(clvarlt[13], "DOWNLOADED");
	strcpy(clvarlt[14], "BACKDOOR");
	strcpy(clvarlt[15], "DEVICE");
	strcpy(clvarlt[16], "NORMAL");
	strcpy(clvarlt[17], "TROJAN");

	strcpy(clvarlt[21], "SYSTEM");
	strcpy(clvarlt[22], "VIRUS");
	strcpy(clvarlt[23], "DOWNLOADED");
	strcpy(clvarlt[24], "DEVICE");
	strcpy(clvarlt[25], "NORMAL");
	strcpy(clvarlt[26], "TROJAN");

	strcpy(clvarlt[31], "SYSTEM");
	strcpy(clvarlt[32], "VIRUS");
	strcpy(clvarlt[33], "ACCESS");
	strcpy(clvarlt[34], "DOWNLOAD");
	strcpy(clvarlt[35], "BACKDOOR");
	strcpy(clvarlt[36], "TROJAN");

	strcpy(clvarlt[41], "SYSTEM");
	strcpy(clvarlt[42], "VIRUS");
	strcpy(clvarlt[43], "ACCESS");
	strcpy(clvarlt[44], "DOWNLOAD");
	strcpy(clvarlt[45], "BACKDOOR");
	strcpy(clvarlt[46], "DEVICE");
	strcpy(clvarlt[47], "NORMAL");
	strcpy(clvarlt[48], "TROJAN");

	strcpy(clvarlt[51], "SYSTEM");
	strcpy(clvarlt[52], "VIRUS");
	strcpy(clvarlt[53], "ACCESS");
	strcpy(clvarlt[54], "DOWNLOAD");
	strcpy(clvarlt[55], "DEVICE");
	strcpy(clvarlt[56], "NORMAL");
	strcpy(clvarlt[57], "TROJAN");

	strcpy(clvarlt[61], "SYSTEM");
	strcpy(clvarlt[62], "VIRUS");
	strcpy(clvarlt[63], "ACCESS");
	strcpy(clvarlt[64], "DEVICE");
	strcpy(clvarlt[65], "NORMAL");
	strcpy(clvarlt[66], "TROJAN");

	strcpy(clvarlt[71], "DEVICE");
	strcpy(clvarlt[72], "NORMAL");
	strcpy(clvarlt[73], "TROJAN");

	strcpy(clvarlt[81], "CHARGES");
	strcpy(clvarlt[82], "CREDIT");

	strcpy(clvarlt[101], "SYSTEM");
	strcpy(clvarlt[102], "BREACH");
	strcpy(clvarlt[103], "UNEXPLAINED");
	strcpy(clvarlt[104], "LOGIN");
	strcpy(clvarlt[105], "VIRUS");
	strcpy(clvarlt[106], "ACCESS");
	strcpy(clvarlt[107], "DEVICE");
	strcpy(clvarlt[108], "NORMAL");
	strcpy(clvarlt[109], "TROJAN");

	strcpy(clvarlt[111], "SYSTEM");
	strcpy(clvarlt[112], "BREACH");
	strcpy(clvarlt[113], "UNEXPLAINED");
	strcpy(clvarlt[114], "LOGIN");
	strcpy(clvarlt[115], "VIRUS");
	strcpy(clvarlt[116], "ACCESS");
	strcpy(clvarlt[117], "DEVICE");

	strcpy(clvarlt[121], "SYSTEM");
	strcpy(clvarlt[122], "BREACH");
	strcpy(clvarlt[123], "LOGIN");
	strcpy(clvarlt[124], "ACCESS");
	strcpy(clvarlt[125], "DOWNLOAD");
	strcpy(clvarlt[126], "DEVICE");
	strcpy(clvarlt[127], "NORMAL");
	strcpy(clvarlt[128], "TROJAN");

	strcpy(clvarlt[131], "SYSTEM");
	strcpy(clvarlt[132], "BREACH");
	strcpy(clvarlt[133], "LOGIN");
	strcpy(clvarlt[134], "ACCESS");
	strcpy(clvarlt[135], "DOWNLOAD");
	strcpy(clvarlt[136], "BACKDOOR");
	strcpy(clvarlt[137], "DEVICE");
	strcpy(clvarlt[138], "NORMAL");
	strcpy(clvarlt[139], "TROJAN");

	strcpy(clvarlt[141], "SYSTEM");
	strcpy(clvarlt[142], "BREACH");
	strcpy(clvarlt[143], "LOGIN");
	strcpy(clvarlt[144], "UNEXPLAINED");
	strcpy(clvarlt[145], "CHARGER");
	strcpy(clvarlt[146], "CREDIT");
	*/
	fstream clvarltFile;
	clvarltFile.open("backward_clvarlt.txt", fstream::in);
	string clauseVar;

	// GENERATE HASH

		/*
		ACCESS = ACS
		DOWNLOADED = DNL
		VIRUS = VR
		BREACH = BR
		UNEXPLAINED = UNE
		SYSTEM = SYS
		NETWORK = NTW
		EXPLANATION = EXP
		VALUABLE = VAL
		LOG-IN = LI
		DEVICE = DV
		NORMAL = NRM
		BACKDOOR = BKD
		TROJAN = TRJ
		CREDIT = CRD
		CHARGES = CHG
		UNUSUALLY = UNU
		INABILITY = INY
		*/

	stringMap backVarList;

	string defaultVal = "UIN"; // uninitialized

	backVarList = { {"ACS",defaultVal}, {"DNL",defaultVal}, {"VR",defaultVal}, {"BR",defaultVal}, {"UNE",defaultVal}, {"SYS",defaultVal}, \
				   {"NTW",defaultVal}, {"EXP",defaultVal}, {"VAL",defaultVal}, {"LI",defaultVal}, {"DV",defaultVal}, {"NRM",defaultVal}, \
				   {"BKD",defaultVal}, {"TRJ",defaultVal}, {"CRD",defaultVal}, {"CHG",defaultVal}, {"UNU",defaultVal}, {"INY",defaultVal} };





	for (int i = 1; i <= 240; i++) {
		getline(clvarltFile, clauseVar);
		strcpy(clvarlt[i], clauseVar.c_str());
	}

	clvarltFile.close();

	for (i = 1; i <= back_conclt_size; i++) {
		printf("** CLAUSE %d\n", i);
		for (j = 1; j < 10 + 1; j++)
		{
			k = 10 * (i - 1) + j;
			printf("VARIABLE %d  %s\n", j, clvarlt[k]);
		}
		// removed waiting at i = 4
	}
	/****** inference section *****/
	printf("** ENTER CONCLUSION ? "); cin >> varble;
	/* get conclusion statement number (sn) from the conclusion list
	   (conclt) */
	   /* first statement starts search */
	do { // b520
		f = 1;
		determine_member_concl_list(&i, &f, &sn, varble, conclt);
		if (sn != 0 || jump == true) {
			/* if sn = 0 then no conclusion of that name */ do
				/* push statement number (sn) and clause number=1 on
				goal
						 stack which is composed of the statement stack
					(statsk)
						 and clause stack (clausk) */
			{
				if (jump == false)
					push_on_stack(&sp, &sn, statsk, clausk);
				do
				{
					/* calculate clause location in clause-variable
					   list */
					jump = false;
					i = (statsk[sp] - 1) * 10 + clausk[sp]; // b545
					/* clause variable */
					strcpy(varble, clvarlt[i]);
					if (strcmp(varble, "") != 0) {
						/*is this clause variable a conclusion? */
						f = 1;
						determine_member_concl_list(&i, &f, &sn, varble, conclt);
						if (sn != 0) {
							/* it is a conclusion push it */
							jump = true;
							break;
						}
						/* check instantiation of this clause */
						instantiate_backward(&i, varble, varlt, instlt);
						clausk[sp] = clausk[sp] + 1;
					}
				} while (strcmp(varble, "") != 0); /*do-while*/
				if (jump)
					break;
				/*no more clauses check if part of statement */
				sn = statsk[sp];
				s = 0;

				char Y[] = "YES";			// YES or NO char arrays
				char N[] = "NO";
				/**** if then statements ****/
				/* sample if parts of if then statements from
				   the position knowledge base */
				switch (sn) {
					/* if part of statement 1 */
					/****** comment 1500 ****/

				// Use the knowledge base on the google docs
					/* statement 1 */

				case 1: if (strcmp(sys, Y) == 0 && strcmp(virus, Y) == 0 && strcmp(downloaded, Y) == 0
					&& strcmp(backdoor, Y) == 0 && strcmp(trojan, N) == 0) s = 1;
					break;
					/* statement 2 */
				case 2: if (strcmp(sys, Y) == 0 && strcmp(virus, Y) == 0 && strcmp(downloaded, Y) == 0
					&& strcmp(backdoor, N) == 0 && strcmp(device, N) == 0 && strcmp(normal, N) == 0 && strcmp(trojan, N) == 0) s = 1;
					break;
					/* statement 3 */
				case 3: if (strcmp(sys, Y) == 0 && strcmp(virus, Y) == 0 && strcmp(downloaded, N) == 0
					&& strcmp(device, N) == 0 && strcmp(normal, N) == 0 && strcmp(trojan, N) == 0) s = 1;
					break;
					/* statement 4 */
					/***** comment 1550 *****/
				case 4: if (strcmp(sys, Y) == 0 && strcmp(virus, N) == 0 && strcmp(access, Y) == 0
					&& strcmp(downloaded, Y) == 0 && strcmp(backdoor, Y) == 0 && strcmp(trojan, N) == 0) s = 1;
					break;
					/* statement 5 */
				case 5: if (strcmp(sys, Y) == 0 && strcmp(virus, N) == 0 && strcmp(access, Y) == 0
					&& strcmp(downloaded, Y) == 0 && strcmp(backdoor, N) == 0 && strcmp(device, N) == 0 && strcmp(normal, N) == 0
					&& strcmp(trojan, N) == 0) s = 1;
					break;
					/* statement 6 */
				case 6: if (strcmp(sys, Y) == 0 && strcmp(virus, N) == 0 && strcmp(access, Y) == 0
					&& strcmp(downloaded, N) == 0 && strcmp(device, N) == 0 && strcmp(normal, N) == 0
					&& strcmp(trojan, N) == 0) s = 1;
					break;
					/***** comment 1610 *****/					// Ghost statements
					/* statement 7 */
				case 7:	if (strcmp(sys, Y) == 0 && strcmp(virus, N) == 0 && strcmp(access, N) == 0
					&& strcmp(device, N) == 0 && strcmp(normal, N) == 0
					&& strcmp(trojan, N) == 0) s = 1;
					break;
					/* statement 8 */
				case 8: if (strcmp(device, Y) == 0 && strcmp(normal, Y) == 0
					&& strcmp(trojan, Y) == 0) s = 1;
					break;
					/* statement 9 */
				case 9: if (strcmp(charges, Y) == 0 && strcmp(credit, Y) == 0) s = 1;
					break;
					/* statement 10 */
				case 10:  if (strcmp(sys, N) == 0 && strcmp(breach, N) == 0 && strcmp(logIn, N) == 0
					&& strcmp(virus, N) == 0 && strcmp(access, N) == 0 && strcmp(device, N) == 0
					&& strcmp(normal, N) == 0 && strcmp(trojan, N) == 0) s = 1;
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
				case 16: if (strcmp(var, "") == 0) s = 1;
					break;
				case 17: if (strcmp(var, "") == 0) s = 1;
					break;
				case 18: if (strcmp(var, "") == 0) s = 1;
					break;
				case 19: if (strcmp(var, "") == 0) s = 1;
					break;
				case 20: if (strcmp(var, "") == 0) s = 1;
					break;
				case 21: if (strcmp(var, "") == 0) s = 1;
					break;
				case 22: if (strcmp(var, "") == 0) s = 1;
					break;
				case 23: if (strcmp(var, "") == 0) s = 1;
					break;
				case 24: if (strcmp(var, "") == 0) s = 1;
					break;

				}
				/* see if the then part should be invoked */
				if (s != 1) {
					/* failed..search rest of statements for
					   same conclusion */
					   /* get conclusion */
					i = statsk[sp];
					strcpy(varble, conclt[i]);
					/* search for conclusion starting at the
					   next statement number */
					f = statsk[sp] + 1;
					determine_member_concl_list(&i, &f, &sn, varble, conclt);
					sp = sp + 1;
				}
				/* pop old conclusion and put on new one */
			} while ((s != 1) && (sn != 0));  /* outer do-while loop */
			if (sn != 0) {
				/* if part true invoke then part */
				/* then part of if-then statements from the
				   position knowledge base */
				switch (sn) {
					/* then part of statement 1 */
					/******* comment 1500 *******/
				case 1: strcpy(malicious, "YES");
					printf("MALICIOUS = YES");
					break;
					/* then part of statement 2 */
					/****** comment 1510 ******/
				case 2:
					break;
					/* then part of statement 3 */
				case 3:
					break;
					/****** comment 1680 ********/
				}
				/* pop the stack */
				sp = sp + 1;
				if (sp >= 11) {
					/* finished */
					printf("*** SUCCESS\n");
					break;
				}

				else {
					/* stack is not empty */
					/* get next clause then continue */
					clausk[sp] = clausk[sp] + 1;
				}
			}
			if (sn == 0) {
				printf("\n*** NOT SUCCESSFUL\n");
				break;

			}
		}
	} while (true);
	cout << "\nEnd of backward chaining part\n";
	//return(backVarList);
}

/*
* varble: char array of variable name
* conclt: 2-d char array of conclusion list
*/
void determine_member_concl_list(int* index, int* f, int* sn, char varble[], char(&conclt)[back_conclt_size + 1][charLength]) {
	/* routine to determine if a variable (varble) is a member of the
	   conclusion list (conclt).  if yes return sn != 0.
	   if not a member sn=0;
	*/
	/* initially set to not a member */
	int i = *index;
	*sn = 0;
	/* member of conclusion list to be searched is f */
	i = *f;
	while ((strcmp(varble, conclt[i]) != 0) && (i <= back_conclt_size))
		/* test for membership */
		i = i + 1;
	if (strcmp(varble, conclt[i]) == 0) *sn = i;  /* a member */

	*index = i;
}

/*
* statsk: int array for statement stack
* clausk: int array of clause stack
*/
void push_on_stack(int* sp, int* sn, int statsk[], int clausk[])
/* routine to push statement number (sn) and a clause number of 1 onto the
conclusion stack which consists of the statement stack (statsk) and the
clause stack (clausk)..to push decrement stack pointer (sp) */
{
	*sp = *sp - 1;
	statsk[*sp] = *sn;
	clausk[*sp] = 1;
}

/*
* varble: char array of variable name
* varlt: 2-d char array for variable list
* instlt: int array for instantiated list
*/
void instantiate_backward(int* index, char varble[], char varlt[][charLength], int instlt[])
/* routine to instantiate a variable (varble) if it isn't already.  the
instantiate indication (instlt) is a 0 if not, a 1 if it is.  the
variable list (varlt) contains the variable (varble). */
{
	int i = *index;
	i = 1;
	/* find variable in the list */
	while ((strcmp(varble, varlt[i]) != 0) && (i <= back_conclt_size)) i = i + 1;
	if ((strcmp(varble, varlt[i]) == 0) && (instlt[i] != 1))
		/*found variable and not already instantiated */
	{
		instlt[i] = 1; /*mark instantiated */
		/* the designer of the
	   knowledge base places the input statements to
	   instantiate the variables below in the case statement */
		switch (i)
		{
			/***** input statement *****/
			/* input statements for sample position knowledge
			   base */
			   /***** comment 1700 ******/

		// use these
			/*
		strcpy(varlt[1], "ACCESS");
		strcpy(varlt[2], "DOWNLOADED");
		strcpy(varlt[3], "VIRUS");
		strcpy(varlt[4], "BREACH");
		strcpy(varlt[5], "UNEXPLAINED");
		strcpy(varlt[6], "SYSTEM");
		strcpy(varlt[7], "NETWORK");
		strcpy(varlt[8], "EXPLANATION");
		strcpy(varlt[9], "VALUABLE");
		strcpy(varlt[10], "LOGIN");
		strcpy(varlt[11], "DEVICE");
		strcpy(varlt[12], "NORMAL");
		strcpy(varlt[13], "BACKDOOR");
		strcpy(varlt[14], "TROJAN");
		strcpy(varlt[15], "CREDIT");
		strcpy(varlt[16], "CHARGES");
		strcpy(varlt[17], "UNUSUALLY");
		strcpy(varlt[18], "INABILITY");
		*/

		case 1: printf("INPUT YES OR NO FOR ACCESS? ");
			cin >> access;
			break;
		case 2: printf("INPUT YES OR NO FOR DOWNLOADED? ");
			cin >> downloaded;
			break;
		case 3: printf("INPUT YES OR NO FOR VIRUS? ");
			cin >> virus;
			break;
		case 4: printf("INPUT YES OR NO FOR BREACH? ");
			cin >> breach;
			break;
		case 5: printf("INPUT YES OR NO FOR UNEXPLAINED? ");
			cin >> unexplained;
			break;
		case 6: printf("INPUT YES OR NO FOR SYSTEM? ");
			cin >> sys;
			break;
		case 7: printf("INPUT YES OR NO FOR NETWORK? ");
			cin >> network;
			break;
		case 8: printf("INPUT YES OR NO FOR EXPLANATION? ");
			cin >> explanation;
			break;
		case 9: printf("INPUT YES OR NO FOR VALUABLE? ");
			cin >> valuable;
			break;
		case 10: printf("INPUT YES OR NO FOR LOGIN? ");
			cin >> logIn;
			break;
		case 11: printf("INPUT YES OR NO FOR DEVICE? ");
			cin >> device;
			break;
		case 12: printf("INPUT YES OR NO FOR NORMAL? ");
			cin >> normal;
			break;
		case 13: printf("INPUT YES OR NO FOR BACKDOOR? ");
			cin >> backdoor;
			break;
		case 14: printf("INPUT YES OR NO FOR TROJAN? ");
			cin >> trojan;
			break;
		case 15: printf("INPUT YES OR NO FOR CREDIT? ");
			cin >> credit;
			break;
		case 16: printf("INPUT YES OR NO FOR CHARGES? ");
			cin >> charges;
			break;
		case 17: printf("INPUT YES OR NO FOR UNUSUALLY? ");
			cin >> unusually;
			break;
		case 18: printf("INPUT YES OR NO FOR INABILITY? ");
			cin >> inability;
			break;


			/***** comment 1715 ****/
		}
		/* end of inputs statements for sample position knowledge
		   base */
	}
	*index = i;
}




