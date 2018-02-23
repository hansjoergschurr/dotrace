#include <stdio.h>
#include "dotrace.h"

static FILE *fp_trace;

#ifdef DOTRACE_SUSPEND
int tracing_active = 0;
#else
int tracing_active = 1;
#endif

#ifndef DOTRACE_FILE
#define DOTRACE_FILE "trace.out"
#endif

void
__attribute__ ((constructor))
__attribute__ ((no_instrument_function))
dotrace_init (void) {
	fp_trace = fopen(DOTRACE_FILE, "w");
}

void
__attribute__ ((destructor))
__attribute__ ((no_instrument_function))
dotrace_finish (void) {
	if(fp_trace != NULL) {
		fclose(fp_trace);
	}
}

void
__attribute__ ((no_instrument_function))
dotrace_start (void) {
	tracing_active = 1;
}

void
__attribute__ ((no_instrument_function))
dotrace_stop (void) {
	tracing_active = 0;
}

void
__attribute__ ((no_instrument_function))
__cyg_profile_func_enter (void *func,  void *caller) {
	if(fp_trace != NULL && tracing_active) {
		fprintf(fp_trace, "e %p %p\n", func, caller);
	}
}

void
__attribute__ ((no_instrument_function))
__cyg_profile_func_exit (void *func, void *caller) {
	if(fp_trace != NULL && tracing_active) {
		fprintf(fp_trace, "x %p %p\n", func, caller);
	}
}
