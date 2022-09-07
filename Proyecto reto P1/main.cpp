#include<iostream>
#include "lib.h"
using namespace std;


int main(){
    bool set=true;
    char opt;
    while(set){
        
        cout<<"Quieres repetir la operacion? s/n";
        cin>>opt;
        if (opt=='s')
        {
            set=true;
        }else{
            set=false;
        }
        
    }
    return 0;
}
