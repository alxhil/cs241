/*************************************************/
/* Alex Hill                                     */
/* Feb-1-2018                                    */
/* CS-241 Section #5                             */
/*************************************************/
#include <stdio.h>
#define IN 1
#define OUT 0
int main()
{
  int c, nl,nc, nw,firstInLine,charInLine,shortLineW,shortLineC,charTest,wordTest,
  wordsInLine, state;
  state = OUT;
  wordTest = charTest  = 100;
  nc = nw = nl = firstInLine = charInLine = wordsInLine = 0;
  while((c = getchar()) != EOF)
    {
      if(firstInLine == 0)
	    {
	      if(nl < 9)
	        {
	          printf(" ");
	        }
	      ++nl;
	      printf("%d. ",nl);
	      firstInLine++;
	    }
      if(c != EOF && c != '\n')
	    {
	      printf("%c",c);
	    }
      ++charInLine;
      if(c == '\n')
	    {
	      if(wordsInLine < wordTest)
	        {
	          wordTest = wordsInLine;
	          shortLineW = nl;
	      
	        }
	      if(charInLine < charTest)
	        {
	          charTest = charInLine;
	          shortLineC = nl;
	        }
	  
	      nc = nc + charInLine;
	      firstInLine--;
	      printf(" [%d,%d]\n",wordsInLine,charInLine-1);
	      charInLine = 0;
	      wordsInLine = 0;
	    }
      if(c == ' ' || c == '\n' || c == '\t')
	    {
	      state = OUT;
	    }   
      else if (state == OUT)
	    {
	      state = IN;
	      ++nw;
	      ++wordsInLine;
	    }
      
    }
  printf("%d lines, %d words, %d characters\n",nl,nw,nc-nl);
  printf("Line %d has the fewest words with %d\n",shortLineW,wordTest);
  printf("Line %d has the fewest characters with %d\n",shortLineC,charTest-1);
  return 0;
}
