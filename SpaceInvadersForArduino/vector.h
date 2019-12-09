#pragma once
template <typename T> class vector
{
  private:
    T *_array;
    int8_t _arraySize;
  public:
    void push_back(T data)
    {
      T *_result = new T[++this->_arraySize];

      for (int8_t index = 0; index < this->_arraySize; index++)
      {
        if (index != this->_arraySize - 1)
        {
          _result[index] = this->_array[index];
        }
        else
        {
          _result[index] = data;
          break;
        }
      }
      delete[] this->_array;
      this->_array = _result;
    }


    int8_t size()
    {
      return this->_arraySize;
    }



    T popIndex(int8_t& index)
    {
      T *_result = new T[--this->_arraySize];

      T resItem;

      int8_t resIndex = 0;

      for (int8_t index2 = 0; index2 < this->_arraySize + 1; index2++)
      {
        T item = this->_array[index2];

        if (index == index2)
        {
          resItem = item;
          continue;
        }
        _result[resIndex++] = this->_array[index2];
      }
      delete[] this->_array;
      this->_array = _result;
      return resItem;
    }
    T& operator [](int8_t index) const
    {
      return this->_array[index];
    }

    vector()
    {
      this->_arraySize = 0;
      this->_array = new T[this->_arraySize];
    }
};
