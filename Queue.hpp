#include <iostream>
#include "Queue.h"

using namespace std;

void Queue::pushBack(T back)
{
  m_queue[m_lineLen] = back;
  m_lineLen++;
}
T Queue::popFront()
{
  T first = m_queue[0];
  for(int i=1;i<m_lineLen;i++)
  {
    m_queue[i-1] = m_queue[i];
  }
  return first;
}

