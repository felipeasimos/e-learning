#include <stdio.h>

int main() {
  printf("qual é a sua altura? ");
  float height;
  scanf("%f", &height);
  printf("qual é o seu peso? ");
  float weight;
  scanf("%f", &weight);
  printf("IMC: %f\n", weight/(height * height));
  return 0;
}
