#include <iostream>
#include "value.h"

template <typename T>
class Pile
{
private:
  int nbElemMax;
  int nbElemCur;
  T* data;

public:

  typedef T* iterator;

  Pile(int nbElemMax)
    :nbElemMax(nbElemMax),
     nbElemCur(0),
     data(new T[nbElemMax])
  {
  }

  ~Pile()
  {
    delete[] data;
  }

  void push (const T& toadd)
  {
    if (nbElemCur < nbElemMax)
      {
	data[nbElemCur] = toadd;
	nbElemCur++;
      }
    else
      {
	std::cerr<<"Pile::pop"<<std::endl;
      }
  }

  //invalides the iterator on the last element
  void pop()
  {
    if (nbElemCur > 0)
      nbElemCur --;
    else
      std::cerr<<"Pile::pop"<<std::endl;
  }

  T& top()
  {
    if (nbElemCur != 0)
	return data[nbElemCur - 1];
    else
      {
	std::cerr<<"Pile::top"<<std::endl;
	return data[0];
      }
  }

  iterator begin()
  {
    return data;
  }

  iterator end()
  {
    return data+nbElemCur;
  }

  bool empty()
  {
    return nbElemCur == 0;
  }
};

int main ()
{
  int sum=0;
  Pile<int> stack(VAL+1);
  stack.push(VAL);
  while (! stack.empty())
    {
      sum++;
      int c = stack.top();
      stack.pop();
      if (c != 0)
	{
	  stack.push(c-1);
	  stack.push(c-1);      
	}
    }

  return 0;
}
