#include <iostream>
#include <fstream>

#include "./primes/primeNums.hpp"
#include "./primes/prime.hpp"

using namespace prime;

int main() {
    const std::string f_path = "primes.dat";
    
    CPrimeNums *primes = new CPrimeNums();

    // ADD NUMBERS FROM THE FILE
    std::ifstream if_file(f_path);
    primes->Load(if_file);


    // PRINT NUMBERS
    std::cout << primes->ToString() << std::endl;

    // some calculates
    unsigned __int64 prime = primes->CalculateBound(5);
    unsigned __int64 target_prime = primes->CalculateNext(2000000000000000);


    // Save prime nums and close file
    std::ofstream of_file(f_path);
    primes->Save(of_file);
    if_file.close();
    of_file.close();

    std::cout << primes->ToString() << std::endl;
    std::cout << target_prime << std::endl;

    delete primes;

    return 0;
}