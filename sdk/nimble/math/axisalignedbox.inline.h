//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

//////////////////////////////////////////////////////////////////////////
// AxisAlignedBox
//////////////////////////////////////////////////////////////////////////

//! center point
template <typename T, int N>
Vector<T, N> AxisAlignedBox<T, N>::getCenter() const{
    return Vector<T, N>::center(m_minimum, m_maximum);
}

//! min point
template <typename T, int N>
Vector<T, N> AxisAlignedBox<T, N>::getMinimum() const{return m_minimum;}
template <typename T, int N>
void AxisAlignedBox<T, N>::setMinimum(Vector<T, N> const& p1){m_minimum = p1;}

//! max point
template <typename T, int N>
Vector<T, N> AxisAlignedBox<T, N>::getMaximum() const{return m_maximum;}
template <typename T, int N>
void AxisAlignedBox<T, N>::setMaximum(Vector<T, N> const& p1){m_maximum = p1;}

//! dimension
template <typename T, int N>
float AxisAlignedBox<T, N>::getDimension(int i) const{
    assert(0 <= i && i < N);
    float dimension = nimble::math::abs(m_minimum[i] - m_maximum[i]);
    return dimension;
}

//! dimension
template <typename T, int N>
math::Vector<T, N> AxisAlignedBox<T, N>::getSize() const{
    return m_maximum - m_minimum;
}

//////////////////////////////////////////////////////////////////////////
// AxisAlignedBox2
//////////////////////////////////////////////////////////////////////////

//! a constructor
template <typename T>
AxisAlignedBox2<T>::AxisAlignedBox2(){
    this->setMinimum(Vector<T, 2>::zero());
    this->setMaximum(Vector<T, 2>::zero());
}

//! a copy constructor
template <typename T>
AxisAlignedBox2<T>::AxisAlignedBox2(AxisAlignedBox2<> const & aab){
    this->setMinimum(aab.getMinimum());
    this->setMaximum(aab.getMaximum());
}

//! a constructor
template <typename T>
AxisAlignedBox2<T>::AxisAlignedBox2(Vector<T, 2> const& min, Vector<T, 2> const& max){
    this->setMinimum(min);
    this->setMaximum(max);
}

//! a constructor
template <typename T>
AxisAlignedBox2<T>::AxisAlignedBox2(Vector<T, 2> const& center, T width, T height){
    Vector2<T> halfDistanceVector(width / 2, height / 2);
    this->setMinimum(center - halfDistanceVector);
    this->setMaximum(center + halfDistanceVector);
}

//! returns the width of the aab
template <typename T>
T AxisAlignedBox2<T>::getWidth() const{
    return AxisAlignedBox<T, 2>::getDimension(0);
}
//! returns the height of the aab
template <typename T>
T AxisAlignedBox2<T>::getHeight() const{
    return AxisAlignedBox<T, 2>::getDimension(1);
}

//! returns the corner point given an index
template <typename T>
Vector<T, 2> AxisAlignedBox2<T>::getCornerPoint(int index) const{
    // (our indexed corners)  (our axis)
    //   0--------1
    //   |        |
    //   |        |
    //   |        |
    //   3--------2
    //

    Vector<T, 2> point = AxisAlignedBox<T, 2>::getCenter();
    float halfWidth = getWidth() / 2.0f;
    float halfHeight = getHeight() / 2.0f;

    switch(index){
    case 0:
        point[0] -= halfWidth;
        point[1] += halfHeight;
        break;
    case 1:
        point[0] += halfWidth;
        point[1] += halfHeight;
        break;
    case 2:
        point[0] += halfWidth;
        point[1] -= halfHeight;
        break;
    case 3:
        point[0] -= halfWidth;
        point[1] -= halfHeight;
        break;
    };

    return point;
}

//! returns the identity aabox
template <typename T>
AxisAlignedBox2<T> AxisAlignedBox2<T>::identity(){
    AxisAlignedBox2<T> aabox;
    aabox.setMaximum(Vector2<T>(0.5f, 0.5f));
    aabox.setMinimum(Vector2<T>(-0.5f, -0.5f));
    return aabox;
}

//////////////////////////////////////////////////////////////////////////
// AxisAlignedBox3
//////////////////////////////////////////////////////////////////////////

//! a constructor
template <typename T>
AxisAlignedBox3<T>::AxisAlignedBox3(){
    this->setMinimum(Vector<T, 3>::zero());
    this->setMaximum(Vector<T, 3>::zero());
}

//! a copy constructor
template <typename T>
AxisAlignedBox3<T>::AxisAlignedBox3(AxisAlignedBox3<> const & aab){
    this->setMinimum(aab.getMinimum());
    this->setMaximum(aab.getMaximum());
}

//! a constructor
template <typename T>
AxisAlignedBox3<T>::AxisAlignedBox3(Vector<T, 3> const& min, Vector<T, 3> const& max){
    this->setMinimum(min);
    this->setMaximum(max);
}

