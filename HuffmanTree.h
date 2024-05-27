//
// Created by Guchen on 2023/11/22.
//

#ifndef HUFFMANTREE_HUFFMANTREE_H
#define HUFFMANTREE_HUFFMANTREE_H

#endif //HUFFMANTREE_HUFFMANTREE_H
#include "LinkList.h"
template<class WeightType>
struct HuffmanTreeNode
{
    WeightType weight;
    unsigned int parent,leftChild,rightChile;
    HuffmanTreeNode():parent(0),leftChild(0),rightChile(0){};
    explicit HuffmanTreeNode(const WeightType &w,int p=0,int lChild=0,int rChild=0);
};
template<class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(const WeightType &w, int p, int lChild, int rChild) {
    parent=p;
    leftChild=lChild;
    rightChile=rChild;
}
template<class CharType,class WeightType>
class HuffmanTree
{
protected:
    HuffmanTreeNode<WeightType>* nodes;
    CharType* leafChars;
    string * leafCharCodes;
    long long curPosition;
    long long num;
    void Select(int cur,int &r1,int &r2);
public:
    HuffmanTree(CharType ch[],WeightType w[],int n);
    string Encode(CharType ch);
    LinkList<CharType> Decode(const string& codeStr);
};
template<class CharType, class WeightType>
void HuffmanTree<CharType,WeightType>::Select(int cur, int &r1, int &r2) {
    int Min1=99999999;
    for(int i=1;i<=cur;i++)
    {
        if(nodes[i].parent==0)
        {
           if(Min1>nodes[i].weight)
           {
               Min1=nodes[i].weight;
               r1=i;
           }
        }
    }
    int Min2=99999999;
    for(int i=1;i<=cur;i++)
    {
        if(nodes[i].weight!=Min1&&nodes[i].parent==0)
        {
            if(Min2>nodes[i].weight)
            {
                Min2=nodes[i].weight;
                r2=i;
            }
        }
    }
}
template<class CharType, class WeightType>
HuffmanTree<CharType,WeightType>::HuffmanTree(CharType *ch, WeightType *w, int n) {
    num=n;
    int m=2*n-1;
    nodes=new HuffmanTreeNode<WeightType> [m+1];
    leafChars=new CharType[n+1];
    leafCharCodes=new string[n+1];
    int temPos;
    for(temPos=1;temPos<=n;temPos++)
    {
        nodes[temPos].weight=w[temPos-1];
        leafChars[temPos]=ch[temPos-1];
    }
    for(temPos=n+1;temPos<=m;temPos++)
    {
        int r1,r2;
        Select(temPos-1,r1,r2);
        nodes[r1].parent=nodes[r2].parent=temPos;
        nodes[temPos].leftChild=r1;
        nodes[temPos].rightChile=r2;
        nodes[temPos].weight=nodes[r1].weight+nodes[r2].weight;
    }
    for(temPos=1;temPos<=n;temPos++)
    {
        LinkList<char> charCode;
        for(unsigned int child=temPos,parent=nodes[child].parent;parent!=0;child=parent,parent=nodes[child].parent)
        {
            if (nodes[parent].leftChild == child)  charCode.Insert(1,'0');
            else charCode.Insert(1,'1');
        }
        for(int i=1;i<=charCode.Length();i++)
        {
            char e='\0';
            charCode.GetElem(i,e);
            leafCharCodes[temPos]+=e;
        }
    }
    curPosition=m;
}
template<class CharType,class WeightType>
string HuffmanTree<CharType,WeightType>::Encode(CharType ch) {
    int temPos;
    for(temPos=1;temPos<=num;temPos++)
    {
        if(leafChars[temPos]==ch) break;
    }
    if(temPos<=num)
    {
        return leafCharCodes[temPos];
    }
    else
    {
        cout<<"非法字符，无法编码！"<<endl;
        exit(1);
    }
}
template<class CharType,class WeightType>
LinkList<CharType> HuffmanTree<CharType,WeightType>::Decode(const string& codeStr) {
    LinkList<CharType>charList;
    for(char temPos : codeStr)
    {
        if(temPos=='0') curPosition=nodes[curPosition].leftChild;
        else curPosition=nodes[curPosition].rightChile;
        if(nodes[curPosition].leftChild==0&&nodes[curPosition].rightChile==0)
        {
            charList.Insert(charList.Length()+1,leafChars[curPosition]);
            curPosition=2*num-1;
        }
    }
    return charList;
}
