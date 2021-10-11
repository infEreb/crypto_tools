#ifndef PRIME_NUMS_H
#define PRIME_NUMS_H

#include <string>
#include <sstream>
#include <list>
#include <iostream>
#include <fstream>

#include "prime.hpp"

namespace prime {

    class CPrimeNums {

        unsigned __int64 m_boundNum;                            // 1 < "list_of_primes" <= m_N
        std::list<CPrime *> *m_primeNums;

        bool isTimeToStopCalcNext(unsigned __int64 N);
        bool isTimeToStopCalcBound(unsigned __int64 N);

    public:
        CPrimeNums();
        ~CPrimeNums();

        std::list<CPrime *> *Get();

        bool Save(std::ofstream &file);
        bool Load(std::ifstream &file);

        void Clear();

        unsigned __int64 CalculateBound(unsigned __int64 boundNum);         // Calculates all prime nums that <= boundNum
        unsigned __int64 CalculateNext();                                   // Calculates next prime num by list
        unsigned __int64 CalculateNext(unsigned __int64 number);            // Calculates next prime num by num and 
                                                                            // return this without add to list

        std::string ToString();
    };


};

#endif