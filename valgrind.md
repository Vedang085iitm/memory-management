
# Valgrind


## Program 1: Accessing an Out-of-Bounds Element

````c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int *)malloc(100 * sizeof(int));
    
    // Set data[100] to zero
    data[100] = 0;
    
    free(data);

    return 0;
}

````
### Output without Valgrind:

It may or may not crash with the GCC compiler.

### Output with Valgrind:

````
==12345== Memcheck, a memory error detector
==12345== Copyright (C) 2002-2021, and GNU GPL'd, by Julian Seward et al.
==12345== Using Valgrind-3.17.0 and LibVEX; rerun with -h for copyright info
==12345== Command: ./prog
==12345==
==12345== Invalid write of size 4
==12345==    at 0x109175: main (prog.c:7)
==12345==  Address 0x4 is not stack'd, malloc'd or (recently) free'd
==12345==
==12345==
==12345== Process terminating with default action of signal 11 (SIGSEGV): dumping core
==12345==  Access not within mapped region at address 0x4
==12345==    at 0x109175: main (prog.c:7)
==12345==  If you believe this happened as a result of a stack
==12345==  overflow in your program's main thread (unlikely but
==12345==  possible), you can try to increase the size of the
==12345==  main thread stack using the --main-stacksize= flag.
==12345==  The main thread stack size used in this run was 8388608.
==12345==
==12345== HEAP SUMMARY:
==12345==     in use at exit: 400 bytes in 1 block
==12345==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
==12345==
==12345== LEAK SUMMARY:
==12345==    definitely lost: 0 bytes in 0 blocks
==12345==    indirectly lost: 0 bytes in 0 blocks
==12345==      possibly lost: 0 bytes in 0 blocks
==12345==    still reachable: 400 bytes in 1 block
==12345==         suppressed: 0 bytes in 0 blocks
==12345== Rerun with --leak-check=full to see details of leaked memory
==12345==
==12345== For lists of detected and suppressed errors, rerun with: -s
==12345== ERROR SUMMARY: 1 error from 1 context (suppressed: 0 from 0)
Segmentation fault (core dumped)

````
## Program 2: Accessing Freed Memory

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *data = (int *)malloc(100 * sizeof(int));    
    // Free the allocated memory
    free(data);
    // Try to print one element of the freed array
    printf("%d\n", data[0]);
    return 0;
}
````

### Output without Valgrind:

It may or may not crash with the GCC compiler.

### Output with Valgrind:

````
==12345== Memcheck, a memory error detector
==12345== Copyright (C) 2002-2021, and GNU GPL'd, by Julian Seward et al.
==12345== Using Valgrind-3.17.0 and LibVEX; rerun with -h for copyright info
==12345== Command: ./prog
==12345==
==12345== Invalid read of size 4
==12345==    at 0x1091A5: main (prog.c:9)
==12345==  Address 0x4 is not stack'd, malloc'd or (recently) free'd
==12345==
==12345==
==12345== Process terminating with default action of signal 11 (SIGSEGV): dumping core
==12345==  Access not within mapped region at address 0x4
==12345==    at 0x1091A5: main (prog.c:9)
==12345==  If you believe this happened as a result of a stack
==12345==  overflow in your program's main thread (unlikely but
==12345==  possible), you can try to increase the size of the
==12345==  main thread stack using the --main-stacksize= flag.
==12345==  The main thread stack size used in this run was 8388608.
==12345==
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==12345==
==12345== All heap blocks were freed -- no leaks are possible
==12345==
==12345== For lists of detected and suppressed errors, rerun with: -s
==12345== ERROR SUMMARY: 1 error from 1 context (suppressed: 0 from 0)
Segmentation fault (core dumped)
```


These programs demonstrate issues with memory access and management. Program 1 exhibits an invalid write, while Program 2 attempts to access freed memory. Valgrind helps identify these issues, making it a valuable tool for debugging memory-related problems in your code