#include <iostream>
#include <fstream>

#include "./primes/primeNums.hpp"
#include "./primes/prime.hpp"
#include "./bin/binStream.hpp"
#include "./bin/cipher.hpp"

using namespace prime;
using namespace bin;

int main() {
    const std::string f_primes_path = "primes.dat";
    const std::string f_str_path = "str.dat";
    const std::string f_enc_str_path = "enc_str.dat";
    const std::string f_dec_str_path = "dec_str.dat";
    std::string f_key_path = "key.dat";
    const std::string f_disk_path = "disk.dat";
    
    std::ifstream f_file(f_str_path, std::ios::in | std::ios::binary);
    std::ofstream f_enc_file(f_enc_str_path);
    std::ofstream f_dec_file(f_dec_str_path);

    CBinStream *stream = new CBinStream();
    
    while(!stream->Read(f_file, 256)) {
        std::cout << stream->ToString() << std::endl;
    }
    std::cout << stream->ToString() << std::endl;
    CCipher *cipher = new CCipher();

    CBinStream *enc_data = new CBinStream();
    enc_data = cipher->Encrypt(stream);
    std::cout << enc_data->ToString() << std::endl;
    


    CBinStream *dec_data = new CBinStream();
    cipher->Decrypt(enc_data, dec_data);
    std::cout << dec_data->ToString() << std::endl;

    *enc_data >> f_enc_file;
    *dec_data >> f_dec_file;

    delete stream;
    delete enc_data;
    delete dec_data;
    return 0;
}