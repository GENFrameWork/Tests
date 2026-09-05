# --------------------------------------------------------------------
# unittests_cipher : Cipher Unit Tests (Google Test console mode)
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(unittests_cipher)



set(GEN_DIRECTORY "../../..") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

option(COVERAGE_CREATEINFO_FEATURE                              "Coverage - Create Info"                                  ON )

option(LINUX_VISUALSTUDIO_UTF8_FEATURE                          "Linux CodePage Editor UTF8"                              ON )

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )

option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )

option(DIO_FEATURE                                              "Input/Output"                                            ON )
option(DIO_STREAMTLS12_FEATURE                                  "TLS 1.2 (RFC 5246)"                                      OFF)

option(XSLEEP_FEATURE                                           "XSleep"                                                  ON )
option(XUUID_FEATURE                                            "UUID functions"                                          ON )
option(XASN1_FEATURE                                            "ANS.1"                                                   ON )
option(XSERIALIZABLE_BINARY_FEATURE                             "Serializable Binary"                                     ON )
option(XSERIALIZABLE_JSON_FEATURE                               "Serializable JSON"                                       ON )
option(XASN1_FEATURE                                            "ANS.1"                                                   ON )
option(XFILE_INI_FEATURE                                        "XFile INI format"                                        ON )

option(HASH_FEATURE                                             "Hash"                                                    ON )
option(HASH_CRC16_FEATURE                                       "Hash CRC16"                                              ON )
option(HASH_CKS16_FEATURE                                       "Hash CKS16"                                              ON )
option(HASH_CRC32_FEATURE                                       "Hash CRC32"                                              ON )
option(HASH_MD5_FEATURE                                         "Hash MD5"                                                ON )
option(HASH_SHA1_FEATURE                                        "Hash SHA1"                                               ON )
option(HASH_SHA2_FEATURE                                        "Hash SHA2"                                               ON )
option(HASH_COMP128V1_FEATURE                                   "Hash COMP128v1"                                          ON )
option(HASH_WHIRLPOOL_FEATURE                                   "Hash Whirlpool"                                          ON )
option(HASH_HMAC_FEATURE                                        "Hash HMAC"                                               ON )

option(CIPHER_SYMMETRIC_FEATURE                                 "Cipher Symmetric"                                        ON )
option(CIPHER_SYMMETRIC_DES_FEATURE                             "Cipher Symmetric DES/3DES"                               ON )
option(CIPHER_SYMMETRIC_AES_FEATURE                             "Cipher Symmetric AES"                                    ON )
option(CIPHER_SYMMETRIC_AESGCM_FEATURE                          "Cipher Symmetric AES-GCM"                                ON )
option(CIPHER_SYMMETRIC_CHACHA20POLY1305_FEATURE                "Cipher Symmetric ChaCha20-Poly1305"                      ON )
option(CIPHER_SYMMETRIC_BLOWFISH_FEATURE                        "Cipher Symmetric Blowfish"                               ON )
option(CIPHER_HKDF_FEATURE                                      "Cipher HKDF"                                             ON )

option(CIPHER_ASYMMETRIC_FEATURE                                "Cipher Asymmetric"                                       ON )
option(CIPHER_ASYMMETRIC_RSA_FEATURE                            "Cipher Asymmetric RSA"                                   ON )
option(CIPHER_ASYMMETRIC_FILEKEY_PEM                            "Cipher Asymmetric PEM file keys"                         ON )
option(CIPHER_ASYMMETRIC_X25519_FEATURE                         "Cipher Asymmetric ECDSA/X25519"                          ON )
option(CIPHER_ASYMMETRIC_ED25519_FEATURE                        "Cipher Asymmetric Ed25519"                               ON )
option(CIPHER_ASYMMETRIC_MLKEM768_FEATURE                       "Cipher Asymmetric ML-KEM-768"                            ON )
option(CIPHER_ASYMMETRIC_MLKEM1024_FEATURE                      "Cipher Asymmetric ML-KEM-1024"                           ON )


option(GOOGLETEST_FEATURE                                       "Google Test functionality"                               ON )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake")


# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashCRC16.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashCKS16.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashCRC32.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashMD5.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashSHA1.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashSHA2.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashCOMP128v1.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashWhirlpool.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_HashHMAC.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherKey.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherKeySymmetrical.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherDES.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_Cipher3DES.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherAES.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherAESGCM.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherChaCha20Poly1305.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherBlowfish.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherHKDF.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherRSA.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherKeyECDSA.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherECDSA.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherEd25519.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherECDSAX25519.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherMLKEM768.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherMLKEM1024.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherX25519MLKEM768.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherSecP256r1MLKEM768.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherSecP384r1MLKEM1024.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherPEMCodec.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherCredentialsLoader.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherCredentialsProvider.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherCertificateX509.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherKeysFilePEM.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Cipher_CipherTrustedRootCertificatesX509.cpp")


# --------------------------------------------------------------------
# End Proyect

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")
