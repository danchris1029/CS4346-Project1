/*** FORWARD CHAINING ***/
/************************/
/* Install your IF clauses in sequence in the middle of the program within the first case statement.
EXAMPLE: IF ((A1==2) && (A2==6) || (A3 == 'YES')) S-1; IF (J=='NO') S-1;

 The THEN part of the above construction always contains S-1.
Install your THEN clauses in sequence in the middle of the program within the second case statement. */



#include <stdio.h>
#include "string.h"

int flag;
char cndvar[10][3];
char varlt[10][3], /* variable list*/
clvarlt[40][3];
/* clause var list */ char c[3], vp[3], /* condition variable */ v[3];
/*variable */ char fedint[10], interest[10], stock[10], dollar[10], fedmon[10];
char po[10], /* position */ qu[10];
/* qualify */ int instlt[10];
/* instantiated list*/ int f, i, j, k, s, fp /* front pointer */;
int bp /* back pointer */, gr /* grade */, sn;
/* statement number */ int cn;
/* clause number */ void search(void);
void check_instantiation(void);
void instantiate(void);

main()
{ /******** INITIALIZATION SECTION ***********/
	fp = 1;
	bp = 1;
	for (i = 1; i < 41; i++)
		strcpy(clvarlt[i], "");
	for (i = 1; i < 11; i++)
		strcpy(cndvar[i], "");
	for (i = 1; i < 11; i++)
		instlt[i] = 0;
	for (i = 1; i < 11; i++)
		strcpy(varlt[i], "");
	/* enter variables which are in the IF part, 1 at a time in the exact order that they occur. Up to 3 variables per IF statement. Do not duplicate any variable names. Any name is used only once. If no more variables left, just hit return key */
   /****** comment 367 *************/
	strcpy(varlt[1], "DO");
	strcpy(varlt[2], "FT");
	strcpy(varlt[3], "FM");
	strcpy(varlt[4], "IN");
	strcpy(varlt[5], "ST");
	printf("*** VARIABLE LIST ***\n");
	for (i = 1; i < 11; i++)
		printf("ENTER VARIABLE %d %s\n", i, varlt[i]);
	printf("HIT RETURN TO CONTINUE");
	getchar();
	/* enter variables as they appear in the IF clauses, Up to 3 variables per IF statement. If no more variables left, just hit return key */
	/****** comment 407, 408 *************/
	strcpy(clvarlt[1], "IN");
	strcpy(clvarlt[5], "IN");
	strcpy(clvarlt[9], "DO");
	strcpy(clvarlt[13], "DO");
	strcpy(clvarlt[17], "FT");
	strcpy(clvarlt[18], "FM");
	printf("*** CLAUSE-VARIABLE LIST ***\n");
	for (i = 1; i < 9; i++)
	{
		printf("** CLAUSE %d\n", i);
		for (j = 1; j < 5; j++)
		{
			k = 4 * (i - 1) + j;
			printf("VARIABLE %d %s\n", j, clvarlt[k]);
		}
		if (i == 4)
		{
			printf("HIT RETURN TO CONTINUE");
			getchar();
		}
	}
	/****** INFERENCE SECTION *****************/
	printf("ENTER CONDITION VARIABLE? ");
	gets(c);
	/* place condition variable c on condition var queue cndvar */
	strcpy(cndvar[bp], c);
	/* move backpointer (bp) to back */
	bp = bp + 1;
	/* set the condition variable pointer consisting of the statement number (sn) and the clause number (cn) */
	sn = 1;
	cn = 1;
	/* find the next statement number containing the condition variable which is in front of the queue (cndvar), this statement number is located in the clause variable list (clvarlt) */
	 /* start at the beginning */
	f = 1;
b496: search();
	/* point to first clause in statement */
	cn = 1;
	if (sn != 0)
		/* more statements */
	{
		/* locate the clause */
		i = 4 * (sn - 1) + cn;
		/* clause variable */
		strcpy(v, clvarlt[i]);
		/* are there any more clauses for this statement */
		while (strcmp(v, ""))
			/* more clauses */
		{
			/* check instantiation of this clause */
			check_instantiation();
			cn = cn + 1;
			/* check next clause */
			i = 4 * (sn - 1) + cn;
			strcpy(v, clvarlt[i]);
		}
		/* no more clauses - check IF part of statement */
		s = 0;Enclosed a program, which comprises the inference engine based on backward chaining.  You need it for your
project #1.  The program contains some errors and it is not designed to be efficient.
Modify the program to make it better and efficient.  Explain in your report how you have modified the
program to make it better.



/*****backward chaining *******/
/* Install your IF clauses in sequence in the first case
   statement of the main program
   example: if((a1==2) && (a2==6)) s=1;
                      if(strcmp(j,NO") != 0) s=1;
   the then part of the above construction always
   contains s=1;
   install your the clauses in sequence in the second
   case statement of the main program
   example strcpy(po,"YES");


/*  conclusion list */
char conclt[10][3];
/*  variable list */
char varlt[10][3];
/*  clause vairable list */
char clvarlt[40][3];
char varble[3];
char /* qualify */ qu[4], /* degree*/ de[4];
char /* discovery */ di[4], /* position */ po[4];
char buff[128];

/* instantiated list */
int instlt[11];
/* statement stack */
int statsk[11];
int /* clause stack */ clausk[11], sn, f, i, j, s, k, /*stack pointer */ sp;

float /* grade */ gr, /*experience */ ex;

void determine_member_concl_list(void);
void push_on_stack(void);
void instantiate(void);

main()
{
        /***** initialization section ******/
        /* stack space is 10 we initially place stack space at 10+1 */
        sp=11;
        for (i=1; i<11; i++)
        {
                strcpy(conclt[i],"");
                strcpy(varlt[i],"");
                instlt[i]=0;
                statsk[i]=0;
                clausk[i]=0;
        }
        for (i=1; i<41; i++)  strcpy(clvarlt[i],"");
        /* enter conclusions which are the variables in the then part,
1 at
        a time.  enter the conclusions in exact order starting at the 1st
        if-then.  after last conclusion hit return key for rest of
        conclusions */

        /*** comment 305 *****/
        strcpy(conclt[1], "PO");
        strcpy(conclt[2], "QU");
        strcpy(conclt[3], "PO");
        strcpy(conclt[4], "PO");
        strcpy(conclt[5], "PO");
        strcpy(conclt[6], "PO");
        printf("*** CONCLUSION LIST ***\n");
        for (i=1; i<11; i++) printf("CONCLUSION %d %s\n", i,conclt[i]);

        printf("HIT RETURN TO CONTINUE");
        gets(buff);
        /* enter variables which are in the if part, 1 at a time in the
exact
        order that they occur, up to 3 variables per if statement.  do not
        duplicate any variable names.  any name is used only once.  if no
        more variables left just hit return key. */
        printf("*** VARIABLE LIST *\n");
        /**** comment 367 *****/
        strcpy(varlt[1], "DE");
        strcpy(varlt[2], "DI");
        strcpy(varlt[3], "EX");
        strcpy(varlt[4], "GR");
        for(i=1; i<11; i++) printf("VARIABLE %d %s\n", i, varlt[i]);
        printf("HIT RETURN KEY TO CONTINUE");
        gets(buff);
        /* enter variables as they appear in the if clauses.  a maximum
of 3
        variables per if statement.  if no more variables hit return
key. */
        printf("*** CLAUSE VARIABLE LIST ***\n");
        /***** comment 407 through 409 ***/
        strcpy(clvarlt[1], "DE");
        strcpy(clvarlt[5], "DE");
        strcpy(clvarlt[9], "DE");
        strcpy(clvarlt[10], "DI");
        strcpy(clvarlt[13], "QU");
        strcpy(clvarlt[14], "GR");
        strcpy(clvarlt[15], "EX");
        strcpy(clvarlt[17], "QU");
        strcpy(clvarlt[18], "GR");
        strcpy(clvarlt[19], "EX");
        strcpy(clvarlt[21], "QU");
        strcpy(clvarlt[22], "GR");
        for(i=1; i<9; i++)
        {
                printf("** CLAUSE %d\n", i);
                for(j=1; j<5; j++)
                { k = 4 * (i-1) + j;
                  printf("VARIABLE %d  %s\n", j, clvarlt[k]); }
                if (i==4)
                { printf("HIT RETURN KEY TO CONTINUE"); gets(buff); }
        }
        /****** inference section *****/
        printf("** ENTER CONCLUSION ? "); gets(varble);
        /* get conclusion statement number (sn) from the conclusion list
           (conclt) */
        /* first statement starts search */
b520: f=1;
          determine_member_concl_list();
          if (sn != 0){
                  /* if sn = 0 then no conclusion of that name */ do
                  /* push statement number (sn) and clause number=1 on
goal
                     stack which is composed of the statement stack
(statsk)
                     and clause stack (clausk) */
                  {
                          push_on_stack();
                          do
                          {
                           /* calculate clause location in clause-variable
                              list */
b545: i= (statsk[sp] -1) *4 + clausk[sp];
          /* clause variable */
          strcpy(varble, clvarlt[i]);
          if(strcmp(varble, "") != 0) {
                  /*is this clause variable a conclusion? */
                  f = 1;
                  determine_member_concl_list();
                  if(sn != 0)
                          /* it is a conclusion push it */
                          goto b520;
                  /* check instantiation of this clause */
                  instantiate();
                  clausk[sp] = clausk[sp] + 1;
          }
                          } while(strcmp(varble, "") != 0); /*do-while*/
                          /*no more clauses check if part of statement */
                          sn = statsk[sp];
                          s = 0;
                          /**** if then statements ****/
                          /* sample if parts of if then statements from
                             the position knowledge base */
                          switch (sn) {
                                  /* if part of statement 1 */
                                  /****** comment 1500 ****/
                          case 1: if(strcmp(de, "NO") == 0) s = 1;
                                  break;
                                  /* if part of statement 2 */
                                  /***** comment 1510 ******/
                          case 2: if(strcmp(de, "YES") == 0) s = 1;
                                  break;
                                  /* if part of statement 3 */
                          case 3: if((strcmp(de, "YES") == 0) &&
                                     (strcmp(di, "YES") == 0)) s =1;
                                  break;
                                  /* if part of statement 4 */
                                  /******** comment 1560 ******/
                          case 4: if((strcmp(qu, "YES") == 0) &&
                                     (gr<3.5) && (ex >= 2)) s = 1;
                                  break;
                                  /******** comment 1570 ********/
                                  /* if part of statement 5 */
                          case 5: if((strcmp(qu, "YES") == 0) &&
                                     (gr<3) && (ex<2)) s = 1;
                                  break;
                                  /* if part of statement 6 */
                          case 6: if((strcmp(qu, "YES") == 0) &&
                                     (gr >=3.5)) s = 1;

                                  break;
                                  /********* comment 1680 ******/
                          }
                          /* see if the then part should be invoked */
                          if( s != 1) {
                                  /* failed..search rest of statements for
                                     same conclusion */
                                  /* get conclusion */
                                  i = statsk[sp];
                                  strcpy(varble, conclt[i]);
                                  /* search for conclusion starting at the
                                     next statement number */
                                  f = statsk[sp] + 1;
                                  determine_member_concl_list();
                                  sp = sp+1;
                          }
                          /* pop old conclusion and put on new one */
                  } while((s != 1) && (sn !=0));  /* outer do-while loop */
                  if(sn != 0){
                          /* if part true invoke then part */
                          /* then part of if-then statements from the
                             position knowledge base */
                          switch (sn) {
                                  /* then part of statement 1 */
                                  /******* comment 1500 *******/
                          case 1: strcpy(po, "NO");
                                  printf("PO=NO\n");
                                  break;
                                  /* then part of statement 2 */
                                  /****** comment 1510 ******/
                          case 2: strcpy(qu, "YES");
                                  printf("QU=YES\n");
                                  break;
                                  /* then part of statement 3 */
                          case 3: strcpy(po, "YES");
                                  printf("PO=RESEARCH\n");
                                  break;
                                  /* then part of statement 4 */
                                  /******** comment 1560 ******/
                          case 4: strcpy(po, "YES");
                                  printf("PO=SERVICE ENGINEER\n");
                                  break;
                                  /* then part of statement 5 */
                                  /****** comment 1570 *****/
                          case 5: strcpy(po, "NO");
                                  printf("PO=NO");
                                  break;
                                  /* then part of statement 6 */
                          case 6: strcpy(po, "YES");
                                  printf("PO=PRODUCT ENGINEER\n");
                                  break;
                                  /****** comment 1680 ********/
                          }
                          /* pop the stack */
                          sp=sp+1;
                          if(sp >= 11)
                                  /* finished */
                                  printf("*** SUCCESS\n");
                          else {
                                  /* stack is not empty */
                                  /* get next clause then continue */
                                  clausk[sp] = clausk[sp]+1;
                                  goto b545;
                          }
                  }
        }
}

void determine_member_concl_list() {
/* routine to determine if a variable (varble) is a member of the
   conclusion list (conclt).  if yes return sn != 0.
   if not a member sn=0;
*/
        /* initially set to not a member */
        sn = 0;
        /* member of conclusion list to be searched is f */
        i = f;
        while((strcmp(varble, conclt[i]) != 0) && (i<8))
                /* test for membership */
                i=i+1;
        if (strcmp(varble, conclt[i]) == 0) sn = i;  /* a member */
}

void push_on_stack()
/* routine to push statement number (sn) and a clause number of 1 onto the
conclusion stack which consists of the statement stack (statsk) and the
clause stack (clausk)..to push decrement stack pointer (sp) */
{
        sp=sp-1;
        statsk[sp] = sn;
        clausk[sp] = 1;
}

void instantiate()
/* routine to instantiate a variable (varble) if it isn't already.  the
instantiate indication (instlt) is a 0 if not, a 1 if it is.  the
variable list (varlt) contains the variable (varble). */
{
        i=1;
        /* find variable in the list */
        while((strcmp(varble, varlt[i]) != 0) && (i<10)) i=i+1;
        if((strcmp(varble, varlt[i]) == 0) && (instlt[i] != 1))
                /*found variable and not already instantiated */
        {
                instlt[i]=1; /*mark instantiated */
                /* the designer of the
               knowledge base places the input statements to
               instantiate the variables below in the case statement */
                switch (i)
                {
                        /***** input statement *****/
                        /* input statements for sample position knowledge
                           base */
                        /***** comment 1700 ******/
                case 1: printf("INPUT YES OR NOW FOR DE-? ");
                        gets(de);
                        break;
                case 2: printf("INPUT YES OR NO FOR DI-? ");
                        gets(di);
                        break;
                case 3: printf("INPUT A REAL NUMBER FOR EX-? ");
                        scanf("%f", &ex);
                        break;
                case 4: printf("INPUT A REAL NUMBER FOR GR-? ");
                        scanf("%f", &gr);
                        break;
                        /***** comment 1715 ****/
                }
                /* end of inputs statements for sample position knowledge
                   base */
        }
}




		/* sample IF-THEN statements from the position knowledge base */
		switch (sn)
		{
			/* statement 1 */
			/***** comment 1500 *****/
		case 1: if (strcmp(interest, "FALL") == 0) s = 1;
			break;
			/* statement 2 */
			/***** comment 1510 *****/
		case 2: if (strcmp(interest, "RISE") == 0) s = 1;
			break;
			/* statement 3 */
			/***** comment 1540 *****/
		case 3: if (strcmp(dollar, "FALL") == 0) s = 1;
			break;
			/* statement 4 */
			/***** comment 1550 *****/
		case 4: if (strcmp(dollar, "RISE") == 0) s = 1;
			break;
			/* statement 5 */
		case 5: if ((strcmp(fedint, "FALL") == 0) && (strcmp(fedmon, "ADD")) == 0) s = 1;
			break;
			/* statement 6 */
		case 6: if ((strcmp(qu, "YES") == 0) && (gr >= 3.5) == 0) s = 1;
			break;
			/***** comment 1610 *****/
		}
		/* see if the THEN part should be invoked, i.e., s=1 */
		if (s != 1)
		{
			f = sn + 1;
			goto b496;
		}
		/* invoke THEN part */
		switch (sn)
		{
			/*********** comment 1500 ***********/
			/* put variable on the conclusion variable queue */
		case 1:
			strcpy(stock, "RISE");
			printf("ST=RISE\n");
			strcpy(v, "ST");
			instantiate();
			break;
			/*********** comment 1510 ***********/
			/*put variable on the conclusion variable queue */
		case 2:
			strcpy(stock, "FALL");
			printf("ST=FALL\n");
			strcpy(v, "ST"); instantiate();
			break;
			/*********** comment 1540 ***********/
			/* put variable on the conclusion variable queue */
		case 3:
			strcpy(interest, "RISE");
			printf("IN=RISE\n");
			strcpy(v, "IN");
			instantiate();
			break;
			/*********** comment 1550 * **********/
			/* put variable on the conclusion variable queue */
		case 4:
			strcpy(interest, "FALL");
			printf("IN=FALL\n");
			strcpy(v, "IN");
			instantiate();
			break;
			/* put variable on the conclusion variable queue */
		case 5:
			strcpy(interest, "FALL");
			printf("IN=FALL\n");
			strcpy(v, "IN");
			instantiate();
			break;
		case 6:
			strcpy(po, "YES");
			printf("PO=YES\n");
			break;
			/*********** comment 1610 ***********/
		}
		f = sn + 1;
		goto b496;
	}
	/* no more clauses in the clause variable list (clvarlt) containing the variable in front of the queue (cndvar(fp)) then remove front variable (cndvar(fp)) and replace it by the next variable (cndvar(fp+1)). If no more variables are at the front of the queue, stop. */
	/* next queue variable */
	fp = fp + 1; if (fp < bp)
	{
		/* check out the condition variable */
		f = 1; goto b496;
	} /* no more conclusion variables on queue */
}

