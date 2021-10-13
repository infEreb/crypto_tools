#include "cipher.hpp"

/*
    [op_num][seq_num][num_of_numbers][numbers] = [8bits(2 actually)][8bits][8bits][...bits]
*/
using namespace bin;

CCipher::CCipher() {
    srand(time(NULL));
    m_opNum = 0;
    m_stepNum = 0;
    m_steps = {1, 2, 4, 8};
    m_numOfNumbers = 0;
    m_numbers = new std::vector<unsigned char>();
    m_header = new CBinStream();
    m_encStream = new CBinStream();
    m_decStream = new CBinStream();
    *m_header << m_opNum << m_stepNum << m_numOfNumbers;
}
CCipher::~CCipher() {
    delete m_numbers;
    delete m_header;
    delete m_encStream;
    delete m_decStream;
}

const CBinStream *CCipher::Get() {
    return m_header;
}
CBinStream *CCipher::GetEnc() {
    return m_encStream;
}
CBinStream *CCipher::GetDec() {
    return m_decStream;
}
CBinStream *CCipher::GetHeader() {
    return m_header;
}
int CCipher::Random() {
    return rand();
}
int CCipher::Random(int begin, int end) {
    if (begin >= end) {
        return begin;
    } else {
        return begin + (rand() % (end - begin + 1));  
    }
}
int CCipher::Random(std::array<unsigned char, 4> numbers) {
    return numbers[Random(0,numbers.size()-1)];
}


bool CCipher::Initialization(CBinStream header) {

    return true;
}

CBinStream *CCipher::Encrypt(CBinStream stream) {
    m_encStream->Clear();
    m_header->Clear();
    unsigned char opNum=Random(1, 2), stepNum=Random(m_steps),      // define subkeys
        numOfNums=Random(3, 255);
    *m_header << opNum << stepNum << numOfNums;                     // add subkeys to the header (key)
    for(int i = 0; i < numOfNums; i++) {                            // generate random numbers for the key
        m_numbers->push_back(Random(0, 255));
        *m_header << m_numbers->back();                             // and add them
    }

    *m_encStream << *m_header << stream;

    // REWRITE !!!!!!!!!!!!!!!!!! TEMP SOLUTION
    m_opNum=opNum, m_stepNum=stepNum, m_numOfNumbers=numOfNums;
    int stepIter = 1;
    int numIndex = 0;
    for(auto i = 0; i < m_encStream->Size(); i++) {
        if(m_opNum == 1) {
            if(stepIter / m_stepNum == 0) {
                m_encStream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                m_encStream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter=1;
                numIndex++;
            }
        }
        if(m_opNum == 2) {
            if(stepIter / m_stepNum == 0) {
                m_encStream->GetUnsafe()->at(i) = ~(m_encStream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                m_encStream->GetUnsafe()->at(i) = ~(m_encStream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter=1;
                numIndex++;
            }
        }
    }
    return m_encStream;
}
void CCipher::Encrypt(CBinStream stream, CBinStream *enc_stream) {
    enc_stream->Clear();
    m_header->Clear();
    unsigned char opNum=Random(1, 2), stepNum=Random(m_steps),      // define subkeys
        numOfNums=Random(3, 255);
    *m_header << opNum << stepNum << numOfNums;                     // add subkeys to the header (key)
    for(int i = 0; i < numOfNums; i++) {                            // generate random numbers for the key
        m_numbers->push_back(Random(0, 255));
        *m_header << m_numbers->back();                             // and add them
    }

    *enc_stream << *m_header << stream;

    // REWRITE !!!!!!!!!!!!!!!!!! TEMP SOLUTION
    m_opNum=opNum, m_stepNum=stepNum, m_numOfNumbers=numOfNums;
    int stepIter = 1;
    int numIndex = 0;
    for(auto i = 0; i < enc_stream->Size(); i++) {
        if(m_opNum == 1) {
            if(stepIter / m_stepNum == 0) {
                enc_stream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                enc_stream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter=1;
                numIndex++;
            }
        }
        if(m_opNum == 2) {
            if(stepIter / m_stepNum == 0) {
                enc_stream->GetUnsafe()->at(i) = ~(enc_stream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                enc_stream->GetUnsafe()->at(i) = ~(enc_stream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter=1;
                numIndex++;
            }
        }
    }
    return;
}

CBinStream *CCipher::Decrypt(CBinStream stream) {
    m_decStream->Clear();
    *m_decStream << stream;

    int stepIter = 1;
    int numIndex = 0;
    for(auto i = 0; i < m_decStream->Size(); i++) {
        if(m_opNum == 1) {
            if(stepIter / m_stepNum == 0) {
                m_decStream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                m_decStream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter=1;
                numIndex++;
            }
        }
        if(m_opNum == 2) {
            if(stepIter / m_stepNum == 0) {
                m_decStream->GetUnsafe()->at(i) = ~(m_decStream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                m_decStream->GetUnsafe()->at(i) = ~(m_decStream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter=1;
                numIndex++;
            }
        }
    }

    return m_decStream;
}
void CCipher::Decrypt(CBinStream stream, CBinStream *dec_stream) {
    dec_stream->Clear();
    *dec_stream << stream;

    int stepIter = 1;
    int numIndex = 0;
    for(auto i = 0; i < dec_stream->Size(); i++) {
        if(m_opNum == 1) {
            if(stepIter / m_stepNum == 0) {
                dec_stream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                dec_stream->GetUnsafe()->at(i) ^= m_numbers->at(numIndex);
                stepIter=1;
                numIndex++;
            }
        }
        if(m_opNum == 2) {
            if(stepIter / m_stepNum == 0) {
                dec_stream->GetUnsafe()->at(i) = ~(dec_stream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter++;
            } else {
                if(numIndex == m_numbers->size()) {
                    numIndex = 0;
                }
                dec_stream->GetUnsafe()->at(i) = ~(dec_stream->GetUnsafe()->at(i) ^ m_numbers->at(numIndex));
                stepIter=1;
                numIndex++;
            }
        }
    }

    return;
}


