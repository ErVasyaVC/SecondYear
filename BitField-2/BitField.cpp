#include "BitField.h"
#include <cstring>

size_t BitField::GetMemIndex(size_t n) const
{
    if (n >= _sizeBit)
        throw "GetMemInde:: Error!! Bit out of range";
    return n / (8 * sizeof(uint16_t));
}
uint16_t BitField::GetMask(size_t n) const
{
    return 1 << (n % (8 * sizeof(uint16_t)));
}

BitField::BitField(size_t len)
{
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;
}

void BitField::SizeT(size_t t)
{
    std::string buffer;
    do
    {
        buffer += char('0' + t % 2);
        t = t / 2;
    } while (t > 0);

    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;

    BitField B = BitField(buffer.size());

    // if (_memSize != tmp._memSize)
    // {
    //     delete[] _mem;

    //     _memSize = tmp._memSize;
    //     _mem = new uint16_t[_memSize];
    // }
    // _sizeBit = tmp._sizeBit;
    // for (size_t i = 0; i < _memSize; ++i)
    //     _mem[i] = tmp._mem[i];
    // return *this;




    for (size_t i = 0; i < buffer.size(); i++)
    {
        if (buffer[i] == '1')
        {
            B.SetBit(i);
        }
    }
    *this = B;
}

BitField::BitField(const BitField &tmp)
{
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];

    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
}

BitField &BitField::operator=(const BitField &tmp)
{
    if (_memSize != tmp._memSize)
    {
        delete[] _mem;

        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    _sizeBit = tmp._sizeBit;
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}

size_t BitField::GetLength() const
{
    return _sizeBit;
}
void BitField::SetBit(size_t n)
{
    _mem[GetMemIndex(n)] |= GetMask(n);
}
void BitField::ClrBit(size_t n)
{

    _mem[GetMemIndex(n)] &= ~GetMask(n);
}
uint8_t BitField::GetBit(size_t n) const
{
    return (_mem[GetMemIndex(n)] & GetMask(n)) != 0;
}
BitField BitField::operator|(const BitField &tmp)
{
    BitField B(*this);
    for (size_t i = 0; i < _memSize; i++)
    {
        B._mem[i] = _mem[i] | tmp._mem[i];
    }

    return B;
}

BitField BitField::operator&(const BitField &tmp)
{
    BitField B(*this);
    if (GetLength() > tmp.GetLength())
    {
        for (size_t i = 0; i < (tmp._memSize); i++)
        {
            B._mem[i] |= tmp._mem[i];
        }
    }
    else
    {
        BitField B(tmp);
        for (size_t i = 0; i < (_memSize); i++)
        {
            B._mem[i] |= tmp._mem[i];
        }
    }

    return B;
}
BitField BitField::operator^(const BitField &tmp)
{
    BitField B(*this);
    for (size_t i = 0; i < _memSize; i++)
    {
        B._mem[i] ^= tmp._mem[i];
    }
    return B;
}
bool BitField::operator==(const BitField &tmp) const
{
    for (size_t i = 0; i < _memSize; i++)
    {
        if (_mem[i] != tmp._mem[i])
        {
            return false;
        }
    }
    return true;
}
BitField BitField::operator~()
{
    BitField B = BitField(*this);
    for (size_t i = 0; i < _sizeBit; i++)
    {
        if (GetBit(i))
        {
            B.ClrBit(i);
        }
        else
        {
            B.SetBit(i);
        }
    }
    return B;
}

BitField::~BitField()
{
    delete[] _mem;
}

ostream& operator<<(ostream &os, const BitField& tmp){
    std::string out;
    for (int i = tmp.GetLength() - 1; i > -1; i--)
    {
        if (tmp.GetBit(i)) out += '1';
        else out += '0';
    }
    return os << out;
}