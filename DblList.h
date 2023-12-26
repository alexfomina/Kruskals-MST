#ifndef DBL_LIST_H
#define DBL_LIST_H
#include "ListNode.h"

template <typename T>
class DblList{
    public:
        DblList();
        virtual ~DblList();
        void addFront(T data);
        void addBack(T data);
        void add(int pos, T data);
        void add(int pos, ListNode<T>* data);
        void addBack(ListNode<T>* data);
        void addFront(ListNode<T>* data);
        T removeFront();
        T removeBack();
        T remove(int pos);
        bool isEmpty();
        int getSize();
        T get(int pos);
        template <typename S>
        friend class PQueue;
    private:
        ListNode<T>* m_front;
        ListNode<T>* m_back;
        int m_size;
};

template <typename T>
DblList<T>::DblList(){
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template <typename T>
DblList<T>::~DblList(){
    //to do - free memory - loop through and list and delete all nodes
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template <typename T>
    int DblList<T>::getSize(){ //constant - O(1)
    return m_size;
}

template <typename T>
bool DblList<T>::isEmpty(){ //constant - O(1)
    return (m_size == 0);
}

template <typename T>
void DblList<T>::addFront(T data){ //Constant
    ListNode<T>* newNode = new ListNode<T>(data);
    if(!isEmpty()){
        m_front->m_prev = newNode;
        newNode->m_next = m_front;
    }else{ //the list is empty
        m_back = newNode;
    }
    m_front = newNode;
    ++m_size;
}

template <typename T>
void DblList<T>::addBack(T data){ //Constant
    ListNode<T>* newNode = new ListNode<T>(data);
    if(!isEmpty()){
        m_back->m_next = newNode;
        newNode->m_prev = m_back;
    }else{ //list is empty
        m_front = newNode;
    }
    m_back = newNode;
    ++m_size;
}

template <typename T>
void DblList<T>::add(int pos, ListNode<T>* data) { //linear
    if (isEmpty()) {
        addFront(data);
    } else if (pos == 0) {
        addFront(data);
    } else if (pos >= m_size) {
        addBack(data);
    } else {
        ListNode<T>* current = m_front;
        int cPos = 0;
        while (cPos != pos) {
            current = current->m_next;
            ++cPos;
        }
        // Insert the new node before the current node
        data->m_prev = current->m_prev;
        data->m_next = current;
        current->m_prev->m_next = data;
        current->m_prev = data;
        ++m_size;
    }
}
// template<typename T>
// void DblList<T>::add(int pos, T data){ //linear
//     if(isEmpty()){
//         addFront(data);
//     }
//     else if(pos == 0){
//         addFront(data);
//     }
//     else if(pos >= m_size){
//         addBack(data);
//     }
//     else{
//         ListNode<T>* current = m_front;
//         int cPos = 0;
//         while(cPos != pos){
//         current = current->m_next;
//         ++cPos;
//         }
//         ListNode<T>* newNode = new ListNode<T>(data);
//         current->m_prev->m_next = newNode;
//         newNode->m_prev = current->m_prev;
//         current->m_prev = newNode;
//         newNode->m_next = current;
//         ++m_size;
//     }
// }

template<typename T>
T DblList<T>::removeFront(){ //constant
    T data;
    data = m_front->m_data;
    //make sure not empty
    if (getSize() == 0)
    {
        return NULL;
    }
    else{
        if(m_size == 1){
            delete m_front;
            m_front = NULL;
            m_back = NULL;
        }
        else{
            ListNode<T>* currFront = m_front;
            m_front = m_front->m_next;
            m_front->m_prev = NULL;
            delete currFront;
        }
        --m_size;
        return data;
    }
}

template<typename T>
T DblList<T>::removeBack(){ //constant
    T data;
    data = m_back->m_data;
    if (getSize() ==0)
    {
        return NULL;
    }
    //make sure not empty
    else
    {
        if(m_size == 1){
            delete m_back; //could also use m_front, since m_back and m_front point to
            //the same place
            m_front = NULL;
            m_back = NULL;
        }
        else{
            ListNode<T>* currBack = m_back;
            m_back = m_back->m_prev;
            m_back->m_next = NULL;
            delete currBack;
        }
        --m_size;
        return data;
    }
}

template<typename T>
T DblList<T>::remove(int pos){ //linear
//make sure not empty
    if(getSize() == 0)
    {
        return NULL;
    }
    else
    {
        T data;
        if(pos == 0){
            data = removeFront();
        }
        else if(pos >= m_size){
            data = removeBack();
        }
        else{
            ListNode<T>* current = m_front;
            int cPos = 0;
            while(cPos != pos){
            current = current->m_next;
            ++cPos;
            }
            data = current->m_data;
            current->m_prev->m_next = current->m_next;
            current->m_next->m_prev = current->m_prev;
            delete current;
            --m_size;
            }
        return data;
    }
}

template<typename T>
T DblList<T>::get(int pos){ //linear
    //todo - make sure position is in range
    if (pos >= getSize())
    {
        return NULL;
    }
    else
    {
        ListNode<T>* current = m_front;
        int cPos = 0;
        while(cPos != pos){
            current = current->m_next;
            ++cPos;
        }
        return current->m_data;
    }
}
template <typename T>
void DblList<T>::addFront(ListNode<T>* data) { // Constant
    if (!isEmpty()) {
        data->m_prev = nullptr;
        data->m_next = m_front;
        m_front->m_prev = data;
    } else { // the list is empty
        m_back = data;
        data->m_prev = nullptr;
    }
    m_front = data;
    ++m_size;
}

template <typename T>
void DblList<T>::addBack(ListNode<T>* data) { // Constant
    if (!isEmpty()) {
        data->m_next = nullptr;
        data->m_prev = m_back;
        m_back->m_next = data;
    } else { // list is empty
        m_front = data;
        data->m_next = nullptr;
    }
    m_back = data;
    ++m_size;
}
#endif