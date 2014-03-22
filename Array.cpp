/***************************************
Class: CS251
Assignment Number: 2
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef ARRAY_CPP
#define ARRAY_CPP

#include <sys/types.h>

#include <algorithm>
#include <sstream>

#include "Array.h"

#if !defined (__INLINE__)
#define INLINE
#include "Array.inl"
#endif /* __INLINE__ */

template <typename T>
Array<T>::Array (size_t size)
  // @@ Please use nullptr
  : max_size_(size), cur_size_(size), array_(new T[size]), default_value_(nullptr){}


template <typename T>
Array<T>::Array (size_t size,  const T &default_value)
  : max_size_(size), cur_size_(size), array_(new T[size]), default_value_(new T(default_value))
{
  std::fill(array_.get(), array_.get() + size, default_value);

}


// The copy constructor (performs initialization).

template <typename T>
Array<T>::Array (const Array<T> &s)
  // @@ Please beware the associativity & prescidence of the ternary operator!
  // Please see https://piazza.com/class/hq5nadmq8h438r?cid=130
  : max_size_(s.max_size_), cur_size_(s.cur_size_), array_(new T[s.max_size_]), default_value_( (s.default_value_.get() == nullptr) ? nullptr : new T(*s.default_value_))
{
  std::copy(s.array_.get(), s.array_.get() + s.cur_size_, array_.get());
}



template <typename T> void
Array<T>::resize (size_t new_size)
{
  if(new_size < cur_size_)
    cur_size_ = new_size;
  else
    {
      if(new_size <= max_size_)
	{
     
	 if(default_value_.get() != nullptr)
	   {
	     std::fill(array_.get()+cur_size_, array_.get()+new_size, *default_value_);
	   }
         cur_size_ = new_size;

	}
      else
	{
         scoped_array<T> temp(new T[new_size]);
         std::copy(array_.get(), array_.get()+cur_size_, temp.get());
         if(default_value_.get() != nullptr )
           {
            std::fill(temp.get()+cur_size_, temp.get()+new_size, *default_value_);
           }
            array_.swap(temp);
            max_size_ = new_size;
            cur_size_ = new_size;
	 }
    }
}


template <typename T> void
Array<T>::swap (Array<T> &new_array)
{
  std::swap(max_size_, new_array.max_size_);
  std::swap(cur_size_, new_array.cur_size_);
  std::swap(default_value_, new_array.default_value_);
  new_array.array_.swap(array_);
}

// Assignment operator (performs assignment).

template <typename T> Array<T> &
Array<T>::operator= (const Array<T> &s)
{
  if (this != &s)
    {
      Array temp(s);
      swap(temp);
    }
  return *this;
}

// Clean up the array (e.g., delete dynamically allocated memory).

template <typename T>
Array<T>::~Array (void)
{}

// = Set/get methods.

// Set an item in the array at location index.

template <typename T> void
Array<T>::set (const T &new_item, size_t index)
{
  // @@ You can restructure this code so that this->array_[index] = new_item; only appears once!
  if(!in_range(index))
    {
     resize(index + 1);
    }

   array_[index] = new_item;

 }

// Get an item in the array at location index.

template <typename T> void
Array<T>::get (T &item, size_t index) const
{
  if(!in_range(index))
    throw std::out_of_range("out of range");
  item = array_[index];

}

// Compare this array with <s> for equality.

template <typename T> bool
Array<T>::operator== (const Array<T> &s) const
{
  if(s.cur_size_ != cur_size_)
    return false;

  // don't check the self-comparision because it is not necessary
  else
    return std::equal(array_.get(), array_.get() + cur_size_, s.array_.get());

}

// Compare this array with <s> for inequality.

template <typename T> bool
Array<T>::operator!= (const Array<T> &s) const
{
  return !(*this == s);
}

template <typename T>
Array_Iterator<T>::Array_Iterator (Array<T> &array, size_t pos)
  :array_(array), pos_(pos) {}

template <typename T>
Const_Array_Iterator<T>::Const_Array_Iterator (const Array<T> &array, size_t pos)
  :array_(array), pos_(pos) {}

#endif /* ARRAY_CPP */
