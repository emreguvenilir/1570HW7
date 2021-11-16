#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
  private:
    static int m_lineLen;
    T m_queue[100]; 
  public:
    //Pre: queue is valid
    //Post: return type T
    //Desc: Returns the first object in the queue
    T peek() const{return m_queue[0];}
    //Pre: None
    //Post: return type T
    //Desc: takes off front objecgt and moves up the queue
    T popFront();
    //Description: adds the paramter object to the back of the  queue
    //Pre: takes the new obj of type T 
    //Post: None
    void pushBack(T back);
};



#endif