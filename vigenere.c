// Simple Vigenere cipher in C
// I have to throw this online since other code I found only were inadequate
// 1. They didn't take into account special characters
// 2. Upper and lower case plaintext has different ciphertext
// 3. Spaces are not kept in ciphertext

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100
int main(){

    char plaintext[SIZE];
    char ciphertext[SIZE];
    char key[5] = "VIPER";
    char newKey[SIZE];
    
    // you can define your own plaintext here.
    // or just do a function call, doesn't matter.

    // generating the key
    // i to keep track of the indices in the string, j is for the original key
    for (int i = 0, j = 0; i < strlen(plaintext); i++, j++){
    if (isalpha(plaintext[i])){       // alphabet character
      if (j == strlen(key)){                    // reach the end of key, reset counter
        j = 0;   
      }  
      newKey[i] = key[j];   
    }

    else {      
      if (j == strlen(key)){                   
        j = 0;    
      }
      newKey[i] = ' ';    // simply ignore it
      j-=1;
    }
  }
  
  // encryption
  for(int i = 0; i < strlen(plaintext); i++){
    if (isalpha(newKey[i])){
      char alpha = islower(plaintext[i]) ? 'a' : 'A';         
      ciphertext[i] = ((toupper(plaintext[i]) + newKey[i]) % 26) + alpha;   // Vigenere cipher formula
    }

    else {
      ciphertext[i] = plaintext[i];      //not alphabet => no need for encryption
    }
  }

  // if you want to decrypt, formula is on Wiki, just reverse the bloody process
    return 0;
}
  
