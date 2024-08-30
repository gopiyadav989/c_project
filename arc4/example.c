#include "arcfour.h"
#include <stdint.h>
#include <stdio.h>

void printbin(int8 *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X", data[i]);  // Print each byte as a 2-digit hexadecimal number
    }
    printf("\n");
}

#define F fflush(stdout);  // Forces the output to be displayed immediately

int main(void);

int main(){

    Arcfour *rc4;
    int16 skey, stext;
    char *key, *from, *to, *encrypted, *decrypted;

    key=from=encrypted=decrypted=0;
    from=key;

    key = "apples";
    skey = strlen(key);
    from = "shall I compare thee to a summer's day?";
    stext = strlen(from);

    printf("Initialising encryptionn....\n"); F;
    // rc4 = rc4init(key,skey);
    printf("done\n");

    printf("'%s'\n ->", from );
    // encrypted = rc4encrypt(from,stext);
    printbin((int8 *)key, skey);


}
