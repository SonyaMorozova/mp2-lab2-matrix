// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz <= 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Invalid vector lenght value");
    pMem = new T[sz](); // {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      if (sz <= 0 || sz > MAX_VECTOR_SIZE)
          throw out_of_range("Invalid vector lenght value");
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      this->pMem = new T[sz];
      for (int i = 0; i < sz; i++) pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->pMem = v.pMem;
      v.pMem = nullptr;
      this->sz = v.sz;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
      sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      this->sz = v.sz;
          this->pMem = new T[sz];
          for (int i = 0; i < sz; i++) pMem[i] = v.pMem[i];
          return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;
      this->pMem = v.pMem;
      v.pMem = nullptr;
      this->sz = v.sz;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) throw ("Invalid index value");
      return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) throw ("Invalid index value");
      return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return 0;
      for (int i = 0; i < sz; i++) if (pMem[i] != v.pMem[i]) return 0;
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] + val;
      return res;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] - val;
      return res;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "Different vector lengths";
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] + v.pMem[i];
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw "Different vector lengths";
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] - v.pMem[i];
      return res;
  }
  T operator*(const TDynamicVector& v) 
  {
      if (sz != v.sz) throw "Different vector lengths";
      T res=0;
      for (int i = 0; i < sz; i++) res = res + pMem[i]*v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem; // столбец, в котором хранятся строки матрицы
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s <= 0 || s > MAX_MATRIX_SIZE)
          throw out_of_range("Invalid matrix size value");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz); 
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  // индексация с контролем
  T& at(size_t col, size_t row) {
      if (col < 0 || row < 0 || col >= this->sz || row >= this->sz) throw ("Invalid index value");
      return this->pMem[row][col];
  }

  const T& at(size_t col, size_t row) const {
      if (col < 0 || row < 0 || col >= this->sz || row >= this->sz) throw ("Invalid index value");
      return this->pMem[row][col];
  }
 // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return 0;
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i]) return 0;
      }
      return 1;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] + val;
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) // v - cтолбец 
  {
      if (sz != v.sz) throw "Different vector and matrix size";
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) res[i] = pMem[i] * v;
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Different matrix size";
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] + m.pMem[i];
      return res;

  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Different matrix size";
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) res.pMem[i] = pMem[i] - m.pMem[i];
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw "Different matrix size";
      TDynamicMatrix res(sz);
      for (int k = 0; k < sz; k++) {
          for (int i = 0; i < sz; i++) {
              T result = 0;
              for (int j = 0; j < sz; j++) {
                  result = result + pMem[i][j] * m.pMem[j][k];
              }
              res.pMem[i][k] = result;
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) istr >> v.pMem[i];
      return istr; 
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)  ostr << v.pMem[i];
      return ostr;
  }
};

#endif
