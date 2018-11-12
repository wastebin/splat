#include <stdio.h>

#include "entry_errs.hh"

#include "t_grammar.hh"
#include "t_sys.hh"

exit_code entry_err_dup(const char *invoc, const char *thing) {
  fprintf(stderr, "%s: there may not be more than one %s\n",  invoc, thing);
  return 1;
}
exit_code entry_err_incompat(const char *invoc, const char *thing_a, grammar_num num, const char *thing_b) {
  const char *verb;
  switch (num) {
    case GRAMMAR_NUM_SG:
      verb = "is";
      break;
    case GRAMMAR_NUM_PL:
      verb = "are";
      break;
  }
  fprintf(stderr, "%s: %s %s incompatible with %s\n",  invoc, thing_a, verb, thing_b);
  return 1;
}