//! a constructor
template <typename T>
AxisAlignedBox3<T>::AxisAlignedBox3(Vector<T, 3> const& center, T width, T height, T depth){
    Vector3<T> halfDistanceVector(width / 2, height / 2, depth / 2);
    this->setMinimum(center - halfDistanceVector);
    this->setMaximum(center + halfDistanceVector);
}

//! returns the width of the aab
template <typename T>
T AxisAlignedBox3<T>::getWidth() const{
    return AxisAlignedBox<T, 3>::getDimension(0);
}
//! returns the height of the aab
template <typename T>
T AxisAlignedBox3<T>::getHeight() const{
    return AxisAlignedBox<T, 3>::getDimension(1);
}
//! returns the depth of the aab
template <typename T>
T AxisAlignedBox3<T>::getDepth() const{
    return AxisAlignedBox<T, 3>::getDimension(2);
}

//! returns the corner point given an index
template <typename T>
Vector<T, 3> AxisAlignedBox3<T>::getCornerPoint(int index) const{
    // (our indexed corners)  (our axis)
    //       0--------1         
    //      /|       /|          y+
    //     / |      / |          |
    //    3--------2  |          |
    //    |  4-----|--5          +---x+
    //    | /      | /          /
    //    |/       |/          z+
    //    7--------6

    Vector<T, 3> point = AxisAlignedBox<T, 3>::getCenter();
    float halfWidth = getWidth() / 2.0f;
    float halfHeight = getHeight() / 2.0f;
    float halfDepth = getDepth() / 2.0f;

    switch(index){
    case 0:
        point[0] -= halfWidth;
        point[1] += halfHeight;
        point[2] -= halfDepth;
        break;
    case 1:
        point[0] += halfWidth;
        point[1] += halfHeight;
        point[2] -= halfDepth;
        break;
    case 2:
        point[0] += halfWidth;
        point[1] += halfHeight;
        point[2] += halfDepth;
        break;
    case 3:
        point[0] -= halfWidth;
        point[1] += halfHeight;
        point[2] += halfDepth;
        break;
    case 4:
        point[0] -= halfWidth;
        point[1] -= halfHeight;
        point[2] -= halfDepth;
        break;
    case 5:
        point[0] += halfWidth;
        point[1] -= halfHeight;
        point[2] -= halfDepth;
        break;
    case 6:
        point[0] += halfWidth;
        point[1] -= halfHeight;
        point[2] += halfDepth;
        break;
    case 7:
        point[0] -= halfWidth;
        point[1] -= halfHeight;
        point[2] += halfDepth;
        break;
    };

    return point;
}

//! returns the corner point given an index
template <typename T>
Plane3<> AxisAlignedBox3<T>::getFacePlane(int index) const{
    // (our indexed corners)  (our axis)
    //       0--------1         
    //      /|       /|          y+
    //     / |      / |          |
    //    3--------2  |          |
    //    |  4-----|--5          +---x+
    //    | /      | /          /
    //    |/       |/          z+
    //    7--------6

    // (our indexed planes)  (our axis)
    //       +--------+         
    //      /|  3    /|          y+
    //     / |      / |-- 2      |
    //    +--------+ -+ 4        |
    //  5-+  +-----|--+          +---x+
    //    | /  0   | /-- 1      /
    //    |/       |/          z+
    //    +--------+

    Vector<T, 3> p1, p2, p3;
    switch(index){
    case 0:
        p1 = getCornerPoint(3);
        p2 = getCornerPoint(7);
        p3 = getCornerPoint(6);
        break;
    case 1:
        p1 = getCornerPoint(5);
        p2 = getCornerPoint(6);
        p3 = getCornerPoint(7);
        break;
    case 2:
        p1 = getCornerPoint(1);
        p2 = getCornerPoint(5);
        p3 = getCornerPoint(4);
        break;
    case 3:
        p1 = getCornerPoint(0);
        p2 = getCornerPoint(3);
        p3 = getCornerPoint(2);
        break;
    case 4:
        p1 = getCornerPoint(2);
        p2 = getCornerPoint(6);
        p3 = getCornerPoint(5);
        break;
    case 5:
        p1 = getCornerPoint(0);
        p2 = getCornerPoint(4);
        p3 = getCornerPoint(7);
        break;
    };

    // find our plane normal
    Vector3<> v1 = p1 - p2;
    Vector3<> v2 = p3 - p2;
    Vector3<> normal = v1 ^ v2;
    normal.normalize();

    // find our distance
    Vector3<> pointVector = p1;
    float D = -1.0f * normal.dot(pointVector);

    // calculate our plane
    Plane3<> plane(normal, D);
    return plane;
}

//! returns the identity aabox
template <typename T>
AxisAlignedBox3<T> AxisAlignedBox3<T>::identity(){
    AxisAlignedBox3<T> aabox;
    aabox.setMaximum(Vector3<T>(0.5f, 0.5f, 0.5f));
    aabox.setMinimum(Vector3<T>(-0.5f, -0.5f, -0.5f));
    return aabox;
}

//////////////////////////////////////////////////////////////////////////

