#include <iostream>
#include "value.h"

template <typename T, int nbElemMax>
class Pile
{
private:
  int nbElemCur;
  T data[nbElemMax];

public:

  typedef T* iterator;

  Pile()
    :nbElemCur(0)
  {
  }

  ~Pile()
  {
  }
  
  void push (const T& toadd)
  {
    data[nbElemCur] = toadd;
    nbElemCur++;
  }

  //invalides the iterator on the last element
  void pop()
  {
    nbElemCur --;
  }

  T& top()
  {
    return data[nbElemCur - 1];
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
  Pile<int,VAL+1> stack;
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
