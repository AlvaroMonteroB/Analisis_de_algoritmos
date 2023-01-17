#include<iostream>
#include<stdio.h>
#include"build_tree.h"
using namespace std;

int main(){
    int opt;
    cout<<"1.-Comprimir mensaje"<<endl<<"2.-Decodificar mensaje"<<endl;
    cin>>opt;
    string str,aux;
    switch (opt)
    {
    case 1:
        
        cout<<"Digite el mensaje a codificar"<<endl;
        getline(cin,aux);
        getline(cin,str);
        Create_tree(str);
        cout<<endl;
        break;
    case 2:
        break;
    
    default:
        break;
    }
    return 0;
}