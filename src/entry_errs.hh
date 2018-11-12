#pragma once

#ifndef ENTRY_ERRS_HH
#define ENTRY_ERRS_HH

#include "t_sys.hh"
#include "t_grammar.hh"

exit_code entry_err_dup(const char *, const char *);
exit_code entry_err_incompat(const char *, const char *, grammar_num, const char *);

#endif
