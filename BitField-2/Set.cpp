#include "Set.h"
#include <cmath>     


Set::Set(size_t mp) : _bitField(mp) {
    _maxPower = mp;
}
Set::Set(const Set &s) : _bitField(s._bitField), _maxPower(s.GetMaxPower()){} 
Set::Set(const BitField &bf) : _bitField(bf), _maxPower(bf.GetLength()){}

size_t Set::GetMaxPower() const{
    return _maxPower;
}    
void Set::InsElem(const uint64_t Elem){
    _bitField.SetBit(Elem);
}
void Set::DelElem(const uint64_t Elem){
    _bitField.ClrBit(Elem);
}
bool Set::IsMember(const uint64_t Elem) const{
    return _bitField.GetBit(Elem);
}


bool Set::operator== (const Set &s) const{
    return s._bitField == _bitField;
}
bool Set::operator!= (const Set &s) const{
    return (s._bitField == _bitField) == 0;
}
Set& Set::operator=(const Set &s){
    _bitField = s._bitField;
    _maxPower = s._maxPower;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){
    Set s(*this);
    s.InsElem(Elem);
    return s;
}
                                  
Set Set::operator- (const uint64_t Elem){
    Set s(*this);
    s.DelElem(Elem);
    return s;
}
                                   
Set Set::operator+ (const Set &s){
    Set ss(max(s._maxPower, _maxPower));
    ss._bitField = _bitField | s._bitField;
    return ss;
}
Set Set::operator* (const Set &s){
    Set ss(_bitField & s._bitField);
    return ss;
}
Set Set::operator~ (){
    Set ss(_maxPower);
    ss._bitField = ~_bitField;
    return ss;
}
std::vector<uint64_t> Set::GetPrimary(){
    Set s(*this);
    
    size_t max_power = GetMaxPower();
    size_t sqrtn = static_cast<size_t> (sqrt (max_power)) + 1;
    for (size_t i = 2; i < sqrtn; i ++){
        if (i != 0){
            for (size_t j = i + i; j < max_power; j += i){
                s._bitField.ClrBit(j);
                }
            }
    }
    std::vector<uint64_t> ss;
    ss.push_back(1);
    for(size_t i = 2; i < max_power; i++){
        if(s._bitField.GetBit(i)){
            ss.push_back(i);
        }
    }
    return ss;
}