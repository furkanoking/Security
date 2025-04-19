#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Security.h"


Security::Security(){
    std::cout<<"Hello"<<std::endl;
}


Security::~Security(){

}

template<typename T>
void Security::MakeHash(T data){
   
    std::string sData = std::to_string(data);

    const unsigned char* SendingData = reinterpret_cast<const unsigned char*>(sData.data());

    unsigned char HashedData[SHA256_DIGEST_LENGTH];
    SHA256(SendingData,sData.length(),HashedData);



    for(int i=0;i<SHA256_DIGEST_LENGTH;i++){
        printf("%02x", HashedData[i]);
    }
    
}

template void Security::MakeHash<int>(int);



void Security::yap() {
    std::cout<<"Hellloo"<<std::endl;
}