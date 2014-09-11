1. pi.c program compute the first 10000 decimals of the  number. Optimize pi.c in order to reach the server's threshold.
	(a) Look at the source code of the program, and in particular, study the source code of routine DIVIDE.
	(b) Profile and analyze the program behavior.
	(c) Modify the code (bithacks, change complicated arithmetic expressions by other with the same result, specializing routine/s, memoization, inlining, code hoisting, loop unrolling, loop collapsing, loop fusion, changing condition evaluation order, removing branches with difficult prediction, etc)
	(d) Profile the new version of the program and compare it with the profile of the original code.
	(e) Which speed-up have you obtained?
	(f) Go back to (a) until you execution time is less or equal to 1.8 seconds

gcc --version
gcc (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3
Copyright (C) 2012 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

uname -a
Linux lastenia 3.8.0-19-generic #30-Ubuntu SMP Wed May 1 16:35:23 UTC 2013 x86_64 x86_64 x86_64 GNU/Linux
