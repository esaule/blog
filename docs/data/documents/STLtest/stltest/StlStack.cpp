#include <iostream>
#include <stack>
#include "value.h"

int main ()
{
  int sum=0;
  std::stack<int> stack;
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
