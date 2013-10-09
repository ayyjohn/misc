/*
 * Name of the Program: Sudoku Solver
 * 
 * Name of creator: Rohan Rangray
 * 
 * Last edited: 9 October 2013
 * 
 * This program lets the user input a grid of 
 * 9x9 integers seperated by whitespace.
 * The grid is interpreted as being read row-wise.
 * The program then uses a bruteforce algorithm to complete the 
 * sudoku puzzle, if a solution exists.
 * If a solution doesn't exist, the program outputs "ERROR" and terminates.
 * 
 * Header files: <iostream> and <stdio> are used for input-output purposes.
 * 		  <cstdio> is used for calling the function exit()
 * 
 */

#define GRID_SIZE 9
#include<iostream>
#include<stdio.h>
#include<cstdlib>
using namespace std;

/* 
 * origrid represents the original grid entered by the user.
 * solgrid represents the solution grid obtained by solving the puzzle.
 * Throughout this program, changes will be made only to solgrid
 * 
 */
int origrid[9][9], solgrid[9][9];


/*
 * Name of function: getGrid()
 * 
 * Purpose: Allow the user to input a square grid of size GRID_SIZE
 * 
 * Paramters: None
 * 
 * Return: none
 * 
 */
void getGrid ()
{
   int input;
   printf ("Enter a Sudoku grid row by row.\nEnter 0 for empty places.\n");
   for (int i = 0; i < GRID_SIZE; i++)
   {
      for (int j = 0; j < GRID_SIZE; j++)
      {
         cin >> input;
         if (input >= 0 && input <= GRID_SIZE) // check if input is valid
         {
            solgrid[i][j] = origrid[i][j] = input;
         }
         else
         {
            printf ("INVALID INPUT.\nENTER AGAIN\n");
            getGrid();
         }
      }
   }
}

/*
 * Name of function: checkCell()
 * 
 * Purpose: Check if a given cell in the grid has the same value as
 * another cell in the same row, column, or sub-square.
 * 
 * Paramters: int type variables x and y.
 * x represents the row number (starting from 0) of the cell to be
 * checked and y represents the column number (starting from 0) of the
 * cell to be checked.
 * 
 * Return: The function returns a bool type value. If the cell (x,y)
 * conflicts with another cell in the same row,column, or sub-square,
 * it returns false, otherwise it returns true.
 * 
 */
bool checkCell (int x, int y)
{
   // If there's a different cell in the same column with the same
   // value as that of (x,y), return false
   for (int i = 0; i < GRID_SIZE; i++)
   {
	  if (solgrid[i][y] == solgrid[x][y] && i != x)
      {
         return false;
      }
   }
   // If there's a different cell in the same row with the same
   // value as that of (x,y), return false
   for (int j = 0; j < 9; j++)
   {
      if (solgrid[x][j] == solgrid[x][y] && j != y)
      {
         return false;
      }
   }
   // If there's a different cell in the same sub-square with the same
   // value as that of (x,y), return false
   for (int i = (x / 3) * 3; i < (x / 3 + 1) * 3; i++)
   {
      for (int j = (y / 3) * 3; j < (y / 3 + 1) * 3; j++)
      {
         if (solgrid[i][j] == solgrid[x][y] && x != i && j != y)
         {
            return false;
         }
      }
   }
   // If none of the above apply, return true
   return true;
}

/*
 * Name of the function: printGrid()
 * 
 * Purpose: Print the solved grid (solgrid), after the program
 * finishes finding a solution.
 * 
 * Parameters: none
 * 
 * Return: none
 * 
 */

void printGrid ()
{
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         printf ("%d ", solgrid[i][j]);
      }
      printf ("\n");
   }
}

/*
 * Name of the function: main()
 * 
 * Purpose: Contains the main body of the program and the implementation
 * of the algorithm to find a solution.
 * 
 * Parameters: none
 * 
 * Return: Returns an int type value (0) after it terminates.
 * 
 */

int main ()
{
   getGrid (); // make the user input a grid
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {

         if (origrid[i][j] == 0) // if the original input was empty
         {
            while (true)
            {
			   // increment the value of cell (i,j)
               solgrid[i][j]++;
               // If value of cell (i,j) exceeds 9, set it to zero
               // to signal the later part of the program
               // to change the value of the previous originally empty
               // cell.
               if (solgrid[i][j] > 9)
               {
                  solgrid[i][j] = 0;
                  break;
               }
               if (checkCell (i, j))
               {
                  break;
               }
            }
            // If value of cell (i,j) is 0, go back to the last cell
            // that was originally empty
            if (solgrid[i][j] == 0)
            {
               int a;
               for (a = j - 1; origrid[i][a] != 0; a--)
               {
                  if (a < 0)
                  {
                     a = GRID_SIZE -1;
                     i--;
                  }
                  if (i < 0)
                  {
                     printf ("ERROR\n"); // i<0 implies no solution
                     exit (0);
                  }
               }
               // set j = a -1, so j becomes equal to a after
               // the incrememnt at the end of iteration
               j = a - 1;
               if (j < -1)
               {
                  j = GRID_SIZE -2;
                  i--;
               }
            }
         }
      }
   }
   // print the solved grid
   printGrid ();
   return 0;
}
