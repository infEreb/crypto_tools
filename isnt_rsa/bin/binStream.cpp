#include "binStream.hpp"

using namespace bin;

CBinStream::CBinStream() {
    m_stream = new std::vector<unsigned char>();
}
CBinStream::CBinStream(unsigned int size) {
    CBinStream();
    m_stream->resize(size);
}
CBinStream::~CBinStream() {
    delete m_stream;
}

const std::vector<unsigned char> *CBinStream::Get() {
    return m_stream;
}
std::vector<unsigned char> *CBinStream::GetUnsafe() {
    return m_stream;
}
unsigned int CBinStream::Size() {
    return m_stream->size();
}
void CBinStream::Clear() {
    int size = Size();
    for(int i = 0; i < size; i++) {
        m_stream->pop_back();
    }
}
char CBinStream::InvertBit(char ch_) {
    char res = 0;
    for(int i = 0; i < sizeof(ch_)-1; i++) {        // iteration for all (except last) bites
        res |= (ch_ & 1);                           // change 1st bit for res
        ch_ >>= 1;                                  // shift to right
        res <<= 1;                                  // res shifts to left
    }
    return res;
}
int CBinStream::InvertByte(int int_) {
    int res = 0;
    char ch;
    for(int i = 0; i < sizeof(int_); i++) {         // byte number iteration
        ch = (int_ & (0xFF << i*8)) >> i*8;         // create mask of n byte and get one
        res = (res | ch);                           // change 1st byte by mask
        if (i != sizeof(int_)-1) {                  // and if it's not last byte
            res <<= i*8;                            // shift to the left side this (1st) byte
        }
    }

    return res;
}
void CBinStream::Invert(int beginIndex, int endIndex) {
    int area = endIndex - beginIndex + 1;
    for(int i = 0; i < area/2; i++) {
        std::iter_swap(m_stream->begin() + beginIndex + i, m_stream->begin() + endIndex - i);
    }
}
char CBinStream::GetBit(char byte, char bit_index) {
            if(bit_index >= 0 && bit_index <= 7) {
                return byte & (1 << bit_index);
            }
            return -1;
        }

bool CBinStream::Read(std::ifstream &file, size_t byteCount) {
    if(file.is_open() && file) {
        Clear();
        file.seekg(0, file.end);
        int len = file.tellg();
        file.seekg(0, file.beg);

        if(len <= byteCount) {
            byteCount = len;
        }
        char *str_c = new char[byteCount+1];
        size_t readed;
        file.read(str_c, byteCount+1);
        str_c[byteCount] = '\0';
        readed = file.gcount();

        if(!readed) {
            return true;
        }

        *this << str_c;
        delete[] str_c;

    } else {
        return true;
    }
    return false;
}

