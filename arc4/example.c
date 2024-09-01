// example.c
#include "arcfour.h"
#include <stdint.h>
#include <stdio.h>

void printbin(int8 *input,const int16 size) {
    for (int i = 0; i < size; i++) {
        if (i%2 == 0) {
            printf(" ");
        }
        printf("%.02X", input[i]);  // Print each byte as a 2-digit hexadecimal number
    }
    printf("\n");
}

#define F fflush(stdout);  // Forces the output to be displayed immediately

int main(void);

int main(){

    Arcfour *rc4;
    int16 skey, stext;
    char *key, *from; // not directly assigned int8 coz - strlen shows error typecast it later
    int8 *encrypted,*decrypted;


    key = "apples";
    skey = strlen(key);
    from = "shall I compare thee to a summer's day?";
    stext = strlen(from);

    printf("Initialising encryptionn...."); F;
    rc4 = rc4init((int8*)key,skey);
    printf("done\n");

    printf("'%s'\n ->", from );
    encrypted = rc4encrypt(rc4,(int8 *)from,stext);
    printbin(encrypted, skey);
    rc4uninit(rc4);

    printf("Encryption.... Done \n\n");

    printf("Initializing decryption...."); F;
    rc4 = rc4init((int8 *)key, skey);
    printf("done\n");

    decrypted = rc4decrypt(rc4, encrypted, stext);
    printf(" -> %s\n",decrypted);
    rc4uninit(rc4);

    return 0;
}
