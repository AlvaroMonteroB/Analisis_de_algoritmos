#include<iostream>
#include<queue>
#include<string>
#include<unordered_map>
using namespace std;

typedef struct Tree{
        Tree *izq;
        Tree *der;
        char _sim;
        int freq;
}Nodo;



Nodo* getnode(char simb,int freq, Tree *izq,Tree *der){
    Nodo *raiz=new Nodo();
    raiz->der=der;
    raiz->freq=freq;
    raiz->izq=izq;
    raiz->_sim=simb;
    return raiz;

}

//objeto de comparacion
struct comp{
    bool operator()(Nodo *i,Nodo* d){
        return i->freq > d->freq;
    }
    
};


void encode(Nodo *raiz, string str, unordered_map<char,string>&codigoHuffman){
    if (raiz==nullptr)
    {
        return;
    }
    if (!(raiz->izq&&raiz->der))
    {
        codigoHuffman[raiz->_sim]=str;
    }
    encode(raiz->izq,str+'0',codigoHuffman);
    encode(raiz->der,str+'1',codigoHuffman);
    
    
}

void decode(Nodo *raiz, int &index,string str){
        if (!raiz)
        {
            return;
        }
        if (!(raiz->izq&& raiz->der))
        {
            cout<<raiz->_sim;
        }
        index ++;
        if (str[index]=='0')
        {
            decode(raiz->izq,index,str);
        }else{
            decode(raiz->der,index,str);
        }
       
}


void Create_tree(string text){
        unordered_map<char, int> frequency;
        for (char simbolo:text)
        {
            frequency[simbolo]++;
        }
        priority_queue<Nodo*,vector<Nodo*>, comp> pq;
        for (auto pair:frequency)
        {
            pq.push(getnode(pair.first,pair.second,nullptr,nullptr));
        }
        while (pq.size()!=1)
        {
            Nodo *izq=pq.top();pq.pop();
            Nodo *der=pq.top();pq.pop();
            int sum=izq->freq+der->freq;
            pq.push(getnode('0',sum,izq,der));
        }
        Nodo *raiz=pq.top();
        unordered_map<char,string> codigoHuffman;
        encode(raiz,"",codigoHuffman);

        
        
}