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
    char *key, *from, *to;
    int8 *encrypted,*decrypted;
    // not directly assigned int8 coz - strlen shows error
    // typecast it later

    key = "apples";
    skey = strlen(key);
    from = "shall I compare thee to a summer's day?";
    stext = strlen(from);

    printf("Initialising encryptionn....\n"); F;
    rc4 = rc4init((int8*)key,skey);
    printf("done\n");

    printf("'%s'\n ->", from );
    encrypted = rc4encrypt(rc4,(int8 *)from,stext);
    printbin(encrypted, skey);


}