/* Routine to instantiate a variable (v) if it isn't already. The instantiate indication (instlt) is a 0 if not, a 1 if it is. The variable list (varlt) contains the variable (v) */
void check_instantiation()
{
	i = 1;
	/* find variable in the variable list */
	while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i = i + 1;
	/* check if already instantiated */
	if (instlt[i] != 1)
	{
		/* mark instantiated */
		instlt[i] = 1;
		/* the designer of this knowledge base places the input 					statements to instantiate the variables in this case statement */
		switch (i)
		{
			/* input statements for sample position knowledge base */
		case 1:
			printf("RISE OR FALL FOR DO? ");
			gets(dollar);
			break;
		case 2:
			printf("RISE OR FALL FOR FT? ");
			gets(fedint); break;
		case 3:
			printf("ADD OR SUBTRACT FOR FM? ");
			gets(fedmon); break;
		case 4:
			printf("RISE OR FALL FOR IN? ");
			gets(interest); break;
		case 5:
			printf("RISE OR FALL FOR ST? ");
			gets(stock);
			break;
		}
	}
	/* end of input statements for the position knowledge base */
}

//====================================================================//* Search clause variable list for a variable (clvarlt) equal to the one in front of the conclusion queue (cndvar). Return the statement number (sn). If there is no match, i.e., sn=0, the first statement for the space is f. */
void search()
{
	int flag = 0;
	sn = f;
	while ((flag == 0) && (sn <= 10))
	{
		cn = 1;
		k = (sn - 1) * 4 + cn;
		while ((strcmp(clvarlt[k], cndvar[fp]) != 0) && (cn < 4))
		{
			cn = cn + 1;
			k = (sn - 1) * 4 + cn;
		}
		if (strcmp(clvarlt[k], cndvar[fp]) == 0) flag = 1;
		if (flag == 0) sn = sn + 1;
	} if (flag == 0) sn = 0;
}

//=================================================================== /* Routine to instantiate a variable (v) and then place it on the back of the queu (cndvar[bp]), if it is not already there. */
void instantiate()
{
	i = 1;
	/* find variable in the variable list (varlt) */
	while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i = i + 1;
	/* instantiate it */
	instlt[i] = 1;
	i = 1;
	/* determine if (v) is or already has been on the queue (cndvar) */
	while ((strcmp(v, cndvar[i]) != 0) && (i <= 10)) i = i + 1;
	/* variable has not been on the queue. Store it in the back of the queue */
	if (strcmp(v, cndvar[i]) != 0)
	{
		strcpy(cndvar[bp], v);
		bp = bp + 1;
	}
}


