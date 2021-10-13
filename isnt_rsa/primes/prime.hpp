#ifndef PRIME_HPP
#define PRIME_HPP

#include <math.h>
#include <string>


namespace prime {

    class CPrime {

        unsigned __int64 m_primeNumber;


    public:
        CPrime();
        CPrime(unsigned __int64 N);                     // N is max number of area where we need to find the prime number
                                                        // (1 < prime <= N)
        ~CPrime();

        unsigned __int64 Get();

        std::string ToString();


    };
};

#endif