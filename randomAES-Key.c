/*
this program will create a random AES-KEY and store it into "AES-Key.dat", so that AES-128-Encryption.c and AES-128-Decryption.c can use it for 
encryption and decryption
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <time.h>

unsigned char buf[16];


void storeData()
{
    
    FILE *fptr;
    fptr = fopen("Aes_key.dat","wb");
   // int n = sizeof buf/sizeof *buf;
    //fwrite
    if(fptr)
    {
        fwrite(&buf,sizeof(unsigned char),16,fptr);
    
    }
    
  /*  int i = 0;
    while (n!=0)
    {
       fprintf(fptr,"%c ", buf[i]);
        n--;
        i++;
    }
    */
    fclose(fptr);
   
    
}
//memset funtion to zero out the buf

void main()
{

int i=0;
int random =0;

srand(time(NULL));

for (i = 0; i < sizeof(buf); i++)
    {
        random =  (rand() % (122-48+1)+48);
        
        printf("%d \n",random);
        buf[i] =(unsigned char ) random;
       
    }
for (i = 0; i < sizeof(buf); i++)
    {
        printf("%c \n",buf[i]);
    }
memset(&buf,0,sizeof(buf));
storeData();
}

