#include <cstdint>
#include <type_traits>

/**
 * @brief It is a class that hve certain abilities such as taking Hash value, encoding and generating keys
 * 
 */

 template <typename T>
class Security {
    public:
    Security();
    ~Security();

    Security operator=(Security& OtherSecurity);


    /**
     * @brief The funcions find the hash value of an integer. 
     * 
     * @param data 
     * @param HashedValue 
     */
    void MakeHash(T data,uint64_t* HashedValue);

    void MakeEncryption(T data, T** EncryptedData) noexcept;

    void MakeDecryption(T data, T** DecryptedData) noexcept;

    private:
    unsigned char Key[32]; // 256 bit
    unsigned char NonceValue[12]; // 92 bit

    /**
     * @brief This function only works in constructor. It generates Key and IV for encryption
     * 
     */
    void randomKeyGenerating();

};

