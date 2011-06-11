#include "includes.h"

#ifndef HODIE_RELEASE
#define HODIE_RELEASE "Please include 'version.h' before compilation"
#endif

void
print_version(void)
{
    printf("hodie %s\n", HODIE_RELEASE);
    printf("\nCopyright (c) 2000, Mikael Johansson\n");
    printf("Released under MIT-style license. Please read the file\n");
    printf("LICENSE distributed with the source code for details\n");
}
