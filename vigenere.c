// Vigenere Cipher implementation in C
// Reference: https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
// Feel free to use this whatever way you want

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100   

int main(int argc, char argv[]){
    
    char plaintext[SIZE];   
    char ciphertext[SIZE];
    char key[5] = "VIPER";  // example key
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
            if (j == 5){                       
                j = 0;    
            }
            newKey[i] = ' ';    
            j-=1;
        }
    }
    newKey[i] = '\0';       
    printf("Key generated: %s\n", newKey);   

    // encryption:
    // you can choose to uppercase final ciphertext. In my encryption I want it to be case sensitive.      
    for(i = 0; i < strlen(plaintext); i++){
        if (isalpha(newKey[i])){       
            char alpha = islower(plaintext[i]) ? 'a' : 'A';  
            ciphertext[i] = ((toupper(plaintext[i]) + newKey[i]) % 26) + alpha;  
        }
        else {
            ciphertext[i] = plaintext[i];      
        }
    }
    ciphertext[i] = '\0';
    printf("Cipher text: %s\n", ciphertext);  

    // decryption:
    // if you choose to make your cipher text all uppercase, then remove toupper()
    for(i = 0; i < strlen(ciphertext); i ++){
        if(isalpha(plaintext[i])){
            char alpha = islower(plaintext[i]) ? 'a' : 'A';
            plaintext[i] = ((toupper(ciphertext[i]) - newKey[i] + 26) % 26) + alpha;   
        }
        else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
    printf("Plaintext: %s\n", plaintext);
    
    return 0;
}
