/*
This program is to decrypt file name that is stored it into "Originalfilename.enc"
there should be a file "AES-Key.dat" and "Originalfilename.enc" present in a same directory to execute it.
*/


#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}


int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

unsigned char aes_key[16];

void fetchkey()
{
    
    int n,i=0;
    FILE *fptr;
    unsigned char *p;
    p=aes_key;
    memset(&aes_key,0,16);
    fptr = fopen("Aes_key.dat","rb");
   // fscanf(fptr,"%d",&n);
    n=15;

    if(fptr)
    {
      fread(&aes_key,sizeof(unsigned char),16,fptr);
       
    }
   /* while(n!=0)
    {
        fscanf(fptr,"%c",&aes_key[i]);
        i++;
        n--;
    } 
  */
    
    fclose(fptr);
    //return p;
}

unsigned char filename[128];
void fetchData()
{
    

    FILE *fptr;

    memset(&filename,0,128);
    fptr = fopen("Originalfilename.enc","rb");
   // fscanf(fptr,"%d",&n);

   
    if(fptr)
    {
      fread(&filename,sizeof(unsigned char),128,fptr);
       
    }
   /* while(n!=0)
    {
        fscanf(fptr,"%c",&aes_key[i]);
        i++;
        n--;
    } 
  */
    
    fclose(fptr);
    //return p;
}

  
void main (int argc,char* argv[])
{
    if(argc==1)
    {
        
            // A 128 bit key 
        fetchkey();
        unsigned char *key = aes_key;
        
        // A 128 bit IV 
        unsigned char *iv = (unsigned char *)"0123456789012345";

        /* Message to be encrypted */
        
        unsigned char decryptedtext[128];
        
        int decryptedtext_len=0;
        fetchData();
        for(int i =0; i<sizeof(filename);i++)
        {
            printf("%c",filename[i]);
        }
        /* Decrypt the ciphertext */
        decryptedtext_len = decrypt(filename, sizeof(filename), key, iv,
                                    decryptedtext);

        /* Add a NULL terminator. We are expecting printable text */
        decryptedtext[decryptedtext_len] = '\0';

        /* Show the decrypted text */
        printf("Decrypted text is:\n");
        printf("%s\n", decryptedtext);
    }
    
}



