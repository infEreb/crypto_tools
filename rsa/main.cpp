#include <iostream>
#include <fstream>

#include "primeNums.hpp"
#include "prime.hpp"

using namespace prime;

int main() {
    const std::string f_path = "primes.txt";
    
    CPrimeNums *primes = new CPrimeNums();

    //
    // ADD NUMBERS FROM THE FILE
    //
    std::ifstream if_primes(f_path);
    primes->Load(if_primes);

    //
    // PRINT NUMBERS
    //
    std::cout << primes->ToString() << std::endl;

    //primes->CalculateNext();
    unsigned __int64 prime = primes->CalculateBound(170);
    unsigned __int64 target_prime = primes->CalculateNext(1000000000000);

    std::ofstream of_file(f_path);
    //primes->Save(of_file);

    std::cout << primes->ToString() << std::endl;
    std::cout << target_prime << std::endl;

    delete primes;

    return 0;
}