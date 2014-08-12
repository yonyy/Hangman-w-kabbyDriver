#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define DASH '_'

typedef struct Letter 
{
	int gameOver;  /* If the whole word has been guessed */
  int numRight;   /* Number of letters correctly guessed */
	char randomWord[80];

}Letter;

int selectWord(char letters []);
int compareChar(char input, char * originalWord, char guesses []);
int gameOver(int numRight, int wordLength, char letters []);
void printWelcomeMessages(int wordLength);
void printChar(char guesses [], int length);
void newGame(Letter newGame, char letters []);

int main(int argc, char * argv[]) 
{

  Letter letter = {FALSE, 0};
  char guesses[80];
  int wordLength;
  int dashes;
  int numGuesses;
  int maxTries;
  
  while(letter.gameOver != TRUE)
  {
    char * word;
    char * ptr;
   	wordLength = 0;
    dashes = 0;
    numGuesses = 0;
    maxTries = 15;
	  wordLength = selectWord(letter.randomWord);        /* Selecting random word */
	  word = letter.randomWord;                          /* Assigning word  to the randomWord */
    ptr = strchr(word,'\n');                           /* Getting rid of the new line */ 
    *ptr = '\0';

    for (dashes = 0; dashes < wordLength; dashes ++)  /* For loop to print out the dashes */
    {
      guesses[dashes] = DASH;
    }
    
    printWelcomeMessages( wordLength );
	
    char input;
	
    while(letter.gameOver != TRUE)
	  {
      printf("Number of guesses: %i\n",numGuesses);
      printf("Number of tries left: %i\n",(maxTries - numGuesses));
		  printf( "Guess a letter: ");
		  input = getchar();
      numGuesses++;

      if (input == '\n' || input == ' ')
      {
        input = getchar();
      }
      if (compareChar(input,word,guesses))
      {
        printf("\n\nYou guessed '%c' correctly\n\n",input);
      }
      else
      {
        printf("\n\nSorry, '%c' is not a letter in the word\n\n",input);
      }

      printChar(guesses,wordLength);
      if (!gameOver(letter.numRight,wordLength,guesses))
      {
        printf("Congratulations! You have correctly guessed '%s'!\n\n",guesses);
        break;
      }
      if (numGuesses == maxTries)
      {
        printf("GAME OVER!\nYou have failed to guess '%s'\n\n",word);
        break;
      }
      
	  }

    newGame(letter,guesses);
  }
	return 0;
}

void newGame(Letter newGame, char letters [])
{

  memset(&newGame,0,sizeof(Letter));
  memset(letters,' ',80);
  newGame.numRight = 0;
  newGame.gameOver = FALSE;
  printf("Starting a new game...\n");
}
int gameOver(int numRight, int wordLength, char letters [])
{
  int index;
  numRight = 0;
  for (index = 0; index < wordLength; index++)
  {
    if (letters[index] != DASH)
      numRight++;
  }
  
  return (wordLength - numRight);
}
void printChar(char guesses [], int length)
{
  int i = 0;
  for ( i = 0; i < length; printf("%c ",guesses[i]), i++);
  puts("\n");
}
int compareChar(char input, char * originalWord, char guesses [])
{
  char * tempPtr = originalWord;
  int index = 0;
  int guess = FALSE;
  while (*tempPtr != '\n')
  {
    if (input == *tempPtr)
    {
      guess = TRUE;
      guesses[index] = *tempPtr;
    }
    tempPtr++;
    index++;
  }
  return guess;
}

void printWelcomeMessages(int wordLength)
{
  int dashes;
	printf("WELCOME TO HANGMAN\n");
	printf("\nSelecting a random word.");
	printf("\nYour word is %d characters long...Good Luck!", wordLength);
	puts("\n");

  for (dashes = 0; dashes < wordLength; dashes++)
  {
    printf("_ ");
  }
  puts("\n");
}

int selectWord( char letters[])
{
	FILE * fp = fopen("./words", "r" );
  char c;
  int index = 0;
	int lineCount = 235886; //number of words in local dictionary
	srand(time(NULL));
	int randomLine = rand() % lineCount; //random line
	while( index < randomLine )
	{
		index++;
		(void)fgets( letters, 80, fp );
	}
  index = 0;
  do {
    c = fgetc(fp);
    letters[index] = c;
    index++;
    } while (c != '\n');
	
  fclose(fp);
  return (index - 1);
}
