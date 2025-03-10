#include <stdio.h>
#include <string.h>

// Swap two bytes
void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

// Initialize the S-box with the key
void init_rc4(unsigned char *key, int key_length, unsigned char *S) {
    int i, j = 0;
    
    // Initialize S-box
    for (i = 0; i < 256; i++) {
        S[i] = i;
    }
    
    // Key-scheduling algorithm (KSA)
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(&S[i], &S[j]);
    }
}

// Generate keystream and encrypt plaintext
void rc4_encrypt(unsigned char *S, unsigned char *plaintext, unsigned char *ciphertext, 
                unsigned char *keystream, int length) {
    int i = 0, j = 0, k;
    
    // Pseudo-random generation algorithm (PRGA)
    for (k = 0; k < length; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
        keystream[k] = S[(S[i] + S[j]) % 256];
        ciphertext[k] = plaintext[k] ^ keystream[k];
    }
}

int main() {
    // Define the custom key
    unsigned char key[] = "SecretKey";
    int key_length = strlen((char *)key);
    
    // Define the plaintext to encrypt
    unsigned char plaintext[] = "Hanoi University of Science and Technology";
    int plaintext_length = strlen((char *)plaintext);
    
    // Declare necessary variables
    unsigned char S[256];
    unsigned char ciphertext[100];
    unsigned char keystream[100];
    
    // Initialize the S-box
    init_rc4(key, key_length, S);
    
    // Encrypt the plaintext
    rc4_encrypt(S, plaintext, ciphertext, keystream, plaintext_length);
    
    // Print the key
    printf("Key: %s\n\n", key);
    
    // Print the plaintext
    printf("Plaintext: %s\n\n", plaintext);
    
    // Print the keystream
    printf("Keystream (decimal):\n");
    for (int i = 0; i < plaintext_length; i++) {
        printf("%d ", keystream[i]);
    }
    printf("\n\n");
    
    // Print the ciphertext
    printf("Ciphertext (decimal):\n");
    for (int i = 0; i < plaintext_length; i++) {
        printf("%d ", ciphertext[i]);
    }
    printf("\n");
    
    return 0;
}
