// Vigenere Cipher implementation in C
// Reference: https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
// Feel free to use this whatever way you want

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100    // example size.

int main(int argc, char argv[]){
    
    char plaintext[SIZE];   // you can define your own plaintext here, or just do a function call
    char ciphertext[SIZE];
    char key[5] = "VIPER";  // this is just an example key. Just don't define key contains special characters
    char newKey[SIZE];
    int i, j;
    // remember to set the plaintext first, otherwise comment this line out
    printf("Original plaintext: %s\n", plaintext);
    
    /* Generating the key
     i is to keep track of the indices in the string, j is for the original key
     now I have to hard code j == 5 instead of j == strlen(key) since there is 
     a known problem in Windows computer that run Cygwin: strlen() will count null character '\0'
     as an extra character.  If you are using Linux/UNIX, replace 5 with strlen(key)*/
    
    for (i = 0, j = 0; i < strlen(plaintext); i++, j++){
        if (isalpha(plaintext[i])){         // if this part of plaintext is an alphabet character
            if (j == 5){                    // reach the end of key, reset counter
                j = 0;   
            }  
            newKey[i] = key[j];   
        }
        else {      
            if (j == 5){                    // always reset the counter   
                j = 0;    
            }
            newKey[i] = ' ';    // simply ignore it (not a alphabet character)
            j-=1;
        }
    }
    newKey[i] = '\0';       // proper null character termination of the string (so we don't have giberish at the end).
    printf("Key generated: %s\n", newKey);   // checking if your product is correct

    // encryption:
    // you can choose to uppercase final ciphertext. In my encryption I want it to be case sensitive.      
    for(i = 0; i < strlen(plaintext); i++){
        if (isalpha(newKey[i])){        // checking if this is an alphabet character (ignore special characater)
            char alpha = islower(plaintext[i]) ? 'a' : 'A';   // offset by upper case character since we want the output to be case sensitive
            ciphertext[i] = ((toupper(plaintext[i]) + newKey[i]) % 26) + alpha;   // Vigenere cipher formula
        }
        else {
            ciphertext[i] = plaintext[i];      //not alphabet => no need for encryption
        }
    }
    ciphertext[i] = '\0';
    printf("Cipher text: %s\n", ciphertext);  

    // decryption:
    // if you choose to make your cipher text all uppercase, then remove toupper()
    for(i = 0; i < strlen(ciphertext); i ++){
        if(isalpha(plaintext[i])){
            char alpha = islower(plaintext[i]) ? 'a' : 'A';
            plaintext[i] = ((toupper(ciphertext[i]) - newKey[i] + 26) % 26) + alpha;    //adding 26 to get back the correct ASCII value
        }
        else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
    printf("Plaintext: %s\n", plaintext);
    
    return 0;
}
