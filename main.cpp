#include "HuffmanTree.h"
struct BufferType
{
    char ch;
    unsigned int bits;
};
class HuffmanCompress
{
protected:
    HuffmanTree<char,unsigned long >* pHuffmanTree;
    FILE *infp, *outfp;
    BufferType buf;
    void Write(unsigned int bit);
    void WriteToOutfp();
public:
    HuffmanCompress()= default;
    void Compress();
    void Decompress();
};
void HuffmanCompress::Write(unsigned int bit) {
    buf.bits++;
    buf.ch=(buf.ch<<1)|bit;
    if(buf.bits==8)
    {
        fputc(buf.ch,outfp);
        buf.bits=0;
        buf.ch='\0';
    }
}
void HuffmanCompress::WriteToOutfp() {
    unsigned int len=buf.bits;
    if(len>0)
    {
        for(unsigned int temPos=0;temPos<8-len;temPos++)
            Write(0);
    }
}
void HuffmanCompress::Compress() {
    char infName[256],outfName[256];
    cout<<"请输入源文件名:";
    cin>>infName;
    if((infp=fopen(infName,"rb"))== nullptr)
    {
        cout<<"打开源文件失败!"<<endl;
        exit(1);
    }
    fgetc(infp);
    if(feof(infp))
    {
        cout<<"空源文件!"<<endl;
        exit(2);
    }
    cout<<"请输入目标文件:";
    cin>>outfName;
    if((outfp=fopen(outfName,"wb"))== nullptr)
    {
        cout<<"打开目标文件失败!"<<endl;
        exit(3);
    }
    cout<<"正在处理，请稍候......"<<endl;
    const unsigned long n=256;
    char ch[n];
    unsigned long w[n];
    unsigned long size=0;
    int temPos;
    char cha;
    for(temPos=0;temPos<n;temPos++)
    {
        ch[temPos]=(char)temPos;
        w[temPos]=0;
    }
    rewind(infp);
    cha=fgetc(infp);
    while (!feof(infp))
    {
        w[(unsigned char )cha]++;
        size++;
        cha=fgetc(infp);
    }
    if(pHuffmanTree!= nullptr) delete []pHuffmanTree;
    pHuffmanTree=new HuffmanTree<char,unsigned long >(ch,w,n);
    rewind(outfp);
    fwrite(&size,sizeof(unsigned long ),1,outfp);
    for(temPos=0;temPos<n;temPos++)
    {
        fwrite(&w[temPos],sizeof(unsigned long ),1,outfp);
    }
    buf.bits=0;
    buf.ch=0;
    rewind(infp);
    cha=fgetc(infp);
    while (!feof(infp))
    {
        string temStr=pHuffmanTree->Encode(cha);
        for(temPos=0;temPos<temStr.length();temPos++)
        {
            if(temStr[temPos]=='0') Write(0);
            else Write(1);
        }
        cha=fgetc(infp);
    }
    WriteToOutfp();
    fclose(infp);
    fclose(outfp);
    cout<<"处理结束."<<endl;
}
void HuffmanCompress::Decompress() {
    char infName[256],outfName[256];
    cout<<"请输入压缩文件名:";
    cin>>infName;
    if((infp=fopen(infName,"rb"))== nullptr)
    {
        cout<<"打开压缩文件失败!"<<endl;
        exit(4);
    }
    fgetc(infp);
    if(feof(infp))
    {
        cout<<"压缩文件为空!"<<endl;
        exit(5);
    }
    cout<<"请输入目标文件名:";
    cin>>outfName;
    if((outfp=fopen(outfName,"wb"))== nullptr)
    {
        cout<<"打开目标文件失败!"<<endl;
        exit(6);
    }
    cout<<"正在处理，请稍后......"<<endl;
    const unsigned long n=256;
    char ch[n];
    unsigned long w[n];
    unsigned long size=0;
    int temPos;
    char cha;
    rewind(infp);
    fread(&size,sizeof(unsigned long ),1,infp);
    for(temPos=0;temPos<n;temPos++)
    {
        ch[temPos]=(char)temPos;
        fread(&w[temPos],sizeof(unsigned long ),1,infp);
    }
    if(pHuffmanTree!= nullptr) delete []pHuffmanTree;
    pHuffmanTree=new HuffmanTree<char,unsigned long >(ch,w,n);
    unsigned long len=0;
    cha=fgetc(infp);
    while (!feof(infp))
    {
        string temStr="";
        unsigned char  c=(unsigned char )cha;
        for(temPos=0;temPos<8;temPos++)
        {
            if(c<128) temStr+="0";
            else temStr+="1";
            c<<=1;
        }
        LinkList<char> lkText=pHuffmanTree->Decode(temStr);
        string curStr;
        for(int i=1;i<=lkText.Length();i++)
        {
            char e='\0';
            lkText.GetElem(i,e);
            curStr+=e;
        }
        for(temPos=1;temPos<=curStr.length();temPos++)
        {
            len++;
            fputc(curStr[temPos-1],outfp);
            if(len==size) break;
        }
        if(len==size) break;
        cha=fgetc(infp);
    }
    fclose(infp);
    fclose(outfp);
    cout<<"处理结束."<<endl;
}
int main()
{
    HuffmanCompress Task{};
    int operate;
    cout<<"输入操作:"<<endl<<"1.压缩文件"<<endl<<"2.解压文件"<<endl;
    cin>>operate;
    if(operate==1)
        Task.Compress();
    else
        Task.Decompress();
    return 0;
//    Task.Compress();
//    Task.Decompress();
}
/*
D:/Code/.cpp/HuffmanTree/task/t1.txt
D:/Code/.cpp/HuffmanTree/task/target1.txt
D:/Code/.cpp/HuffmanTree/task/Decode1.txt
*/
