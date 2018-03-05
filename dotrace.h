#ifndef DOTRACE_H
#define DOTRACE_H

int dotrace_active;

/** 
Starts tracing.

Unless the preprocesser variable DOTRACE_SUSPEND is set, tracing is
active when the program starts.
*/
void dotrace_start (void);
/** 
Stops tracing.
*/
void dotrace_stop (void);

#endif
