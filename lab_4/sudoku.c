/*--------------------------------*/
/*Alex Hill                       */
/*CS241-005                       */
/*February 24th, 2018             */
/*--------------------------------*/
#define TRUE 1
#define FALSE 0
#include <stdio.h>
int search(int grid[9][9], int index, int num); /* had to write this or else it threw a warning for some reason*/
/*Reads in one line at a time */
int readLine(int grid[9][9])
{
  int i, r, c, num;
  int error = FALSE;

  for (i = 0; (num = getchar()) != '\n'; i++)
    {
      if (num == EOF) return EOF; /*A sneaky way to return if its EOF since im only checking for '\n' */
      putchar(num); /*used to print out the original sequence */
      if ((num < '1' || num > '9') && (num != '.')) error = TRUE;
      if (num == '.') num = '0';
      /*'.' are given value 0 b/c they havn't been assigned a value yet*/

      r = (i / 9) % 9;
      c = i % 9;
      grid[r][c] = num - '0';  /*- '0' is a bandaid fix so it thinks its an char-int*/
    }                          /*working with ints is much easier in my opinion though*/
  putchar('\n');
  if (i != 81) error = TRUE; /*sudoku can only have 81 digits*/
  return error;
}

/*Checks if there are duplicates in the row*/
int rowCheck(int grid[9][9])
{
  int r, c, i;
  for (r = 0; r < 9; r++)
    {
      for (c = 0; c < 9; c++)
	{
	  for (i = c + 1; i < 9; i++)
	    {
        if ((grid[r][c] != 0) && (grid[r][c] == grid[r][i]))
	  {
	    return TRUE;
	  }
	    }
	}
    }
  return FALSE;
}

/*Checks if there are duplicates in the column*/
int columnCheck(int grid[9][9])
{
  int r, c, i;
  
  for (c = 0; c < 9; c++)
    {
      for (r = 0; r < 9; r++)
	{
	  for (i = r + 1; i < 9; i++)
	    { /* the logic here is that it loops through every variation
	     and checks that it is not 0 and that it is not equal to any similar
	     value in that column/row*/
	      if ((grid[r][c] != 0) && (grid[r][c] == grid[i][c]))
		{
		  return TRUE;
		}
	    }
	}
    }
  return FALSE;
}

/*Checks if there are duplicates in the box*/
int boxCheck(int grid[9][9])
{
  /*First two for loops are to find a box
    next two for loops are to search inside the box*/
  int r, c, i, j;
  
  for (r = 0; r < 9; r += 3)
    {
      for (c = 0; c < 9; c += 3)
    {
      for (i = 0; i < 9; i++)
	{
	  for (j = i + 1; j < 9; j++)
	    {
	      /*example of this in action grid[3 + 0 / 3][3+ 0 % 3] != 0
		so basically its grid[1][0] != 0 && grid[1][0] == grid[1][1]
		which means its checking for every variation after that so if
		its not zero and its not equal to anyother number then there are no
		duplicates in that box. else it returns that there is a duplicate.*/
	      if ((grid[r + i / 3][c + i % 3] != 0) &&
              (grid[r + i / 3][c + i % 3] ==
               grid[r + j / 3][c + j % 3]))
		{
		  return TRUE;
		}
	    }
	}
    }
    }
  return FALSE;
}

/*If solve doesn't have any 0's, it's validated*/
int validate (int grid[9][9])
{
  int r, c;
  
  for (r = 0; r < 9; r++)
    {
      for (c = 0; c < 9; c++)
	{
	  if (!grid[r][c]) /*Logic behind this is if it is a 0 then it will return true
			     because a zero in C is false*/
	    {
	      printf("No solution\n\n");
	      return TRUE;
	    }
	}
    }
  return FALSE;
}

/*Writes sudoku puzzle from the puzz array.
  It also uses DEBUG to write in standard form or it writes it out in the form required*/
void prettyPrint(int grid[9][9])
{
  int r, c;
  printf("solution:");
  for (r = 0; r < 9; r++)
    {
      printf("\n");
      if (r == 3 || r == 6)
	{
	  printf("------+-------+------\n");
	}
      for (c = 0; c < 9; c++)
	{
	  if(c > 0)  printf(" ");
	  if (grid[r][c]) printf("%d", grid[r][c]);
	  /*the if statement was mainly for debugging
	    basically if its a zero it prints"."*/
	  else printf(".");
	  if (c == 2 || c == 5) printf(" |");
	}
    }
  printf("\n");
}

/*recursive method*/
int findSolution(int grid[9][9], int index)
{
  int num;
  int r = index / 9; /*Row is / because you don't need an exact number */
  int c = index % 9; /*Column is % because you need the exact number */
                     /*This is pretty much a bandaid fix so you don't need for loops in a 
		       recursive method*/
  
  if (index == 81) return TRUE; /*Only 81 digits work*/
  if (grid[r][c] != 0)
    { /* if grid is not 0 then it recurses with +1 to its index*/
      return findSolution(grid, ++index); /*Needs ++ before index or else its a segmentation dump */
    } /* if it is 0 then it tries to findSolution */
  else
    {
      for (num = 1; num <= 9; num++)
	{
	  if (search(grid, index, num))
	    {
	      grid[r][c] = num;
	      if (findSolution(grid, index)) return TRUE; 
	      grid[r][c] = 0; /* if not solution, sets it to 0 to try again later*/
	    }
	}
      return FALSE;
    }
}


int search(int puzz[9][9], int index, int num)
{
  int i, j;
  int r = index / 9;
  int c = index % 9;
  int begR = r - (r % 3); /*to find beginning numbers*/
  int begC = c - (c % 3);
  /*Checks if a spot works or not*/
  for (i = 0; i < 9; i++)
    {
      if (puzz[r][i] == num)
	{
	  return FALSE;
	}
    }
  
  for (i = 0; i < 9; i++)
    {
      if (puzz[i][c] == num)
	{
	  return FALSE;
	}
    }
  
  for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 3; j++)
	{
	  if (puzz[begR + i][begC + j] == num)
	    {
	      return FALSE;
	    }
	}
    }
  return TRUE;
}
int main (void)
{
  int grid[9][9];
  int error;
  int index = 0; /*Sees how many numbers in a problem */
  
  while ((error = readLine(grid)) != EOF) /*To read in one line at a time*/
    {
      error += rowCheck(grid); 
      error += columnCheck(grid); /*Error checking first so its more efficient */
      error += boxCheck(grid);
      
      if (error) printf("Error\n\n");
      else
	{
	  findSolution(grid, index);
	  if (!validate(grid)) prettyPrint(grid);
	}
    }
  return 0;
}
