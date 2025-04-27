#include <cstdint>
#include <type_traits>

/**
 * @brief It is a class that hve certain abilities such as taking Hash value, encoding and generating keys
 * 
 */
class Security {
    public:
    Security();
    ~Security();


    /**
     * @brief The funcions find the hash value of an integer. 
     * 
     * @tparam T 
     * @param data 
     * @param HashedValue 
     */
    template<typename T>
    void MakeHash(T data,uint64_t* HashedValue);

    
    template < typename T>
    void MakeEncryption(T data) noexcept;

    private:
    unsigned char Key[32]; // 256 bit
    unsigned char NonceValue[12]; // 92 bit

    /**
     * @brief This function only works in constructor. It generates Key and IV for encryption
     * 
     */
    void randomKeyGenerating();

};