find_package(OpenSSL REQUIRED)

target_include_directories(SecurityLib PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(SecurityLib PRIVATE OpenSSL::Crypto)