# Dotrace

Dotrace is a library which allows users to trace function calls during
the execution of a C program by utilizing GCCs `instrument-functions`
functionality. The execution generates a trace file containing
addresses. This trace file can then be decoded using the provided
`dotrace_decode.py` script.

## Dependencies 

The tool has been tested with GCC version 6.4.0, but any more or less
recent version should work. The decoding scrip requires Python 3. It
was tested with version 3.6.4. Furthermore, the `addr2line` utility is 
required by the decoding script. On many platforms this utility is part
of a `binutils` package.

Nix users can use the provided `default.nix` file with the `nix-shell`
command to get a shell with the packages required for decoding present.

## Usage

First the program and `dotrace.c` must be compiled with the compilation
option `-finstrument-functions`. The provided `dotrace.h` should also
be available in the include paths of the compile.

Here is how to do this with the provided examples:

```
> gcc -I. -finstrument-functions examples/example1.c dotrace.c
> ./a.out
```

This generates a file `trace.out`:

```
e 0x4006c0 0x7fe810ed07e0
e 0x400840 0x4006df
x 0x400840 0x4006df
x 0x4006c0 0x7fe810ed07e0
```

This can then be decoded:

```
> ./dotrace_decode.py -b a.out -t trace.out
Processing lines 1-4 [final block].
> cat trace.decoded
Enter main from ?? (??:0)
Enter square from main (??:?)
Exit square
Exit main
```

The `dotrace_decode` script provides various command line arguments to
customize the output. This is especially helpful when comparing bigger
trace files.

The filename of the trace file can be changed by overwriting the
preprocessor variable `DOTRACE_FILE`.

Furthermore the two functions `dotrace_start` and `dotrace_stop`
provided in `dotrace.h` can be used to turn tracing on and off. The
calls to these functions is not traced. To have tracing turned off
at the start of the program the `DOTRACE_SUSPEND` must be set.

The provided `examples/example2.c` file uses this functionality. To compile 
it run:

```
> gcc -I. -finstrument-functions -DDOTRACE_SUSPEND examples/example2.c dotrace.c
```

After running the resulting program, the trace file contains only the
one call to the `square` function where tracing is activated.


## References

For a documentation of the instrumentation functionality provided by
GCC see the 
[online documentation](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html).

The functionality of `dotrace` is heavily inspired by 
[this](https://balau82.wordpress.com/2010/10/06/trace-and-profile-function-calls-with-gcc/) 
blog post.

The [etrace](http://ndevilla.free.fr/etrace/) tool provides a similar
functionality, but has not been maintained for some years.
