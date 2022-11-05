#include<iostream>
#include "lib.h"
using namespace std;


int main(){
    bool set=true;
    char opt;
    while(set){
        func_prin();
        cout<<"Quieres repetir la operacion? s/n"<<endl;
        cin>>opt;
        if (opt=='s')
        {
            set=true;
        }else{
            set=false;
        }
        system("cls");
    }
    
    return 0;
    
}
