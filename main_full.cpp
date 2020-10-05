// Updated 10/4/2020 8:07 PM. 
/*
	// NOTE:
	Have these files in the same folder as this cpp file:
			backward_clvarlt.txt
			backward_conclusionlist.txt
			backward_variablelist.txt
			forward_clvarlt.txt
			forward_variablelist.txt

	Compile using: g++ -o <exe name> main_full.cpp -std=c++11

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
void Prevention_FW();
void Attacks_BW();


string var;


string access, downloaded, virus, breach, unexplained, sys, network,
explanation, logIn, device, normal, backdoor1, backdoor2, trojan, credit, charges,
unusually, inability1, inability2, inability3, malicious, basic, idAttack, idLeak, slow1, slow2, ddos,
solution, valuable, dropping, restarted1, restarted2;



int main(int argc, char** argv) {

	cout << "Performing backward chaining to identify the type of attack.\n";

	Attacks_BW();

	cout << "Performing forward chaining to recommend possible preventions.\n";

	Prevention_FW();

	return 0;
}

const int forward_clvarlt_size = 96;
const int forward_varl_size = 13;


// removed some global variables
void check_instantiation(int* index, string v, string varlt[forward_varl_size + 1], int instlt[]);
void search(int* flag, int* sn, int* f, int* fp, string clvarlt[forward_clvarlt_size + 1], string cndvar[forward_varl_size + 1], int* cn, int* k);
void instantiate_forward(int* index, string v, string varlt[forward_varl_size + 1], int instlt[], string cndvar[forward_varl_size + 1], int* bp);



void Prevention_FW(string condition)
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

	int instlt[forward_varl_size + 1];
	int flag;
	int f, i, j, k, s, fp   /* front pointer */;
	int  bp  /* back pointer */, gr /* grade */, sn; /* statement number */
	int cn;  /* clause number */
	string cndvar[forward_varl_size + 1];
	string varlt[forward_varl_size + 1], /* variable list*/ clvarlt[forward_clvarlt_size + 1]; /* clause var list */ // 4 * 15 =  60
	string c, vp, /* condition variable */  v; /*variable */

	int forward_clause_size = 4;

	fp = 1;
	bp = 1;


	//cout << "HIT RETURN TO CONTINUE" << endl;
	//getchar();

	// clause variables are inserted into clvarlt from the file "forward_clvarlt.txt"		



	fstream variablelistFile;
	variablelistFile.open("forward_variablelist.txt", fstream::in);
	string variable;

	for (int i = 1; i <= forward_varl_size; i++) {
		getline(variablelistFile, variable);
		varlt[i] = variable.c_str();
	}

	cout << "*** VARIABLE LIST ***\n";
	for (j = 1; j <= forward_varl_size; j++)
		cout << "VARIABLE " << j << " " << varlt[j] << endl;

	variablelistFile.close();
	cout << "Press any key to continue\n";
	cin.get();

	fstream clvarltFile;
	clvarltFile.open("forward_clvarlt.txt", fstream::in);
	string clauseVar;

	for (int i = 1; i <= forward_clvarlt_size; i++) {
		getline(clvarltFile, clauseVar);
		clvarlt[i] = clauseVar.c_str();
	}

	clvarltFile.close();

	/*for (i = 1; i <= 24; i++) {
		cout << "** CLAUSE " << i << endl;
			for (j = 1; j < forward_clause_size + 1; j++)
			{
				k = forward_clause_size * (i - 1) + j;
				cout << "VARIABLE " << j <<  " " <<  clvarlt[k] << endl;
			}
		// removed waiting at i = 4
	}*/

	cout << "*** CLAUSE-VARIABLE LIST ***\n";
	for (i = 1; i <= 24; i++)
	{
		cout << "** CLAUSE " << i << endl;
		for (j = 1; j <= 4; j++)
		{
			k = forward_clause_size * (i - 1) + j;
			cout << "VARIABLE " << j << " " << clvarlt[k] << endl;
		}
		// removed waiting at i = 4
	}

	/****** INFERENCE SECTION *****************/


	while (true) {
		int leave = 0;
		cout << "ENTER CONDITION VARIABLE? " << endl;
		cin >> c;
		for (int k = 1; k <= forward_varl_size; k++) {
			if (varlt[k] == c) {
				leave = 1;
				break;
			}
		}
		if (leave)
			break;
		cout << "\nNOT A CONDITION VARIABLE " << endl;
	}
	/* place condition variable c on condition var queue cndvar */
	cndvar[bp] = c;
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
		cn = 1;
		search(&flag, &sn, &f, &fp, clvarlt, cndvar, &cn, &k);
		/* point to first clause in statement */
		if (sn != 0) {
			/* more statements */
			/* locate the clause */
			i = forward_clause_size * (sn - 1) + cn;
			/* clause variable */
			v = clvarlt[i];
			/* are there any more clauses for this statement */
			while (v != "")
				/* more clauses */
			{
				/* check instantiation of this clause */
				check_instantiation(&i, v, varlt, instlt);
				cn = cn + 1;
				/* check next clause */
				i = forward_clause_size * (sn - 1) + cn;
				v = clvarlt[i];
			}

			/* no more clauses - check IF part of statement */
			s = 0;
			/* sample IF-THEN statements from the position knowledge base */
			string N = "NO";
			string Y = "YES";

			switch (sn)
			{
				/* statement 1 */
			case 1:
				if (condition == "MALICIOUS" && backdoor2 == N) s = 1;
				break;
				/* statement 2 */
			case 2:
				if (condition == "MALICIOUS" && device == N) s = 1;
				break;
				/* statement 3 */
			case 3:
				if (condition == "IDENTITY" && dropping == N) s = 1;
				break;
				/* statement 4 */
			case 4: if (condition == "SLOW" && slow1 == N) s = 1;
				break;
				/* statement 5 */
			case 5: if (condition == "DDOS" && inability3 == N) s = 1;
				break;
				/* statement 6 */
			case 6: if (condition == "DDOS" && restarted2 == Y && inability1 == N) s = 1;
				break;
			case 7: if (condition == "DDOS" && restarted2 == N && inability1 == N) s = 1;
				break;
			case 8: if (condition == "DDOS" && inability1 == Y && inability2 == N) s = 1;
				break;
			case 9: if (condition == "SLOW" && restarted1 == N && slow1 == N) s = 1;
				break;
			case 10: if (condition == "SLOW" && restarted1 == Y && slow1 == N) s = 1;
				break;
			case 11: if (condition == "SLOW" && restarted1 == Y && slow1 == Y) s = 1;
				break;
			case 12: if (slow1 == Y && slow2 == N) s = 1;
				break;
			case 13: if (slow1 == Y && slow2 == Y) s = 1;
				break;
			case 14: if (charges == Y && dropping == Y) s = 1;
				break;
			case 15: if (charges == N && dropping == Y) s = 1;
				break;
			case 16: if (charges == N && dropping == N) s = 1;
				break;
			case 17: if (trojan == N && backdoor1 == N) s = 1;
				break;
			case 18: if (trojan == Y && normal == Y) s = 1;
				break;
			case 19: if (trojan == Y && normal == N && device == N) s = 1;
				break;
			case 20: if (trojan == Y && normal == N && device == Y) s = 1;
				break;
			case 21: if (trojan == Y && backdoor1 == Y && backdoor2 == Y) s = 1;
				break;
			case 22: if (trojan == Y && backdoor1 == Y && backdoor2 == N) s = 1;
				break;
			case 23: if (inability1 == Y && inability2 == Y && inability3 == Y) s = 1;
				break;
			case 24: if (inability1 == Y && inability2 == Y && inability3 == N) s = 1;
				break;

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
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
					/* put variable on the conclusion variable queue */

				case 2:
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
					/* put variable on the conclusion variable queue */
				case 3:
					solution = "YES";
					cout << "PROBLEM SOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
					/* put variable on the conclusion variable queue */
				case 4:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
					/* put variable on the conclusion variable queue */
				case 5:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 6:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 7:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 8:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 9:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 10:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 11:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 12:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 13:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 14:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 15:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 16:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 17:
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 18:
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 19:
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 20:
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 21:
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 22:
					solution = "NO";
					cout << "PROBLEM UNSOLVED\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 23:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
				case 24:
					solution = "YES";
					cout << "SOLUTION = YES\n";
					v = "SOLUTION";
					instantiate_forward(&i, v, varlt, instlt, cndvar, &bp);
					break;
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
		if (jump == false && sn != 0) {
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
	//if (v == "")
	//	cout << "\nNO SOLUTIONS FOUND" << endl;
	cout << "\nEnd of forward chaining part\n";
}


//==========================================================================

/* Routine to instantiate a variable (v) if it isn't already.
The instantiate indication (instlt) is a 0 if not, a 1 if it is.
The variable list (varlt) contains the variable (v) */
void check_instantiation(int* index, string v, string varlt[forward_varl_size + 1], int instlt[])
{
	int i = *index;

	i = 1;

	/* find variable in the variable list */
	while (v != varlt[i] && (i <= forward_varl_size)) i = i + 1;

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
			cout << "YES OR NO FOR BACKDOOR? ";
			cin >> backdoor1;
			if (backdoor1 == "YES")
				cout << "Install the free Total AV. Use this to scan your system.";
			break;
		case 2:
			cout << "YES OR NO FOR DEVICE? ";
			cin >> device;
			if (device == "YES")
				cout << "Use the Active Directory and make your network use a Host-based firewall" << endl;
			break;
		case 3:
			cout << "YES OR NO FOR DROPPING? ";
			cin >> dropping;
			if (dropping == "YES")
				cout << "Change affected login account credentials. Contact your financial institution." << endl;
			break;
		case 4:
			cout << "YES OR NO FOR SLOW? ";
			cin >> slow1;
			if (slow1 == "YES")
				cout << "Restart System." << endl;
			break;
		case 5:
			cout << "YES OR NO FOR INABILITY? ";
			cin >> inability1;
			if (inability1 == "YES")
				cout << "Configure your firewall or router to drop incoming ICMP packets or block DNS responses." << endl;
			break;
		case 6:
			cout << "YES OR NO FOR RESTARTED? ";
			cin >> restarted1;
			if (restarted1 == "NO")
				cout << "Restart Router" << endl;
			break;
		case 7:
			cout << "YES OR NO FOR RESTARTED? ";
			cin >> restarted2;
			if (restarted2 == "YES")
				cout << "Restart Router" << endl;
			break;
		case 8:
			cout << "YES OR NO FOR SLOW? ";
			cin >> slow2;
			if (slow2 == "YES")
				cout << "Contact local network provider about better network solutions that they offer." << endl;
			break;
		case 9:
			cout << "YES OR NO FOR CHARGES? ";
			cin >> charges;
			if (charges == "YES")
				cout << "Change affected login account credentials. Contact your financial institution.s" << endl;
			break;
		case 10:
			cout << "YES OR NO FOR TROJAN? ";
			cin >> trojan;
			break;
		case 11:
			cout << "YES OR NO FOR NORMAL? ";
			cin >> normal;
			if (normal == "YES")
				cout << "Using secpol.msc, Automatically deny elevation requests." << endl;
			break;
		case 12:
			cout << "YES OR NO FOR BACKDOOR? ";
			cin >> backdoor2;
			if (backdoor2 == "YES")
				cout << "Factory reset your system to remove all extra added software or use a restore point." << endl;
			break;
		case 13:
			cout << "YES OR NO FOR INABILITY? ";
			cin >> inability2;
			if (inability2 == "YES")
				cout << "Move to a cloud-baesd DNS provider that can offer high  band width and multiple points-of-presence in data centers around the world." << endl;
			break;
		case 14:
			cout << "YES OR NO FOR INABILITY? ";
			cin >> inability3;
			if (backdoor2 == "YES")
				cout << "Akamai's DDoS mitigation." << endl;
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
void search(int* flag, int* sn, int* f, int* fp, string clvarlt[forward_clvarlt_size + 1], string cndvar[forward_varl_size + 1], int* cn, int* k)
{
	*flag = 0;
	*sn = *f;

	while ((*flag == 0) && (*sn <= 24))
	{
		*cn = 1;
		*k = (*sn - 1) * 4 + *cn;
		while (clvarlt[*k] != cndvar[*fp] && (*cn <= 4))	// if variable in Conclusion variable queue is not equal to Clause variable
		{
			*cn = *cn + 1;
			*k = (*sn - 1) * 4 + *cn;
		}

		if (clvarlt[*k] == cndvar[*fp]) *flag = 1;
		if (*flag == 0) *sn = *sn + 1;
	}
	if (*flag == 0) *sn = 0;
}

//==========================================================================
/* Routine to instantiate a varialbe (v) and then place it on the
back of the queue (cndvar[bp]), if it is not already there. */
void instantiate_forward(int* index, string v, string varlt[forward_varl_size + 1], int instlt[], string cndvar[forward_varl_size + 1], int* bp)
{
	int i = *index;
	i = 1;
	/* find varialbe in the varialbe list (varlt) */
	while ((v != varlt[i]) && (i <= forward_varl_size)) i = i + 1;

	/* instantiate it */
	instlt[i] = 1;
	i = 1;

	/* determine if (v) is or already has been on the queue (cndvar) */
	while ((v != cndvar[i]) && (i <= forward_varl_size)) i = i + 1;
	/* variable has not been on the queue. Store it in the back of the queue */
	if (v != cndvar[i])
	{
		cndvar[*bp] = v;
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
					  if(j != "NO") s=1;
   the then part of the above construction always
   contains s=1;
   install your the clauses in sequence in the second
   case statement of the main program
 */

const int back_conclt_size = 24;
const int back_varlt_size = 18;

void determine_member_concl_list(int* index, int* f, int* sn, string varble, string conclt[]);
void push_on_stack(int* sp, int* sn, int statsk[], int clausk[]);
void instantiate_backward(int* index, string varble, string varlt[], int instlt[]);


void Attacks_BW()
{
	bool b520 = true;
	bool b545 = true;
	bool jump = false;

	/*  conclusion list */
	string conclt[back_conclt_size + 1];					// [number of elements in list][length of string]
	/*  variable list */
	string varlt[back_varlt_size + 1];
	/*  clause vairable list */
	string clvarlt[241];	// 4 * 15 =  60
	string varble;

	int back_clause_size = 10;

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
		conclt[i] = "";
		statsk[i] = 0;
		clausk[i] = 0;
	}
	for (i = 0; i <= back_varlt_size; i++)
	{
		varlt[i] = "";
		instlt[i] = 0;
	}


	for (i = 1; i <= 240; i++)  clvarlt[i] = "";
	fstream conclusionListF;
	conclusionListF.open("backward_conclusionlist.txt", fstream::in);
	string c;

	for (int i = 1; i <= 24; i++) {
		getline(conclusionListF, c);
		conclt[i] = c;
	}

	conclusionListF.close();


	cout << "*** CONCLUSION LIST ***\n";
	for (i = 1; i <= 24; i++) cout << "CONCLUSION " << i << " " << conclt[i] << endl;

	cout << "HIT RETURN TO CONTINUE" << endl;
	cin.get();
	cout << "*** VARIABLE LIST *\n";
	/**** comment 367 *****/
	fstream variableListF;
	variableListF.open("backward_variablelist.txt", fstream::in);

	for (int i = 1; i <= back_varlt_size; i++) {
		getline(variableListF, c);
		varlt[i] = c;
	}

	variableListF.close();


	for (i = 1; i <= back_varlt_size; i++) cout << "VARIABLE " << i << " " << varlt[i] << endl;
	cout << "HIT RETURN KEY TO CONTINUE" << endl;
	cin.get();
	cout << "*** CLAUSE VARIABLE LIST ***\n";
	/***** comment 407 through 409 ***/

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
		clvarlt[i] = clauseVar;
	}

	clvarltFile.close();

	for (i = 1; i <= back_conclt_size; i++) {
		cout << "** CLAUSE " << i << endl;
		for (j = 1; j < back_clause_size + 1; j++)
		{
			k = back_clause_size * (i - 1) + j;
			cout << "VARIABLE " << j << " " << clvarlt[k] << endl;
		}
		// removed waiting at i = 4
	}
	/****** inference section *****/
	cout << "** ENTER CONCLUSION ? ";
	cin >> varble;
	/* get conclusion statement number (sn) from the conclusion list
	   (conclt) */
	   /* first statement starts search */
	do { // b520
		f = 1;
		determine_member_concl_list(&i, &f, &sn, varble, conclt);
		/* if sn = 0 then no conclusion of that name */
		if (sn != 0 || jump == true) {

			do
			{
				if (jump == false)
					push_on_stack(&sp, &sn, statsk, clausk);
				/* push statement number (sn) and clause number=1 on
				goal stack which is composed of the statement stack (statsk) and clause stack (clausk) */

				do
				{

					jump = false;
					/* calculate clause location in clause-variable
					   list */
					i = (statsk[sp] - 1) * back_clause_size + clausk[sp]; // b545
					/* clause variable */
					varble = clvarlt[i];
					if (varble != "") {
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
				} while (varble != ""); /*do-while*/
				if (jump)
					break;
				/*no more clauses check if part of statement */
				sn = statsk[sp];
				s = 0;

				string Y = "YES";			// YES or NO char arrays
				string N = "NO";
				/**** if then statements ****/
				/* if parts of if then statements from
				   the position knowledge base */
				switch (sn) {
					/* if part of statement 1 */

				// Use the knowledge base on the google docs
					/* statement 1 */
				case 1: if (sys.compare(Y) == 0 && virus.compare(Y) == 0 && downloaded.compare(Y) == 0
					&& backdoor1.compare(Y) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 2 */
				case 2: if (sys.compare(Y) == 0 && virus.compare(Y) == 0 && downloaded.compare(Y) == 0
					&& backdoor1.compare(N) == 0 && device.compare(N) == 0 && normal.compare(N) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 3 */
				case 3: if (sys.compare(Y) == 0 && virus.compare(Y) == 0 && downloaded.compare(N) == 0
					&& device.compare(N) == 0 && normal.compare(N) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 4 */
				case 4: if (sys.compare(Y) == 0 && virus.compare(N) == 0 && access.compare(Y) == 0
					&& downloaded.compare(Y) == 0 && backdoor1.compare(Y) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 5 */
				case 5: if (sys.compare(Y) == 0 && virus.compare(N) == 0 && access.compare(Y) == 0
					&& downloaded.compare(Y) == 0 && backdoor1.compare(N) == 0 && device.compare(N) == 0 && normal.compare(N) == 0
					&& trojan.compare(N) == 0) s = 1;
					break;
					/* statement 6 */
				case 6: if (sys.compare(Y) == 0 && virus.compare(N) == 0 && access.compare(Y) == 0
					&& downloaded.compare(N) == 0 && device.compare(N) == 0 && normal.compare(N) == 0
					&& trojan.compare(N) == 0) s = 1;
					break;
					/* statement 7 */
				case 7:	if (sys.compare(Y) == 0 && virus.compare(N) == 0 && access.compare(N) == 0
					&& device.compare(N) == 0 && normal.compare(N) == 0
					&& trojan.compare(N) == 0) s = 1;
					break;
					/* statement 8 */
				case 8: if (device.compare(Y) == 0 && normal.compare(Y) == 0
					&& trojan.compare(Y) == 0) s = 1;
					break;
					/* statement 9 */
				case 9: if (charges.compare(Y) == 0 && credit.compare(Y) == 0) s = 1;
					break;
					/* statement 10 */
				case 10:  if (sys.compare(N) == 0 && breach.compare(N) == 0 && logIn.compare(N) == 0
					&& virus.compare(N) == 0 && access.compare(N) == 0 && device.compare(N) == 0
					&& normal.compare(N) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 11 */

				case 11: if (sys.compare(N) == 0 && breach.compare(Y) == 0 && unexplained.compare(N) == 0
					&& logIn.compare(N) == 0 && virus.compare(N) == 0 && access.compare(N) == 0
					&& device.compare(N) == 0 && normal.compare(N) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 12 */
				case 12: if (sys.compare(N) == 0 && breach.compare(Y) == 0 && logIn.compare(Y) == 0
					&& access.compare(Y) == 0 && downloaded.compare(Y) == 0 && backdoor1.compare(Y) == 0
					&& trojan.compare(N) == 0 && normal.compare(N) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 13 */
				case 13: if (sys.compare(N) == 0 && breach.compare(N) == 0 && logIn.compare(Y) == 0
					&& access.compare(Y) == 0 && downloaded.compare(N) == 0 && device.compare(N) == 0
					&& normal.compare(N) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 14 */
				case 14: if (sys.compare(N) == 0 && breach.compare(N) == 0 && logIn.compare(Y) == 0
					&& access.compare(Y) == 0 && downloaded.compare(Y) == 0 && backdoor1.compare(N) == 0
					&& device.compare(N) == 0 && normal.compare(N) == 0 && trojan.compare(N) == 0) s = 1;
					break;
					/* statement 15 */
				case 15: if (sys.compare(N) == 0 && breach.compare(N) == 0 && logIn.compare(Y) == 0
					&& logIn.compare(Y) == 0 && unexplained.compare(Y) == 0 && charges.compare(N) == 0
					&& credit.compare(N) == 0) s = 1;
					break;
				case 16: if (sys.compare(N) == 0 && breach.compare(N) == 0 && logIn.compare(Y) == 0
					&& unexplained.compare(Y) == 0 && charges.compare(N) == 0
					&& credit.compare(Y) == 0) s = 1;
					break;
				case 17: if (sys.compare(N) == 0 && breach.compare(N) == 0 && logIn.compare(Y) == 0
					&& unexplained.compare(Y) == 0 && charges.compare(Y) == 0) s = 1;
					break;
				case 18: if (sys.compare(N) == 0 && breach.compare(Y) == 0
					&& unexplained.compare(Y) == 0 && charges.compare(N) == 0
					&& credit.compare(N) == 0) s = 1;
					break;
				case 19: if (sys.compare(N) == 0 && breach.compare(Y) == 0
					&& unexplained.compare(Y) == 0 && charges.compare(N) == 0
					&& credit.compare(Y) == 0) s = 1;
					break;
				case 20: if (sys.compare(N) == 0 && breach.compare(Y) == 0
					&& unexplained.compare(Y) == 0 && charges.compare(Y) == 0) s = 1;
					break;
				case 21: if (network.compare(Y) == 0 && explanation.compare(Y) == 0) s = 1;
					break;
				case 22: if (network.compare(Y) == 0 && explanation.compare(N) == 0 && inability1.compare(Y) == 0) s = 1;
					break;
				case 23: if (network.compare(Y) == 0 && explanation.compare(N) == 0 && inability1.compare(N) == 0 && unusually.compare(Y) == 0) s = 1;
					break;
				case 24: if (inability1.compare(N) == 0 && unusually.compare(N) == 0) s = 1;
					break;



				}
				/* see if the then part should be invoked */
				if (s != 1) {
					/* failed..search rest of statements for
					   same conclusion */
					   /* get conclusion */
					i = statsk[sp];
					varble = conclt[i];
					/* search for conclusion starting at the
					   next statement number */
					f = statsk[sp] + 1;
					determine_member_concl_list(&i, &f, &sn, varble, conclt);
					sp = sp + 1;
				}
				/* pop old conclusion and put on new one */
			} while ((s != 1) && (sn != 0));  /* outer do-while loop */
			if (sn != 0) {
				string Y = "YES";			// YES or NO char arrays
				string N = "NO";

				/* if part true invoke then part */
				/* then part of if-then statements from the
				   position knowledge base */
				switch (sn) {
					/* then part of statement 1 */
				case 1:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 2:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 3:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 4:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 5:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 6:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 7:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 8:
					basic = Y;
					cout << "BASIC = YES" << endl;
					break;
				case 9:
					idAttack = Y;
					cout << "IDATTACK = YES" << endl;
					break;
				case 10:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 11:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 12:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 13:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 14:
					malicious = Y;
					cout << "MALICIOUS = YES" << endl;
					break;
				case 15:
					idLeak = Y;
					cout << "IDLEAK = YES" << endl;
					break;
				case 16:
					idAttack = Y;
					cout << "IDATTACK = YES" << endl;
					break;
				case 17:
					idAttack = Y;
					cout << "IDATTACK = YES" << endl;
					break;
				case 18:
					idLeak = Y;
					cout << "IDLEAK = YES" << endl;
					break;
				case 19:
					idAttack = Y;
					cout << "IDATTACK = YES" << endl;
					break;
				case 20:
					idAttack = Y;
					cout << "IDATTACK = YES" << endl;
					break;
				case 21:
					slow1 = Y;
					cout << "SLOW = YES" << endl;
					break;
				case 22:
					ddos = Y;
					cout << "DDOS = YES" << endl;
					break;
				case 23:
					ddos = Y;
					cout << "DDOS = YES" << endl;
					break;
				case 24:
					slow1 = Y;
					cout << "SLOW = YES" << endl;
					break;
				}
				/* pop the stack */
				sp = sp + 1;
				if (sp >= 11) {
					/* finished */
					cout << "*** SUCCESS\n";
					break;
				}

				else {
					/* stack is not empty */
					/* get next clause then continue */
					clausk[sp] = clausk[sp] + 1;
				}
			}
			if (sn == 0) {
				cout << "\n*** NOT SUCCESSFUL\n";
				break;

			}

		}
		// If user entered a value which is not from the conclusion list.
		if (sn == 0) {
			cout << "\n** THE VALUE ENTERED IS NOT A CONCLUSION\n";
			cout << "** ENTER CONCLUSION ? "; cin >> varble;
		}

	} while (true);
	cout << "\nEnd of backward chaining part\n";
	cout << "\nPress any key to continue...";
	cin.get();
	cin.get();
	cout << endl;
	//return(backVarList);


}

//==========================================================================
/*
* varble: char array of variable name
* conclt: 2-d char array of conclusion list
*/
void determine_member_concl_list(int* index, int* f, int* sn, string varble, string conclt[]) {
	/* routine to determine if a variable (varble) is a member of the
	   conclusion list (conclt).  if yes return sn != 0.
	   if not a member sn=0;
	*/
	/* initially set to not a member */
	int i = *index;
	*sn = 0;
	/* member of conclusion list to be searched is f */
	i = *f;
	while (varble != conclt[i] && (i <= back_conclt_size))
		/* test for membership */
		i = i + 1;
	if (varble == conclt[i]) *sn = i;  /* a member */

	*index = i;
}

//==========================================================================
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

//==========================================================================
/*
* varble: char array of variable name
* varlt: 2-d char array for variable list
* instlt: int array for instantiated list
*/
void instantiate_backward(int* index, string varble, string varlt[], int instlt[])
/* routine to instantiate a variable (varble) if it isn't already.  the
instantiate indication (instlt) is a 0 if not, a 1 if it is.  the
variable list (varlt) contains the variable (varble). */
{
	int i = *index;
	i = 1;
	/* find variable in the list */
	while (varble != varlt[i] && (i <= back_conclt_size)) i = i + 1;
	if (varble == varlt[i] && (instlt[i] != 1))
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

		case 1: cout << "INPUT YES OR NO FOR ACCESS? ";
			cin >> access;
			break;
		case 2: cout << "INPUT YES OR NO FOR DOWNLOADED? ";
			cin >> downloaded;
			break;
		case 3: cout << "INPUT YES OR NO FOR VIRUS? ";
			cin >> virus;
			break;
		case 4: cout << "INPUT YES OR NO FOR BREACH? ";
			cin >> breach;
			break;
		case 5: cout << "INPUT YES OR NO FOR UNEXPLAINED? ";
			cin >> unexplained;
			break;
		case 6: cout << "INPUT YES OR NO FOR SYSTEM? ";
			cin >> sys;
			break;
		case 7: cout << "INPUT YES OR NO FOR NETWORK? ";
			cin >> network;
			break;
		case 8: cout << "INPUT YES OR NO FOR EXPLANATION? ";
			cin >> explanation;
			break;
		case 9: cout << "INPUT YES OR NO FOR VALUABLE? ";
			cin >> valuable;
			break;
		case 10: cout << "INPUT YES OR NO FOR LOGIN? ";
			cin >> logIn;
			break;
		case 11: cout << "INPUT YES OR NO FOR DEVICE? ";
			cin >> device;
			break;
		case 12: cout << "INPUT YES OR NO FOR NORMAL? ";
			cin >> normal;
			break;
		case 13: cout << "INPUT YES OR NO FOR backdoor1? ";
			cin >> backdoor1;
			break;
		case 14: cout << "INPUT YES OR NO FOR TROJAN? ";
			cin >> trojan;
			break;
		case 15: cout << "INPUT YES OR NO FOR CREDIT? ";
			cin >> credit;
			break;
		case 16: cout << "INPUT YES OR NO FOR CHARGES? ";
			cin >> charges;
			break;
		case 17: cout << "INPUT YES OR NO FOR UNUSUALLY? ";
			cin >> unusually;
			break;
		case 18: cout << "INPUT YES OR NO FOR INABILITY? ";
			cin >> inability1;
			break;


		}
		/* end of inputs statements for position knowledge
		   base */
	}
	*index = i;
}
