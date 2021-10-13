#ifndef BIN_STREAM_H
#define BIN_STREAM_H

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace bin {
    class CBinStream {
        std::vector<unsigned char> *m_stream;

    public:
        CBinStream();
        CBinStream(unsigned int size);                  // number of bytes
        ~CBinStream();

        const std::vector<unsigned char> *Get();
        std::vector<unsigned char> *GetUnsafe();
        unsigned int Size();
        void Clear();
        void Invert(int begin_index, int end_index);
        static char InvertBit(char ch_);
        static int InvertByte(int int_);

        

        CBinStream& operator >> (int &int_);
        CBinStream& operator >> (short &sh_);
        CBinStream& operator >> (char &ch_);
        CBinStream& operator >> (unsigned char &ch_);
        CBinStream& operator >> (std::vector<int> &int_vec);
        CBinStream& operator >> (std::vector<short> &sh_vec);
        CBinStream& operator >> (std::vector<char> &ch_vec);
        CBinStream& operator >> (std::vector<unsigned char> &ch_vec);
        CBinStream& operator >> (std::string &string);
        CBinStream& operator >> (std::ofstream &file_out);

        CBinStream& operator << (const CBinStream &stream);
        CBinStream& operator << (const int &int_);
        CBinStream& operator << (const short &sh_);
        CBinStream& operator << (const char &ch_);
        CBinStream& operator << (const unsigned char &ch_);
        CBinStream& operator << (const std::vector<int> &int_vec);
        CBinStream& operator << (const std::vector<short> &sh_vec);
        CBinStream& operator << (const std::vector<char> &ch_vec);
        CBinStream& operator << (const std::vector<unsigned char> &ch_vec);
        CBinStream& operator << (const std::string &string);
        CBinStream& operator << (std::ifstream &file_in);

        const std::string ToString();

    };
};

#endif