#include "Security.h"
#include <iostream>
#include <cstdint>


int main() {
    Security mysecurity;
    int x=5;
    uint64_t a[4];
    mysecurity.MakeHash(x,a);
    std::cout<<std::hex<<*a<<std::endl;
    std::cout<<std::hex<<*(a+1)<<std::endl;;
    std::cout<<std::hex<<*(a+2)<<std::endl;;
    std::cout<<std::hex<<*(a+3)<<std::endl;;

    uint64_t y=12;
    mysecurity.MakeEncryption(y);
    //mysecurity.yap();
}