#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../headers/hangman.h"

char secretWord[WORD_SIZE];
char guesses[26];
int attempts = 0;

void defineWord() {
  // fopen returns a pointer
  FILE* f;

  // first param: path (starting point is root); second: how it's going to be open (r = readonly)
  f = fopen("words.txt", "r");
  if (f == 0) {
    printf("Desculpe, banco de dados não disponível!\n\n");
    exit(1);
  }

  int wordsQty;
  // reading a file
  // file, type, var
  fscanf(f, "%d", &wordsQty);

  srand(time(0));
  int random = rand() % wordsQty;

  for (int i = 0; i <= random; i++) {
    fscanf(f, "%s", secretWord);
  }

  fclose(f);
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
  int fails = failedGuesses();

  printf("  _______      \n");
  printf(" |/      |     \n");
  printf(" |      %c%c%c \n", (fails >= 1 ? '(' : ' '), (fails >= 1 ? '_' : ' '), (fails >= 1 ? ')' : ' '));
  printf(" |      %c%c%c \n", (fails >= 2 ? '\\' : ' '), (fails >= 2 ? '|' : ' '), (fails >= 2 ? '/' : ' '));
  printf(" |       %c    \n", (fails >= 3 ? '|' : ' '));
  printf(" |      %c%c%c \n", (fails >= 4 ? '/' : ' '), ' ', (fails >= 4 ? '\\' : ' '));
  printf(" |             \n");
  printf("_|___          \n");
  printf("\n\n");

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

  for (int i = 0; i < strlen(guesses); i++) {
    printf("%c ", guesses[i]);
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

int failedGuesses() {
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

  return fails;
}

int hasHanged() {
  return failedGuesses() >= 5;
}

int hasWon() {
  for (int i = 0; i < strlen(secretWord); i++) {
    if (!hasGuessed(secretWord[i])) {
      return 0;
    }
  }

  return 1;
}

void addWord() {
  char choice;

  printf("Do you wish to add a new word to the game? (S/N)\n");
  scanf(" %c", &choice);
  choice = toupper(choice);

  if (choice == 'S') {
    char newWord[WORD_SIZE];
    printf("Which word it is?");
    scanf("%s", newWord);

    FILE* f;
    f = fopen("words.txt", "r+");

    if (f == 0) {
    printf("Sorry, game database not working!\n\n");
    exit(1);
  }

    int qty;
    fscanf(f, "%d", &qty);
    qty++;

    // sets the position of the "file manager" to the start
    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qty);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", newWord);

    fclose(f);
  }
}

int main() {

  defineWord(secretWord);
  opening();

  do
  {
    drawHanger();

    makeGuess();

  } while (!hasWon() && !hasHanged());

  if (hasWon()) {
    printf("Congratulations, you won the game!\n\n");
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
  }
  else {
    printf("You were hanged!\nThe correct word was *** %s ***\n\n", secretWord);
    printf("    _______________         \n");
    printf("   /               \\       \n");
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }
}
