#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100
// program to encrypt user string by keyword entered in command line

int main(int argc, char argv[]){
    // you can define your own plaintext here.
    // or just do a function call, doesn't matter.
    char plaintext[SIZE];
    char ciphertext[SIZE];
    // this is just an example key. Make one yourself if you want.
    // just don't pick key contains special characters
    char key[5] = "VIPER";          
    char newKey[SIZE];
    
    // remember to set the plaintext first, otherwise comment this line out
    printf("Original plaintext: %s\n", plaintext);
    
    /* generating the key
     i to keep track of the indices in the string, j is for the original key
     now I have to hard code j == 5 instead of j == strlen(key) since there is 
     a known problem in Windows computer that run Cygwin:
     strlen() will count null character '\0' as an extra character. 
     If you are using Linux/UNIX like I should have, replace 5 with strlen(key)  */
    
    for (int i = 0, j = 0; i < strlen(plaintext); i++, j++){
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
            newKey[i] = ' ';    // simply ignore it (not a alphabet character)
            j-=1;
        }
    }
  
    printf("Key generate: %s\n", newKey);

    // encryption
    for(int i = 0; i < strlen(plaintext); i++){
        if (isalpha(newKey[i])){
            char alpha = islower(plaintext[i]) ? 'a' : 'A';   // offset by upper case character since we want the output to be uppercase
            ciphertext[i] = ((toupper(plaintext[i]) + newKey[i]) % 26) + alpha;   // Vigenere cipher formula
        }

        else {
            ciphertext[i] = plaintext[i];      //not alphabet => no need for encryption
        }
    }

    printf("Cipher text: %s\n", ciphertext);

    // decryption:
    
    for(int i = 0; i < strlen(ciphertext); i ++){
        if(isalpha(plaintext[i])){
            char alpha = islower(plaintext[i]) ? 'a' : 'A';
            plaintext[i] = ((toupper(ciphertext[i]) - newKey[i] + 26) % 26) + alpha;    //adding 26 to get back the correct ASCII value
        }
      
        else {
            plaintext[i] = ciphertext[i];
        }
    }

    printf("Plaintext: %s\n", plaintext);
    return 0;
}
