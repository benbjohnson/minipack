#ifndef _memdump_h
#define _memdump_h

#include <stdio.h>

#define memdump(PTR, LENGTH) do {\
    char *address = (char*)PTR;\
    int length = LENGTH;\
    int i = 0;\
    char *line = (char*)address;\
    unsigned char ch;\
    fprintf(stderr, "%08X | ", (int)address);\
    while (length-- > 0) {\
        fprintf(stderr, "%02X ", (unsigned char)*address++);\
        if (!(++i % 16) || (length == 0 && i % 16)) {\
            if (length == 0) { while (i++ % 16) { fprintf(stderr, "__ "); } }\
            fprintf(stderr, "| ");\
            while (line < address) {\
                ch = *line++;\
                fprintf(stderr, "%c", (ch < 33 || ch == 255) ? 0x2E : ch);\
            }\
            if (length > 0) { fprintf(stderr, "\n%08X | ", (int)address); }\
        }\
    }\
    fprintf(stderr, "\n\n");\
} while(0)

#endif
