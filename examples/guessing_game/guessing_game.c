#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int chute(int tentativas, int max_tentativas) {
  int guess;
  printf("[tentativa %d/%d] qual é o seu chute?", tentativas, max_tentativas);
  scanf("%u", &guess);
  return guess;
}

int feedback(int secret, int guess) {
  if( guess < secret ) {
    printf("chute foi menor que o segredo\n");
  } else if( guess > secret ) {
    printf("chute foi maior que o segredo\n");
  } else {
    printf("você acertou! o segredo é %d\n", secret);
    return 1;
  }
  return 0;
}

int main() {

  srand(time(0));
  int max_secret = 100;
  int secret = rand() % max_secret;
  int guess = -1;
  int tentativas = 0;
  int max_tentativas = 7;
  while( guess != secret && tentativas < max_tentativas) {
    guess = chute(tentativas, max_tentativas);

    if( feedback(secret, guess) ) {
      return 0;
    }
    tentativas++;
  }
  printf("Infelizmente você usou todas as suas tentativas e não acertou :(\n");
  return 1;
}
