/*
* FIXED-POINT ALGORITHM 2.2
*
* To find a solution to p = g(p) given an
* initial approximation p0
*
* INPUT:  initial approximation; tolerance TOL;
*         maximum number of iterations NO.
*
* OUTPUT: approximate solution p or 
*         a message that the method fails.
*/

#include<stdio.h>
#include<math.h> 
#define true 1
#define false 0

main()
{
   double TOL,P0,P;
   int I,NO,FLAG,OK;
   char AA;
   FILE *OUP[1];

   void INPUT(int *, double *, double *, int *);
   void OUTPUT(FILE **, int *);
   double absval(double);
   double G(double ); 

   INPUT(&OK, &P0, &TOL, &NO);
   if (OK) {
      OUTPUT(OUP, &FLAG);
      /* STEP 1 */ 
      I = 1; OK = true; 
      /* STEP 2 */ 
      while((I<=NO) && OK) {
         /* STEP 3 */ 
         /* compute P(I) */  
         P = G(P0);
         if (FLAG == 2) fprintf(*OUP, "%3d   %15.8e\n", I, P);
         /* STEP 4 */ 
         if (absval(P-P0) < TOL) { 
            /* procedure completed successfully */
            fprintf(*OUP, "\nApproximate solution P = %12.8f\n", P);
            fprintf(*OUP, "Number of iterations = %3d", I);
            fprintf(*OUP, "    Tolerance = %14.8e\n",TOL);
            OK = false;
         }
         else {
            /* STEP 5 */ 
            I++;
            /* STEP 6 */ 
            /* update P0 */ 
            P0 = P; 
         }
      }
      if (OK) {
         /* STEP 7 */  
         /* procedure completed unsuccessfully */ 
         fprintf(*OUP, "\nIteration number %3d", NO);
         fprintf(*OUP, " gave approximation %12.8f\n", P);
         fprintf(*OUP, "not within tolerance %14.8e\n",TOL);
      }
      fclose(*OUP);
   }
}
/* Change function G for a new problem */
double G(double X)
{
   double g; 

   g = sqrt(10.0 / (4.0 + X)); 
   return g;
}

void INPUT(int *OK, double *P0, double *TOL, int *NO)
{
   char AA;

   printf("This is the Fixed-Point Method.\n");
   printf("Has the function G been created in the program immediately preceding\n");
   printf("the INPUT function?\n");
   printf("Enter Y or N\n");
   scanf("%c",&AA);
   if ((AA == 'Y') || (AA == 'y')) {
      *OK = false;
      printf("Input initial approximation\n");
      scanf("%lf",P0); 
      while(!(*OK)) {
         printf("Input tolerance\n");
         scanf("%lf", TOL);
         if (*TOL <= 0.0) printf("Tolerance must be positive\n");
         else *OK = true;
      }
      *OK = false;
      while (!(*OK)) {
         printf("Input maximum number of iterations - no decimal point\n");
         scanf("%d", NO);
         if (*NO <= 0) printf("Must be positive integer\n");
         else *OK = true;
      }
   }
   else {
      printf("The program will end so that the function G can be created\n");
      *OK = false;
   }
}

void OUTPUT(FILE **OUP, int *FLAG)
{
   char NAME[30];

   printf("Select output destination\n");
   printf("1. Screen\n");
   printf("2. Text file\n");
   printf("Enter 1 or 2\n");
   scanf("%d", FLAG);
   if (*FLAG == 2) {
      printf("Input the file name in the form - drive:name.ext\n");
      printf("For example:   A:OUTPUT.DTA\n");
      scanf("%s", NAME);
      *OUP = fopen(NAME, "w");
   }
   else *OUP = stdout;
   printf("Select amount of output\n");
   printf("1. Answer only\n");
   printf("2. All intermeditate approximations\n");
   printf("Enter 1 or 2\n");
   scanf("%d", FLAG);
   fprintf(*OUP, "FIXED-POINT METHOD\n"); 
   if (*FLAG == 2) fprintf(*OUP, "  I                 P\n");
}   

/* Absolute Value Function */
double absval(double val)
{
   if (val >= 0) return val;
   else return -val;
} 
