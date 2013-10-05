#include<iostream>
#include<stdio.h>
#include<cstdlib>
using namespace std;

int origrid[9][9], solgrid[9][9];
void getGrid()
{
   int input;
   printf("Enter a Sudoku grid row by row.\nEnter 0 for empty places.\n");
   for( int i = 0; i < 9; i++ )
   {
      for( int j = 0; j < 9; j++ )
      {
	 cin>>input;
	 if( input >= 0 && input <= 9 )
	 {
	    solgrid[i][j] = origrid[i][j] = input;
	 }
	 else
	 {
	    printf("INVALID INPUT.\nABORTING\n");
	    exit(0);
	 }
      }
   }
}

bool checkCell( int x, int y)
{
  bool check = true;
  for( int i = 0; i < 9; i++ )
  {
    if( solgrid[i][y] == solgrid[x][y] && i != x )
    {
      return false;
    }
  }
 for( int j = 0; j < 9; j++ )
  {
     if( solgrid[x][j] == solgrid[x][y] && j != y )
     {
	return false;
     }
  }
  for( int i = (x / 3) * 3; i < (x / 3 + 1) * 3; i++ )
  {
     for( int j = (y / 3) * 3; j < (y / 3 + 1) * 3; j++)
     {
	if( solgrid[i][j] == solgrid[x][y] && x != i && j != y )
	{
	   return false;
	}
     }
  }
  return true;
}

void printGrid()
{
   for( int i = 0; i < 9; i++ )
   {
      for( int j = 0; j < 9; j++ )
      {
	 printf("%d   ",solgrid[i][j]);
      }
      printf("\n\n");
   }
}

int main()
{
   getGrid();
   for( int i = 0; i < 9; i++ )
   {
      for( int j = 0; j < 9; j++ )
      {
         if( origrid[i][j] == 0 )
	      {
	         while(true)
	         {
               solgrid[i][j]++;
	            if( solgrid[i][j] > 9 )
               {
                  solgrid[i][j] = 0;
                  break;
               }
	            if( checkCell(i,j) )
	            {
		            break;
	            }
	         }
	         if( solgrid[i][j] == 0  )
	         {
               int a;
	            for( a = j-1; origrid[i][a] != 0; a--)
               {
                  if( a < 0 )
                  {
                     a = 8;
                     i--;
                  }
                  if( i < 0 )
                  {
                     printf("ERROR\n");
                     exit(0);
                  }
               }
               j = a-1;
               if( j < -1 )
		         {
		            j = 7;
	               i--;
	            }
	         }
	      }
      }
   }
   printGrid();
   return 0;
}
