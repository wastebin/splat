#include "t_grammar.hh"
#include "t_sys.hh"
#include "t_vid.hh"

#include "entry_errs.hh"

#include "eng_main.hh"

int main(int argc, char **argv) {
  eng_args args = {0};

  {
    exit_code c = eng_args_init(&args, argc, argv);
    if (c) return c;
  }

  return eng_main(&args);
}

exit_code eng_args_init(eng_args *self, int argc, char **argv) {
  self->invoc = *argv;

  self->mode = VID_MODE_NONE;
  self->res = VID_RES_NONE;

  for (int i = 1; i < argc; i++) {
    // check for command line option
    if (*argv[i] == '+') {
      if (!strcmp(argv[i] + 1, "res")) {
        if (self->res) {
          return entry_err_dup(self->invoc, "resolution");
        } else if (++i < argc) {
          // attempt to get resolution argument
          if (sscanf(argv[i], "%ux%u", &self->width, &self->height) == 2) self->res = VID_RES_SPEC;
          else {
            fprintf(stderr, "%s: %s argument %s is not of form WIDTHxHEIGHT\n", self->invoc, argv[i - 1], argv[i]);
            return 1;
          }
        } else {
          fprintf(stderr, "%s: no resolution (WIDTHxHEIGHT) provided for option %s\n", self->invoc, argv[i - 1]);
          return 1;
        }
      } else if (!strcmp(argv[i] + 1, "windowed")) {
        if (self->mode) {
          return entry_err_dup(self->invoc, "video mode");
        } else if (self->res == VID_RES_AUTO) {
          return entry_err_incompat(self->invoc, "windowed mode", GRAMMAR_NUM_SG, "automatic resolution");
        } else self->mode = VID_MODE_WINDOWED;
      } else if (!strcmp(argv[i] + 1, "fullscreen")) {
        if (self->mode) {
          return entry_err_dup(self->invoc, "video mode");
        } else self->mode = VID_MODE_FULLSCREEN;
      } else if (!strcmp(argv[i] + 1, "auto-res")) {
        if (self->res) {
          return entry_err_dup(self->invoc, "resolution");
        } else if (self->mode == VID_MODE_WINDOWED) {
          return entry_err_incompat(self->invoc, "automatic resolution", GRAMMAR_NUM_SG, "windowed mode");
        } else self->res = VID_RES_AUTO;
      } else {
        fprintf(stderr, "%s: unknown option %s\n", self->invoc, argv[i]);
        return 1;
      }
    } else {
      // we currently do not accept any plain arguments
      fprintf(stderr, "%s: unexpected argument %s\n", self->invoc, argv[i]);
      return 1;
    }
  }

  return 0;
}
