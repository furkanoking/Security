#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Security.h"
#include <cstring>
#include <endian.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

template <typename T>
Security<T>::Security(){
    std::cout<<"Hello"<<std::endl;

    static_assert(std::is_same_v<T,uint64_t> || std::is_same_v<T,int> || std::is_same_v<T,unsigned char> ,
        "It only accepts uint64_t, int or char");
    randomKeyGenerating();
    for(int i=0;i<32;i++){
        //printf("%02X ", Key[i]);  // Büyük harfli hexadecimal
        //std::cout<<std::hex<<Key[i];
    }
    std::cout<<"  "<<std::endl;
    //std::cout<<std::hex<<NonceValue<<std::endl;

}

template <typename T>
Security<T>::~Security(){}

template <typename T>
Security<T> Security<T>::operator=(Security& OtherSecurity){
    memcpy(this->Key,OtherSecurity.Key,32);
    memcpy(this->NonceValue,OtherSecurity.NonceValue,12);
}

template <typename T>
void Security<T>::MakeHash(T data, uint64_t* hashedvalue){
   
    unsigned char HashedData[SHA256_DIGEST_LENGTH];


    if constexpr(std::is_same_v<T,unsigned char>) {
        SHA256(&data,sizeof(data),HashedData);
    }

    else if constexpr(std::is_same_v<T,uint64_t>) {
        std::string sData = std::to_string(data);
        const unsigned char* SendingData = reinterpret_cast<const unsigned char*>(sData.data());
        SHA256(SendingData,sData.length(),HashedData);
    }

    else {
        std::cout<<"Wrong type for MakeHash"<<std::endl;
        return;
    }



    /*
    for(int i=0;i<SHA256_DIGEST_LENGTH;i++){
        printf("%02x", HashedData[i]);
    }
    //uint64_t zort[4];
    std::cout<<"******************"<<std::endl;

    */
    memcpy(hashedvalue,HashedData,32);

    *hashedvalue = be64toh(*hashedvalue) ;
    *(hashedvalue+1) = be64toh(*(hashedvalue + 1));
    *(hashedvalue+2) = be64toh(*(hashedvalue + 2));
    *(hashedvalue+3) = be64toh(*(hashedvalue + 3));
}
 
//void Security<T>::MakeHash(int,uint64_t*);

template <typename T>
void Security<T>::randomKeyGenerating() {
        RAND_bytes(Key,sizeof(Key));
        RAND_bytes(NonceValue,sizeof(NonceValue));
}

template <typename T>
void Security<T>::MakeEncryption(T data, T** EncrypedData) noexcept{

    //static_assert(std::is_same_v<T,uint64_t> || std::is_same_v<T,char*>);

    unsigned char ciphertext[sizeof(data)];
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int SizeofCipherText = 0;
    int FinalSizeofCipherText = 0;

    // Set the key and the NonceValue
    EVP_EncryptInit_ex(ctx,EVP_chacha20(),NULL,Key,NonceValue);      

    if constexpr (std::is_same_v<T,uint64_t>)  {

        unsigned char plaindata[8];
        memcpy(plaindata,&data,sizeof(data));

        if(1 !=EVP_EncryptUpdate(ctx,ciphertext,&SizeofCipherText,plaindata,sizeof(plaindata))){
            std::cout<<"Error in Encryption"<<std::endl;
        }

        EVP_EncryptFinal_ex(ctx,ciphertext + SizeofCipherText,&FinalSizeofCipherText);
        // Save the encrypted file into the 
        memcpy(*EncrypedData, ciphertext, 8);
 
    }    

    else if constexpr(std::is_same_v<T,unsigned char>)  {
        if(1!=EVP_EncryptUpdate(ctx,ciphertext,&SizeofCipherText,&data,sizeof(data))) {
            std::cout<<"Error in Encryption"<<std::endl;
        }

        EVP_EncryptFinal_ex(ctx,ciphertext + SizeofCipherText,&FinalSizeofCipherText);

        memcpy(*EncrypedData,ciphertext,sizeof(data));

    }

    else {
        std::cout<<"Wrong type"<<std::endl;
    }


}

template <typename T>
void Security<T>::MakeDecryption(T data, T** DecryptedData) noexcept {


    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int SizeofCipherText = 0;
    int FinalSizeofCipherText = 0;
    unsigned char plaintext [sizeof(data)];

    if(!ctx){
        throw std::runtime_error("Failed to create EVP_CIPHER_CTX pointer");
    }


    // Initiliaze decryption
    if(1 != EVP_DecryptInit_ex(ctx,EVP_chacha20(),NULL,Key,NonceValue)){
        throw std::runtime_error("Failed to EVP_DecryptInit_ex");
    }

    if constexpr (std::is_same_v<T,uint64_t>){
        
        unsigned char EncryptedData[8];
        memcpy(EncryptedData,&data,8);
        
        if(1!= EVP_DecryptUpdate(ctx,plaintext,&SizeofCipherText,EncryptedData,sizeof(data))) {
            throw std::runtime_error("Failed to EVP_DecryptUpdate");
        }
        
        if (1!= EVP_DecryptFinal_ex(ctx,plaintext + SizeofCipherText,&FinalSizeofCipherText)){
            throw std::runtime_error("Failed to EVP_DecryptFinal_ex");
        }
        
        memcpy(*DecryptedData,plaintext,sizeof(data));
    }

    else if constexpr (std::is_same_v<T,unsigned char>){

        if(1!= EVP_DecryptUpdate(ctx,plaintext,&SizeofCipherText,&data,sizeof(data))) {
            throw std::runtime_error("Failed to EVP_DecryptUpdate");
        }

        if (1!= EVP_DecryptFinal_ex(ctx,plaintext + SizeofCipherText,&FinalSizeofCipherText)){
            throw std::runtime_error("Failed to EVP_DecryptFinal_ex");
        }

        memcpy(*DecryptedData,plaintext,sizeof(data));
    }

    else {
        std::cout<<"Wrong type !!!!"<<std::endl;
    }
}
template class Security<int>;
template class Security<uint64_t>;
template class Security<unsigned char>;

//TODO We will add a size value for char Because the system works for 1 byte. We have to handle the size.
 
