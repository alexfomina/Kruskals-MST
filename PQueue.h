#ifndef P_QUEUE_H
#define P_QUEUE_H
#include "DblList.h"

template <typename T>
class PQueue{
    public:
        PQueue(bool isMin); //min queue or not
        virtual ~PQueue();
        void add(T data);
        T remove();
        int size();
        bool isEmpty();
        T peek();
    private:
        bool isMinQ;
        DblList<T>* m_list;
};

template <typename T>
PQueue<T>::PQueue(bool isMin){
    isMinQ = isMin;
    m_list = new DblList<T>();
}

template <typename T>
PQueue<T>::~PQueue(){}

template <typename T>
bool PQueue<T>::isEmpty(){
    return m_list->isEmpty();
}

template <typename T>
int PQueue<T>::size(){
    return m_list->getSize();
}

template <typename T>
T PQueue<T>::remove(){
    if(isMinQ){
        return m_list->removeFront(); //smallest always at front
    } 
    else{
        return m_list->removeBack(); //largest always at back
    }
}

template <typename T>
void PQueue<T>::add(T d) {
    if (isEmpty()) {
        // Just add if the list is empty
        m_list->addFront(d);
    } else {
        // Create a new node with the provided data
        ListNode<T>* newNode = new ListNode<T>(d);
        int currIdx = 0;
        ListNode<T>* currNode = m_list->m_front;

        // Find the right place to add based on the comparison function
        while (currNode != nullptr && currNode->m_data->getWeight() <= d->getWeight()) {
            ++currIdx;
            currNode = currNode->m_next;
        }

        // Add the new node to the list
        m_list->add(currIdx, newNode);
    }
}
// template <typename T>
// void PQueue<T>::add(T d){
//     if(isEmpty())
//     { //well, that's easy. Just add.
//         m_list->addFront(d);
//     }
//     else
//     {
//         ListNode<T>* newNode = new ListNode<T>(d);
//         int currIdx = 0;
//         ListNode<T>* currNode = m_list->m_front;
//         while(currNode != NULL && currNode->m_data->getWeight() < d->getWeight()){ //from front, find the right
//         //place to add. The < operator better be defined on the class.
//             ++currIdx;
//             currNode = currNode->m_next;
//         }
//         m_list->add(currIdx,newNode); //this is a hack because it starts over looking from
//     //front. But doesn't change linear runtime. Just 2x as slow in practice.
//     }
// }
template <typename T>
T PQueue<T>::peek()
{
    return m_list->get(0);
}
#endif