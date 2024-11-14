#include "Set.h"


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
    Set ss(max(s._maxPower, _maxPower));
    ss._bitField = _bitField & s._bitField;
    return ss;
}
Set Set::operator~ (){
    Set ss(_maxPower);
    ss._bitField = ~_bitField;
    return ss;
}
std::vector<uint64_t> Set::GetPrimary(){
    return std::vector<uint64_t>();
}