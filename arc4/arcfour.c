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

    if (p == NULL){
        perror("");
        exit(EXIT_FAILURE);
    }

    int16 x;
    for(x = 0; x<=255; x++){
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


int8 rc4byte(Arcfour *p){

    int16 temp1, temp2;

    p->i = (p->i +1)%256;
    p->j = (p->j + p->s[p->i]) %256;

    temp1 = p->s[p->i];
    temp2 = p->s[p->j];
    p->s[p->i] = temp2;
    p->s[p->j] = temp1;

    temp1 = (p->s[p->i] + p->s[p->j])%256;
    p->k = p->s[temp1];

    return p->k;

}

int8 *rc4encrypt(Arcfour *p, int8*cleartext, int16 size){
    int8 *ciphertext;
    int16 x;
    ciphertext = (int8 *)malloc(size+1);
    if (!ciphertext){
        perror("");
        exit(EXIT_FAILURE);
    }

    for(x=0; x<size; x++){
        ciphertext[x] = cleartext[x] ^ rc4byte(p);
    }

    return ciphertext;

}