CBinStream& CBinStream::operator<< (const CBinStream &stream) {
    for(auto byte : *stream.m_stream) {
        *this << byte;
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const int &int_) {
    int nTemp;
    unsigned char part;
    for(int i = sizeof(int_) - 1; i >= 0; i--) {
        nTemp = int_;
        part = (nTemp & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
        m_stream->push_back(part);
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const short &sh_) {
    short nTemp;
    unsigned char part;
    for(int i = sizeof(sh_) - 1; i >= 0; i--) {
        nTemp = sh_;
        part = (nTemp & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
        m_stream->push_back(part);
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const char &ch_) {
    char nTemp;
    unsigned char part;
    m_stream->push_back(ch_);
    // for(int i = sizeof(ch_) - 1; i >= 0; i--) {
    //     nTemp = ch_;
    //     part = (nTemp & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
    //     m_stream->push_back(part);
    // }
    return *this;
}
CBinStream& CBinStream::operator<< (const unsigned char &ch_) {
    char nTemp;
    unsigned char part;
    m_stream->push_back(ch_);
    // for(int i = sizeof(ch_) - 1; i >= 0; i--) {
    //     nTemp = ch_;
    //     part = (nTemp & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
    //     m_stream->push_back(part);
    // }
    return *this;
}
CBinStream& CBinStream::operator<< (const std::vector<int> &int_vec) {
    int nTemp;
    unsigned char part;
    for(auto el : int_vec) {
        for(int i = sizeof(el) - 1; i >= 0; i--) {
            nTemp = el;
            part = (el & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
            m_stream->push_back(part);
        }
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const std::vector<short> &sh_vec) {
    short nTemp;
    unsigned char part;
    for(auto el : sh_vec) {
        for(int i = sizeof(el) - 1; i >= 0; i--) {
            nTemp = el;
            part = (el & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
            m_stream->push_back(part);
        }
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const std::vector<char> &ch_vec) {
    char nTemp;
    unsigned char part;
    for(auto el : ch_vec) {
        for(int i = sizeof(el) - 1; i >= 0; i--) {
            nTemp = el;
            part = (el & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
            m_stream->push_back(part);
        }
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const std::vector<unsigned char> &ch_vec) {
    char nTemp;
    unsigned char part;
    for(auto el : ch_vec) {
        for(int i = sizeof(el) - 1; i >= 0; i--) {
            nTemp = el;
            part = (el & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
            m_stream->push_back(part);
        }
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const char *str_) {
    while(*str_) {
        *this << *str_;
        str_++;
    }
    return *this;
}
CBinStream& CBinStream::operator<< (const std::string &string) {
    char nTemp;
    unsigned char part;
    for(auto el : string) {
        m_stream->push_back(el);
        // for(int i = sizeof(el) - 1; i >= 0; i--) {
        //     nTemp = el;
        //     part = (el & (0xFF << i*8)) >> i*8;              // 11111111 00000000 00000000 00000000
        //     m_stream->push_back(part);
        // }
    }
    return *this;
}
CBinStream& CBinStream::operator<< (std::ifstream &file_in) {
    if(file_in.is_open()) {
        std::string str;
        while(std::getline(file_in, str)) {
            *this << str;
            *this << '\n';
        }
    }
    return *this;
}


CBinStream& CBinStream::operator>> (int &int_) {
    int nTemp = 0x0;
    char ch;
    if(Size() >= sizeof(int_)) {
        Invert(Size()-sizeof(int_), Size()-1);
        for (int i = 0; i < sizeof(int_); i++) {
            *this >> ch;
            nTemp |= ch;
            if (i != sizeof(int_) - 1) {
                nTemp <<= 8;
            }
        }
        int_ = nTemp;
    }

    return *this;
}
CBinStream& CBinStream::operator>> (short &sh_) {
    int nTemp = 0x0;
    char ch;
    if(Size() >= sizeof(sh_)) {
        Invert(Size()-sizeof(sh_), Size()-1);
        for (int i = 0; i < sizeof(sh_); i++) {
            *this >> ch;
            nTemp |= ch;
            if (i != sizeof(sh_) - 1) {
                nTemp <<= 8;
            }
        }
        sh_ = nTemp;
    }
    return *this;
}
CBinStream& CBinStream::operator>> (char &ch_) {
    if(Size() >= sizeof(ch_)) {
        ch_ = m_stream->back();
        m_stream->pop_back();
    }
    return *this;
}
CBinStream& CBinStream::operator>> (unsigned char &ch_) {
    if(Size() >= sizeof(ch_)) {
        ch_ = m_stream->back();
        m_stream->pop_back();
    }
    return *this;
}
CBinStream& CBinStream::operator>> (std::vector<int> &int_vec) {
    return *this;
}
CBinStream& CBinStream::operator>> (std::vector<short> &sh_vec) {
    return *this;
}
CBinStream& CBinStream::operator>> (std::vector<char> &ch_vec) {
    return *this;
}
CBinStream& CBinStream::operator>> (std::string &string) {
    if (Size() != 0) {
        for(auto ch : *m_stream) {
            string.push_back(ch);
        }
        //Clear();
    }
    return *this;
}
CBinStream& CBinStream::operator>> (std::ofstream &file_out) {
    std::string str;
    *this >> str;
    file_out << str;
    return *this;
}
CBinStream& CBinStream::operator>> (std::ostream &stream_out) {
    
    return *this;
}

const std::string CBinStream::ToString() {
    std::string str("{ ");
    
    if(Size() == 1) {
        char ch = (*m_stream)[0];
        if(ch == 0xA) {
            str.append("\\n");
        } else if(ch >= 0x20) {
            str.push_back(ch);
        }
    } else {
        *this >> str;
    }
    
    str.append(" }");
    
    return str;
}
const std::string CBinStream::ToHexString() {
    std::stringstream ss;
    ss << "{ ";
    for(auto byte : *m_stream) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
        //ss << byte << " ";
    }
    ss << "}";
    return ss.str();
}
