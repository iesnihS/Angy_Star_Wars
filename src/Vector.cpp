#include "Vector.hpp"

using namespace engine;

#pragma region Vector2

template<typename T>
engine::Vector2<T>::Vector2(T _x, T _y) : x(_x), y(_y) {}

template<typename T>
Vector2<T>::Vector2(T _v) : x(_v), y(_v) {}

template<typename T>
Vector2<T>::Vector2() : x(0), y(0) {}
#pragma endregion

#pragma region Vector3

template<typename T>
engine::Vector3<T>::Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z){}

template<typename T>
Vector3<T>::Vector3(T _v) : x(_v), y(_v), z(0) {}

template<typename T>
Vector3<T>::Vector3() : x(0), y(0), z(0) {}
#pragma endregion
