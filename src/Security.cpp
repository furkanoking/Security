#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Security.h"
#include <cstring>
#include <endian.h>

Security::Security(){
    std::cout<<"Hello"<<std::endl;
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