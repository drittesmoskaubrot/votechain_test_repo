#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
 
int main (int argc, char *argv[]) {

        if ( argc != 2 ){ /* argc should be 2 for correct execution */
          /* We print argv[0] assuming it is the program name */
          printf( "usage: sha256.01 <string to hash>" );
        }
        else{
        	const char *s = argv[1];
        	unsigned char *d = SHA256(s, strlen(s), 0);
 
        	int i;
        	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	        	printf("%02x", d[i]);
         	putchar('\n');
 
        	return 0;
        }
}
