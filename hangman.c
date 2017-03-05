/****************************************************************************
* COSC2138/CPT 220 - Programming Principles 2A
* Study Period 2  2015 Assignment #1 - hangman program
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Course Code      : EDIT HERE
* Start up code provided by the CTeach Team
****************************************************************************/


#include "hangman.h"

/****************************************************************************
* Function main() is the entry point for the program.
****************************************************************************/
int main(void)
{
   char word[MAX_WORD_LEN + 1];
   unsigned wrongGuesses = 0;
   int guessedLetters[ALPHABET_SIZE] = {
      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
   };
   init(word);
   do{
      displayWord(word,guessedLetters);
      if(guessLetter(word,guessedLetters)== BAD_GUESS)
      {
         wrongGuesses++;
      }
      displayHangman(wrongGuesses);
   }while(isGameOver(word,guessedLetters,wrongGuesses) == GAME_CONTINUE);
   getchar();
   return EXIT_SUCCESS;
}


/****************************************************************************
* Function init() choses a word for the hangman game from the words[] array.
****************************************************************************/
void init(char* word)
{
   const char* words[NUM_WORDS] = {
      "array",      "auto",       "break",      "case",       "cast",
      "character",  "comment",    "compiler",   "constant",   "continue",
      "default",    "double",     "dynamic",    "else",       "enum",
      "expression", "extern",     "file",       "float",      "function",
      "goto",       "heap",       "identifier", "library",    "linker",
      "long",       "macro",      "operand",    "operator",   "pointer",
      "prototype",  "recursion",  "register",   "return",     "short",
      "signed",     "sizeof",     "stack",      "statement",  "static",
      "string",     "struct",     "switch",     "typedef",    "union",
      "unsigned",   "variable",   "void",       "volatile",   "while"
   };
   const char* chosenWord;
   int i = 0;
   srand(time(NULL));
   chosenWord = words[rand()%50];
   while(i<strlen(chosenWord))
   {
      word[i] = chosenWord[i];
      i++;
   }
   word[i] = '\0';
}
/****************************************************************************
* Function displayWord() prints the word to screen with all letters that 
* have not been correctly guessed blanked out with an underscore. 
* Output example:
* +-+-+-+-+-+-+-+-+-+-+
* |i|d|e|n|_|i|_|i|e|r|
* +-+-+-+-+-+-+-+-+-+-+
****************************************************************************/
void displayWord(char* word, int* guessedLetters)
{
     char alphabet[ALPHABET_SIZE] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 
     int i = 0;
     while(i<strlen(word))
     {
         int j = 0;
         while(j<ALPHABET_SIZE)
         {
            if(alphabet[j] == word[i])
            {
               if(guessedLetters[j] == 1)
               {
                  printf("%c%s", word[i]," ");
               }
               else
               {
                  printf("_ "); 
               }
            }
            j++;
         }
         i++;
     }
}


/****************************************************************************
* Function guessLetter() prompts the user to enter one letter. The function
* maintains an array of guessed letters. The function returns GOOD_GUESS
* or BAD_GUESS depending on whether or not the letter is in the word.
****************************************************************************/
int guessLetter(char* word, int* guessedLetters)
{
    char alphabet[ALPHABET_SIZE] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; 
    char guess;
    int duplicateGuess;
    int i = 0;
    do{
       duplicateGuess = 0;
       do{
          printf("\n%s","Please enter a letter you think is in the above word:");
          guess = fgetc(stdin);
          readRestOfLine();
       }while(!isalpha(guess));
       i = 0;
       while(i<ALPHABET_SIZE)
       {
          if(tolower(guess) == alphabet[i])
          {
             if(guessedLetters[i] == 1)
             {
                 duplicateGuess = 1;
             }
          }
          i++;
       }
    }while(duplicateGuess == 1);
    i = 0;
    while(i<strlen(word))
    {
       if(tolower(guess) == tolower(word[i]))
       {
          int j = 0;
          while(j<ALPHABET_SIZE)
          {
             if(alphabet[j]==tolower(guess))
             {
                guessedLetters[j] = 1;
                return GOOD_GUESS;
             }
             j++;
          }         
       }
       i++;
    }
    return BAD_GUESS;
    
}


