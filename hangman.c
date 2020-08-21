#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
  char secretWord[20];

  // prints a string inside an array
  sprintf(secretWord, "HANGMAN");

  int won = 0;
  int hanged = 0;

  char guesses[26];
  int attempts = 0;

  do
  {
    for (int i = 0; i < strlen(secretWord); i++)
    {
      int found = 0;

      for (int j = 0; j < attempts; j++)
      {
        if (guesses[j] == secretWord[i])
        {
          found = 1;
          break;
        }
      }

      if (found)
      {
        printf("%c ", secretWord[i]);
      }
      else
      {
        printf("_ ");
      }
    }
    printf("\n\n");

    char guess;
    printf("Choose a letter: ");
    scanf(" %c", &guess);
    guess = toupper(guess);

    guesses[attempts] = guess;
    attempts++;

  } while (!won && !hanged);

}
