#include <cstdint>

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

};