#include <stdio.h>
#include <string.h>
#include <ctype.h>

char secretWord[20];
char guesses[26];
int attempts = 0;

void defineWord() {
  sprintf(secretWord, "HANGMAN");
}

void opening() {
  printf("***************************\n");
  printf("*      HANGMAN GAME       *\n");
  printf("***************************\n\n");
}

int hasGuessed(char letter) {
  int found = 0;

  for (int j = 0; j < attempts; j++)
  {
    if (guesses[j] == letter)
    {
      found = 1;
      break;
    }
  }

  return found;
}

void drawHanger() {
  for (int i = 0; i < strlen(secretWord); i++)
    {
      int found = hasGuessed(secretWord[i]);

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
}

void makeGuess() {
  char guess;
    printf("Choose a letter: ");
    scanf(" %c", &guess);
    guess = toupper(guess);

    guesses[attempts] = guess;
    attempts++;
}

int main() {
  int won = 0;
  int hanged = 0;

  defineWord(secretWord);
  opening();

  do
  {
    drawHanger();

    makeGuess();

  } while (!won && !hanged);

}
