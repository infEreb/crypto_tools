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
    const std::string f_key_path = "key.dat";
    
    std::ifstream f_primes(f_primes_path);

    CBinStream *stream = new CBinStream();
    *stream << f_primes;

    CCipher *cipher = new CCipher();

    CBinStream *enc_data = new CBinStream();
    enc_data = cipher->Encrypt(*stream);
    std::cout << cipher->GetHeader()->ToString() << std::endl;
    std::cout << enc_data->ToString() << std::endl;

    CBinStream *dec_data = new CBinStream();
    cipher->Decrypt(*enc_data, dec_data);
    std::cout << dec_data->ToString() << std::endl;

    delete stream;
    return 0;
}