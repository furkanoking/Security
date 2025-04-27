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

Security::Security(){
    std::cout<<"Hello"<<std::endl;
    randomKeyGenerating();
    for(int i=0;i<32;i++){
        printf("%02X ", Key[i]);  // Büyük harfli hexadecimal
        //std::cout<<std::hex<<Key[i];
    }
    std::cout<<"  "<<std::endl;
    //std::cout<<std::hex<<NonceValue<<std::endl;

}


Security::~Security(){

}

template<typename T>
void Security::MakeHash(T data, uint64_t* hashedvalue){
   
    std::string sData = std::to_string(data);

    const unsigned char* SendingData = reinterpret_cast<const unsigned char*>(sData.data());

    unsigned char HashedData[SHA256_DIGEST_LENGTH];
    SHA256(SendingData,sData.length(),HashedData);



    for(int i=0;i<SHA256_DIGEST_LENGTH;i++){
        printf("%02x", HashedData[i]);
    }
    //uint64_t zort[4];
    std::cout<<"******************"<<std::endl;
    memcpy(hashedvalue,HashedData,32);

    *hashedvalue = be64toh(*hashedvalue) ;
    *(hashedvalue+1) = be64toh(*(hashedvalue + 1));
    *(hashedvalue+2) = be64toh(*(hashedvalue + 2));
    *(hashedvalue+3) = be64toh(*(hashedvalue + 3));
}

template void Security::MakeHash<int>(int,uint64_t*);


void Security::randomKeyGenerating() {
        RAND_bytes(Key,sizeof(Key));
        RAND_bytes(NonceValue,sizeof(NonceValue));
}

template < typename T>
void Security::MakeEncryption(T data) noexcept{

    static_assert(std::is_same_v<T,uint64_t> || std::is_same_v<T,char*>);

    unsigned char ciphertext[sizeof(data)];
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int SizeofCipherText;

    // Set the key and the NonceValue
    EVP_EncryptInit_ex(ctx,EVP_chacha20(),NULL,Key,NonceValue);


        

    if constexpr (std::is_same_v<T,uint64_t>)  {
        unsigned char plaindata[8];
        memcpy(plaindata,&data,sizeof(data));
        if(1 !=EVP_EncryptUpdate(ctx,ciphertext,&SizeofCipherText,plaindata,sizeof(plaindata))){
            std::cout<<"Error in Encryption"<<std::endl;
        }
    
    }    

    else if constexpr(std::is_same_v<T,const unsigned char*>)  {
        if(1!=EVP_EncryptUpdate(ctx,ciphertext,&SizeofCipherText,data,sizeof(data))) {
            std::cout<<"Error in Encryption"<<std::endl;
        }

    }

    else {
        std::cout<<"Wrong type"<<std::endl;
    }
}

template void Security::MakeEncryption<uint64_t>(uint64_t);

template void Security::MakeEncryption<char*>(char*);
