//
// Created by Guchen on 2023/11/20.
//

#ifndef HUFFMANTREE_LINKLIST_H
#define HUFFMANTREE_LINKLIST_H

#endif //HUFFMANTREE_LINKLIST_H
#include <bits/stdc++.h>
using namespace std;
template<class ElemType>
struct Node
{
    ElemType data;
    Node<ElemType>* next;
    Node();
    explicit Node(const ElemType &e,Node<ElemType> *link= nullptr);
};
template<class ElemType>
Node<ElemType>::Node() {
    next= nullptr;
}
template<class ElemType>
Node<ElemType>::Node(const ElemType &e, Node<ElemType> *link) {
    data=e;
    next=link;
}
template<class ElemType>
class LinkList
{
protected:
    Node<ElemType> *head;
    Node<ElemType> * GetElemPtr(int position) const;
public:
    LinkList();
    virtual ~LinkList();
    int Length() const;
    bool Empty() const;
    void Clear();
    void Traverse(void(*visit)(const ElemType &)) const;
    bool GetElem(int position,ElemType &e);
    bool SetElem(int position,const ElemType &e);
    bool Delete(int position,ElemType &e);
    bool Delete(int position);
    bool Insert(int position,const ElemType &e);
};
template<class ElemType>
Node<ElemType> * LinkList<ElemType>::GetElemPtr(int position) const {
    Node<ElemType> * temPtr=head;
    int temPos=0;
    while (temPtr!= nullptr&&temPos<position)
    {
        temPtr=temPtr->next;
        temPos++;
    }
    if(temPtr!= nullptr&&temPos==position)
    {
        return temPtr;
    }
    else
    {
        return nullptr;
    }
}
template<class ElemType>
LinkList<ElemType>::LinkList() {
    head=new Node<ElemType>;
}
template<class ElemType>
LinkList<ElemType>::~LinkList(){
    Clear();
    delete head;
}
template<class ElemType>
int LinkList<ElemType>::Length() const{
    int count=0;
    for(Node<ElemType> * temPtr = head->next;temPtr!= nullptr;temPtr=temPtr->next)
    {
        count++;
    }
    return count;
}
template<class ElemType>
bool LinkList<ElemType>::Empty() const {
    return head->next== nullptr;
}
template<class ElemType>
void LinkList<ElemType>::Clear() {
    while(!Empty())
    {
        Delete(1);
    }
}
template<class ElemType>
void LinkList<ElemType>::Traverse(void (*visit)(const ElemType &)) const {
    for(Node<ElemType> *temPtr=head->next;temPtr!= nullptr;temPtr= temPtr->next)
    {
        (*visit)(temPtr->data);
    }
}
template<class ElemType>
bool LinkList<ElemType>::GetElem(int position, ElemType &e) {
    if(position<1||position>Length())
        return false;
    else
    {
        Node<ElemType> * temPtr= GetElemPtr(position);
        e= temPtr->data;
        return true;
    }
}
template<class ElemType>
bool LinkList<ElemType> ::SetElem(int position, const ElemType &e) {
    if(position<1||position>Length())
        return false;
    else
    {
        Node<ElemType> temPtr= GetElemPtr(position);
        temPtr->data=e;
        return true;
    }
}
template<class ElemType>
bool LinkList<ElemType>::Insert(int position, const ElemType &e) {
    if(position<1||position>Length()+1)
        return false;
    else
    {
        Node<ElemType> *temPtr= GetElemPtr(position-1);
        Node<ElemType> * newPtr=new Node<ElemType>(e,temPtr->next);
        temPtr->next=newPtr;
        return true;
    }
}
template<class ElemType>
bool LinkList<ElemType> ::Delete(int position,ElemType &e) {
    if(position<1||position>Length())
        return false;
    else
    {
        Node<ElemType> * temPtr= GetElemPtr(position-1);
        Node<ElemType>* nextPtr= temPtr->next;
        temPtr->next=nextPtr->next;
        e=nextPtr->data;
        delete nextPtr;
        return true;
    }
}
template<class ElemType>
bool LinkList<ElemType> ::Delete(int position) {
    if(position<1||position>Length())
        return false;
    else
    {
        Node<ElemType> * temPtr= GetElemPtr(position-1);
        Node<ElemType>* nextPtr= temPtr->next;
        temPtr->next=nextPtr->next;
        delete nextPtr;
        return true;
    }
}
template<class ElemType>
void MergeList(const LinkList<ElemType> &la,const LinkList<ElemType> &lb,LinkList<ElemType> &lc)
{
    ElemType aElem,bElem;
    int aLength=la.Length(),bLength=lb.Length();
    int aPos=1,bPos=1;
    lc.Clear();
    while (aPos<=aLength&&bPos<=bLength)
    {
        la.GetElem(aPos,aElem);
        lb.GetElem(bPos,bElem);
        if(aElem<bElem)
        {
            lc.Insert(lc.Length()+1,aElem);
            aPos++;
        }
        else
        {
            lc.Insert(lc.Length()+1,bElem);
            bPos++;
        }
    }
    while (aPos<=aLength)
    {
        la.GetElem(aPos,aElem);
        lc.Insert(lc.Length()+1,aElem);
        aPos++;
    }
    while (bPos<=bLength)
    {
        lb.GetElem(bPos,bElem);
        lc.Insert(lc.Length()+1,bElem);
        bPos++;
    }
}
template<class ElemType>
void Reverse(LinkList<ElemType> &la)
{
    ElemType aElem,bElem;
    for(int pos=1; pos<=la.Length()/2;pos++)
    {
        la.GetElem(pos,aElem);
        la.GetElem(la.Length()-pos+1,bElem);
        la.SetElem(pos,bElem);
        la.SetElem(la.Length()-pos+1,aElem);
    }
}

