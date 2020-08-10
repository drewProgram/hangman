#include <stdio.h>

int main() {
  char secretWord[20];

  // prints a string inside an array
  sprintf(secretWord, "HANGMAN");

  printf("%s", secretWord);
}