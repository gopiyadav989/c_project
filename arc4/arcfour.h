//arcfour.h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define rc4decrypt(x,y,z)  rc4encrypt(x,y,z)  // #define rc4decrypt(x,y) rc4encrypt(x,y) is used to create a macro that substitutes every occurrence of rc4decrypt(x, y) with rc4encrypt(x, y) during the preprocessing phase of compilation.
#define rc4uninit(x)        free(x)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct s_arcfour {

    int16 i,j;
    int8 s[256];

};
typedef struct s_arcfour Arcfour;

Arcfour *rc4init(int8*, int16);
int8 rcbyte(Arcfour*);
int8 *rc4encrypt(Arcfour*, int8*, int16);
