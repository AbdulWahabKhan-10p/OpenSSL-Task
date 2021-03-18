/*
This program is to encrypt file name and store it into "Originalfilename.enc"
there should be a file "AES-Key.dat" present in a same directory to execute it.
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
unsigned char ciphertext[128];
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

unsigned char aes_key[16];

void fetchData()
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
void storeData()
{
    
    FILE *fptr;
    fptr = fopen("Originalfilename.enc","wb");
   // int n = sizeof buf/sizeof *buf;
    //fwrite
    if(fptr)
    {
        fwrite(&ciphertext,sizeof(unsigned char),sizeof(ciphertext),fptr);
    
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
 
void main (int argc,char* argv[])
{
    if(argc==2)
    {
            // A 128 bit key 
        fetchData();
        unsigned char *key = aes_key;
        if(key!=NULL)
        {
                    // A 128 bit IV 
        unsigned char *iv = (unsigned char *)"0123456789012345";

        /* Message to be encrypted */
        unsigned char *plaintext =argv[1];


        /*
        * Buffer for ciphertext. Ensure the buffer is long enough for the
        * ciphertext which may be longer than the plaintext, depending on the
        * algorithm and mode.
        */
        

        /* Buffer for the decrypted text */
        unsigned char decryptedtext[128];

        int ciphertext_len=0;

        /* Encrypt the plaintext */
        ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv,
                                ciphertext);

        /* Do something useful with the ciphertext here */
        printf("Ciphertext is:\n");
        //BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
        ciphertext[ciphertext_len] = '\0';
        printf("Encrypted text is:\n");
        printf("%s\n", ciphertext);
        storeData();
        }
        else
        {
            printf("AES-Key.dat not present in a directory or empty");
        }
    
    }
    else
    {
        printf("invalid argument length \n");
    }
    
}