#include "primeNums.hpp"

using namespace prime;

CPrimeNums::CPrimeNums() {
    m_primeNums = new std::list<CPrime *>();
}

CPrimeNums::~CPrimeNums() {
    Clear();
}

std::list<CPrime *> *CPrimeNums::Get() {                                    // returns list of prime nums
    return m_primeNums;
}

bool CPrimeNums::isTimeToStopCalcNext(unsigned __int64 num) {               // stops calculate next prime num
    bool primeFlag = true;
    for(auto prime : *m_primeNums) {
        unsigned __int64 n_prime = prime->Get();
        if (num % n_prime != 0 && primeFlag) {      // if is prime with that num
            primeFlag = true;
            if (n_prime*n_prime > num || num == n_prime) {
                break;
            }
        } else {
            primeFlag = false;                      // if we have found at least one
            break;
        }
    }
    return primeFlag;
}

bool CPrimeNums::isTimeToStopCalcBound(unsigned __int64 num) {              // stops calculate bound prime num
    if(num > m_boundNum) {
        return true;
    } else {
        return false;
    }
}

unsigned __int64 CPrimeNums::CalculateNext() {                              // calculates next prime num by list
    unsigned __int64 last_num = Get()->back()->Get() + 1;
    while(!isTimeToStopCalcNext(last_num)) {
        last_num++;
    }
    m_primeNums->push_back(new CPrime(last_num));

    return last_num;
}

unsigned __int64 CPrimeNums::CalculateNext(unsigned __int64 number) {
    unsigned __int64 last_num = number;
    unsigned __int64 iter = m_primeNums->back()->Get();
    while(iter*iter < number) {
        std::cout << iter << std::endl; /////////////////////////////////////////////
        iter = CalculateNext();
    }
    while(!isTimeToStopCalcNext(last_num)) {
        last_num++;
    }

    return last_num;
}

unsigned __int64 CPrimeNums::CalculateBound(unsigned __int64 bound) {
    m_boundNum = bound;
    unsigned __int64 iter = m_primeNums->back()->Get();
    while(iter <= bound) {
        if(!isTimeToStopCalcBound(iter)) {
            iter = CalculateNext();
        }
    }
    m_primeNums->pop_back();
    return m_primeNums->back()->Get();
}

bool CPrimeNums::Load(std::ifstream &file) {
    if(file.is_open()) {
        Clear();
        std::string line;
        while(std::getline(file, line)) {
            m_primeNums->push_back(
                new CPrime(std::stol(line)));
        }

        if(m_primeNums->empty()) {
            m_primeNums->push_back(new CPrime(2));
            CalculateNext();
            CalculateNext();
        }
        return false;
    }
    else {
        return true;
    }
}

bool CPrimeNums::Save(std::ofstream &file) {
    if(file.is_open()) {
        if(m_primeNums->empty()) {
            m_primeNums->push_back(new CPrime(2));
        }
        for(auto prime : *m_primeNums) {
            if(prime->Get() != m_primeNums->back()->Get()) {
                file << prime->Get() << std::endl;
            } else {
                file << prime->Get();
            }
        }
        return false;
    }
    else {
        return true;
    }
}

void CPrimeNums::Clear() {
    for(auto prime : *m_primeNums) {
        delete prime;
    }
    delete m_primeNums;
}

std::string CPrimeNums::ToString() {
    std::stringstream ss;
    ss << "{ ";
    for (auto primeNum : *m_primeNums)
    {
        ss << primeNum->ToString();
        if (primeNum->Get() != (m_primeNums->back())->Get()) {
            ss << ", ";
        } else {
            ss << " }";
        }
    }
    return ss.str();
}