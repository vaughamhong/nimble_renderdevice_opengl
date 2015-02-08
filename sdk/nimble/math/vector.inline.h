//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////
// Vector
//////////////////////////////////////////////////////////////////////////

//! Constructor
template <typename T, int N>
Vector<T, N>::Vector(){
}
//! copy constructor
template <typename T, int N>
Vector<T, N>::Vector(Vector<T, N-1> const& v1){
    this->assignment(v1);
}
//! copy constructor
template <typename T, int N>
Vector<T, N>::Vector(Vector<T, N> const& v1){
    this->assignment(v1);
}
//! copy constructor
template <typename T, int N>
Vector<T, N>::Vector(Vector<T, N+1> const& v1){
    this->assignment(v1);
}
//! Destructor
template <typename T, int N>
Vector<T, N>::~Vector(){
}

//////////////////////////////////////////////////////////////////////////

//! data access
template <typename T, int N>
T Vector<T, N>::operator[](int i) const{
    core::assert_error(0 <= i && i < N, "Invalid array index");
    return m_data.m_array[i];
}
//! data access
template <typename T, int N>
T& Vector<T, N>::operator[](int i){
    core::assert_error(0 <= i && i < N, "Invalid array index");
    return m_data.m_array[i];
}
//! data access
template <typename T, int N>
T* Vector<T, N>::getData(){
    return m_data.m_array;
}
//! data access
template <typename T, int N>
const T* Vector<T, N>::getConstData() const{
    return m_data.m_array;
}

//////////////////////////////////////////////////////////////////////////

//! returns the dimensions of the vector
template <typename T, int N>
int Vector<T, N>::getDimension() const{
    return N;
}

//////////////////////////////////////////////////////////////////////////

template <typename T, int N>
bool Vector<T, N>::operator==(Vector<T, N> const& v1) const{
    return this->equal(v1);
}
template <typename T, int N>
bool Vector<T, N>::operator!=(Vector<T, N> const& v1) const{
    return this->notEqual(v1);
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator=(Vector<T, N-1> const& v1){
    this->assignment(v1); 
    return Vector<T, N>(*this);
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator=(Vector<T, N> const& v1){
    this->assignment(v1); 
    return Vector<T, N>(*this);
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator=(Vector<T, N+1> const& v1){
    this->assignment(v1); 
    return Vector<T, N>(*this);
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator+(Vector<T, N> const& v1) const{
    Vector<T, N> retVect(*this); 
    retVect.add(v1); 
    return retVect;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator+=(Vector<T, N> const& v1){
    this->add(v1); 
    return *this;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator-(Vector<T, N> const& v1) const{
    Vector<T, N> retVect(*this); 
    retVect.subtract(v1); 
    return retVect;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator-=(Vector<T, N> const& v1){
    this->subtract(v1); 
    return *this;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator*(T scaler) const{
    Vector<T, N> v1(*this); 
    v1.multiply(scaler); 
    return v1;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator*=(T scaler){
    this->multiply(scaler); 
    return *this;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator/(T scaler) const{
    Vector<T, N> v1(*this); 
    v1.divide(scaler); 
    return v1;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator/=(T scaler){
    this->divide(scaler); 
    return *this;
}

template <typename T, int N>
Vector<T, N> Vector<T, N>::operator^(Vector<T, N> const& v1) const{
    Vector<T, N> retVect; 
    retVect.cross(*this, v1); 
    return retVect;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::operator^=(Vector<T, N> const& v1){
    Vector<T, N> v2(*this); 
    cross(v2, v1); 
    return *this;
}

//////////////////////////////////////////////////////////////////////////

// assignment
template <typename T, int N>
void Vector<T, N>::assignment(Vector<T, N-1> const& v1){
    vecZero<T, N>(getData()); 
    vecCopy<T, N-1>(getData(), v1.getConstData());
}
template <typename T, int N>
void Vector<T, N>::assignment(Vector<T, N> const& v1){
    vecCopy<T, N>(getData(), v1.getConstData());
}
template <typename T, int N>
void Vector<T, N>::assignment(Vector<T, N+1> const& v1){
    vecCopy<T, N>(getData(), v1.getConstData());
}

// comparison
template <typename T, int N>
bool Vector<T, N>::equal(Vector<T, N> const& v1) const{
    return vecEq<T, N>(getConstData(), v1.getConstData());
}
template <typename T, int N>
bool Vector<T, N>::notEqual(Vector<T, N> const& v1) const{
    return !equal(v1);
}

// arithmetic
template <typename T, int N>
void Vector<T, N>::add(Vector<T, N> const& v1){
    vecAdd<T, N>(getData(), getConstData(), v1.getConstData());
}
template <typename T, int N>
void Vector<T, N>::subtract(Vector<T, N> const& v1){
    vecSub<T, N>(getData(), getConstData(), v1.getConstData());
}
template <typename T, int N>
void Vector<T, N>::multiply(T scaler){
    vecMul<T, N>(getData(), scaler);
}
template <typename T, int N>
void Vector<T, N>::divide(T scaler){
    vecDiv<T, N>(getData(), scaler);
}

// misc
template <typename T, int N>
float Vector<T, N>::dot(Vector<T, N> const& v1) const{
    float retValue; 
    vecDot<T, N>(&retValue, getConstData(), v1.getConstData()); 
    return retValue;
}
template <typename T, int N>
float Vector<T, N>::dot(T const v[N]) const{
    float retValue;
    vecDot<T, N>(&retValue, getConstData(), v);
    return retValue;
}
template <typename T, int N>
void Vector<T, N>::cross(Vector<T, N> const& v1, Vector<T, N> const& v2){
    vecCrs<T, N>(getData(), v1.getConstData(), v2.getConstData());
}
template <typename T, int N>
float Vector<T, N>::length() const{
    float retValue; 
    vecLen<T, N>(&retValue, getConstData()); 
    return retValue;
}
template <typename T, int N>
void Vector<T, N>::normalize(){
    vecNor<T, N>(getData());
}

//////////////////////////////////////////////////////////////////////////

template <typename T, int N>
Vector<T, N> Vector<T, N>::zero(){
    Vector<T, N> retPnt; 
    vecZero<T, N>(retPnt.getData()); 
    return retPnt;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::center(Vector<T, N> const& v1, Vector<T, N> const& v2){
    Vector<T, N> retPnt;
    vecCenter<T, N>(retPnt.getData(), v1.getConstData(), v2.getConstData());
    return retPnt;
}
template <typename T, int N>
Vector<T, N> Vector<T, N>::unit(){
    Vector<T, N> retPnt; 
    vecUnit<T, N>(retPnt.getData()); 
    return retPnt;
}

//////////////////////////////////////////////////////////////////////////
