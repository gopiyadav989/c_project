// arcfour.c
#include "arcfour.h"

Arcfour *rc4init(int8 *key, int16 size){


    // for i from 0 to 255
    //     S[i] := i
    // endfor
    // j := 0
    // for i from 0 to 255
    //     j := (j + S[i] + key[i mod keylength]) mod 256
    //     swap values of S[i] and S[j]
    // endfor

    Arcfour *p;
    p = (Arcfour *)malloc(sizeof(struct s_arcfour));

    if (p == NULL) perror("");

    int8 x;   // i can use int also, only to look good check code na fate bas
    for(x = 0; x<256; x++){
        p->s[x] = 0;
    }
    p->i = p->j = p->k = 0;

    // to do loop with i, wikipedia docs
    for(p->i = 0; p->i <= 255; p->i++){
        p->s[p->i] = p->i;
    }

    int8 temp1,temp2;
    for(p->i = 0; p->i <= 255; p->i++){
        temp1 = p->i % size;
        temp2 = p->j + p->s[p->i] + key[temp1];
        p->j = temp2 % 256;

        temp1 = p->s[p->i];
        temp2 = p->s[p->j];

        p->s[p->i] = temp2;
        p->s[p->j] = temp1;
    }

    p->i =0;
    p->j = 0;

    return p;

}
