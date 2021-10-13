#include "prime.hpp"

using namespace prime;

CPrime::CPrime() {
    m_primeNumber = 2;
};
CPrime::CPrime(unsigned __int64 primeNum) {
    m_primeNumber = primeNum;
}

CPrime::~CPrime() {}

unsigned __int64 CPrime::Get() {
    return m_primeNumber;
}

std::string CPrime::ToString() {
    return std::to_string(m_primeNumber);
}
