#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../headers/hangman.h"

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

int hasHanged() {
  int fails = 0;

  for (int i = 0; i < attempts; i++) {
    int exists = 0;

    for (int j = 0; j < strlen(secretWord); j++) {
      if (guesses[i] == secretWord[j]) {
        exists = 1;
        break;
      }
    }

    if (!exists) fails++;
  }

  return fails >= 5;
}

int hasWon() {
  for (int i = 0; i < strlen(secretWord); i++) {
    if (!hasGuessed(secretWord[i])) {
      return 0;
    }
  }

  return 1;
}

int main() {

  defineWord(secretWord);
  opening();

  do
  {
    drawHanger();

    makeGuess();

  } while (!hasWon() && !hasHanged());

}
