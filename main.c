#include <stdio.h>
#include <string.h>
#include <sys/param.h>

size_t levenshtein_distance(char *a, char *b) {
  if (strlen(b) == 0) {
    return strlen(a);
  } else if (strlen(a) == 0) {
    return strlen(b);
  } else if (*a == *b) {
    return levenshtein_distance(&a[1], &b[1]);
  } else {
    size_t lev1 = levenshtein_distance(&a[1], b);
    size_t lev2 = levenshtein_distance(a, &b[1]);
    size_t lev3 = levenshtein_distance(&a[1], &b[1]);
    return 1 + MIN(lev3, MIN(lev2, lev1));
  }
}

int main(int argc, char *argv[])
{
  size_t distance = levenshtein_distance(argv[1], argv[2]);
  printf("distance = %zu\n", distance);
  return 0;
}
