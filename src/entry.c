#include "types/sys.h"

#include "eng/main.h"

int main(int argc, char **argv) {
  exit_code c;

  eng_args args = {0};
  c = eng_args_init(&args, argc, argv);
  if (c) return c;

  c = eng_main(&args);
  if (c) return c;

  return 0;
}

exit_code eng_args_init(eng_args *self, int argc, char **argv) {
  self->invoc = *argv;

  for (int i = 1; i < argc; i++) {
    if (*argv[i] == '+') {
      if (!strcmp(argv[i] + 1, "res")) {
        if (++i < argc) {
          if (sscanf(argv[i], "%ux%u", &self->width, &self->height) != 2) {
            fprintf(stderr, "%s: %s argument %s is not of form WIDTHxHEIGHT\n", self->invoc, argv[i - 1], argv[i]);
            return 1;
          }
        } else {
          fprintf(stderr, "%s: no font path provided for option %s\n", self->invoc, argv[i - 1]);
          return 1;
        }
      } else {
        fprintf(stderr, "%s: unknown option %s\n", self->invoc, argv[i]);
        return 1;
      }
    }
  }

  return 0;
}
