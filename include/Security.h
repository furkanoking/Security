class Security {
    public:
    Security();
    ~Security();


    template<typename T>
    void MakeHash(T data);
    void yap();
};