/****************************************************************************
* Function displayHangman() displays an ascii art drawing to complement the
* game. The drawing varies depending on the number of wrong guesses.
* When there are no wrong guesses, an empty drawing is displayed:
* **********
* *        *
* *        *
* *        *
* *        *
* *        *
* *        *
* **********
* When there are 10 wrong guesses (and the game is over), the complete
* drawing is displayed:
* **********
* * +--+   *
* * |  |   *
* * |  O   *
* * | -+-  *
* * | / \  *
* * +----- *
* **********
* You need to display an appropriate drawing depending on the number of 
* wrong guesses:
* - 0 wrong: empty drawing.
* - 1 wrong: include floor.
* - 2 wrong: include vertical beam.
* - 3 wrong: include horizontal beam.
* - 4 wrong: include noose.
* - 5 wrong: include head.
* - 6 wrong: include body.
* - 7 wrong: include left arm.
* - 8 wrong: include right arm.
* - 9 wrong: include left leg.
* - 10 wrong: include right leg (complete drawing).
****************************************************************************/
void displayHangman(unsigned wrongGuesses)
{
     switch(wrongGuesses)
     {
        case 0 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","*        *","*        *","*        *","*        *","*        *","*        *","**********");
           break;
        case 1 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","*        *","*        *","*        *","*        *","*        *","* +----- *","**********");
           break;
        case 2 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +      *","* |      *","* |      *","* |      *","* |      *","* +----- *","**********");
           break;
        case 3 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |      *","* |      *","* |      *","* |      *","* +----- *","**********");
           break;
        case 4 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |  |   *","* |      *","* |      *","* |      *","* +----- *","**********");
           break;
        case 5 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |  |   *","* |  O   *","* |      *","* |      *","* +----- *","**********");
           break;
        case 6 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |  |   *","* |  O   *","* |  +   *","* |      *","* +----- *","**********");
           break;
        case 7 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |  |   *","* |  O   *","* | -+   *","* |      *","* +----- *","**********");
           break;
        case 8 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |  |   *","* |  O   *","* | -+-  *","* |      *","* +----- *","**********");
           break;
        case 9 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |  |   *","* |  O   *","* | -+-  *","* | /    *","* +----- *","**********");
           break;
        case 10 :
           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n","**********","* +--+   *","* |  |   *","* |  O   *","* | -+-  *","* | / \\  *","* +----- *","**********");
           break;                       
     }
}


/****************************************************************************
* Function isGameOver() is the final step in the program. The game is over
* if either all letters in the word have been guessed, or the player has run
* out of guesses. The player is congratulated if he/she wins. The word is
* displayed to the player if he/she loses. This function returns either 
* GAME_OVER or GAME_CONTINUE.
****************************************************************************/
int isGameOver(char* word, int* guessedLetters, unsigned wrongGuesses)
{
    char alphabet[ALPHABET_SIZE] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int i = 0;
    if(wrongGuesses == 10)
    {
       printf("\n%s\n%s%s\n","GAME OVER","The word was: ", word);
       return GAME_OVER;
    }
    while(i<strlen(word))
    {
       int j = 0;
       while(j<ALPHABET_SIZE)
       {
          if(tolower(word[i]) == alphabet[j])
          {
             if(guessedLetters[j] == 0)
             {
                return GAME_CONTINUE;
             }
             else
             {
                 break;
             }
          }
          j++;
       }
       i++;
    }
    printf("\n%s\n", "CONGRATULATIONS you WIN!");
    return GAME_OVER;
}


/****************************************************************************
* Function readRestOfLine() is used for buffer clearing. Source: 
* https://inside.cs.rmit.edu.au/~sdb/teaching/C-Prog/CourseDocuments/
* FrequentlyAskedQuestions/
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}

