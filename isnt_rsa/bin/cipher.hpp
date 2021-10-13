#ifndef CIPHER_H
#define CIPHER_H

#include <cstdlib>
#include <ctime>
#include <array>

#include "binStream.hpp"

/*
    [op_num][seq_num][num_of_numbers][numbers] = [8bits(2 actually)][8bits][8bits][...bits]
*/
namespace bin {
    class CCipher {
        unsigned char m_opNum, m_stepNum, m_numOfNumbers;
        std::array<unsigned char, 4> m_steps;
        std::vector<unsigned char> *m_numbers;
        CBinStream *m_header;
        CBinStream *m_encStream;
        CBinStream *m_decStream;

    public:
        CCipher();
        ~CCipher();

        const CBinStream *Get();
        CBinStream *GetHeader();
        CBinStream *GetEnc();
        CBinStream *GetDec();
        int Random();
        int Random(int begin, int end);
        int Random(std::array<unsigned char, 4> numbers);

        bool Initialization(CBinStream header);
        CBinStream *Encrypt(CBinStream stream);
        void Encrypt(CBinStream stream, CBinStream *encStream);
        CBinStream *Decrypt(CBinStream stream);
        void Decrypt(CBinStream stream, CBinStream *decStream);

    };
};

#endif