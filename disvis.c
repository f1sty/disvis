#include <stdio.h>
#include <stdlib.h>
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

void usage(char *name) {
  fprintf(stderr, "Usage: %s <filename>\n", name);
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  FILE *fp;
  fp = fopen(argv[1], "rb");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  size_t nbytes = 64;
  size_t length = 0;
  char *buffer = (char *)malloc(0);

  while (!feof(fp)) {
    buffer = (char *)realloc(buffer, length + nbytes);
    length += fread(buffer + length, 1, nbytes, fp);
  }

  buffer[length] = '\0';

  char *token, *str;
  int i;
  int ntokens = 1024;
  char **tokens = (char **)calloc(ntokens, 8);

  for (i = 0, str = buffer; ; i++, str = NULL) {
    if (i >= ntokens) {
      ntokens += ntokens;
      tokens = (char **)realloc(tokens, ntokens * 8);
    }
    if ((token = strtok(str, " \n")) == NULL) break;
    tokens[i] = token;
  }

  size_t distance;

  for(int j = 0; j < i - 1; j++) {
    distance = levenshtein_distance(tokens[j], tokens[j + 1]);
    printf("%zu\n", distance);
  }

  free(tokens);
  free(buffer);
  return 0;
}
