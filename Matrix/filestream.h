#include<iostream>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<string>
#include<string.h>
using namespace std;
void clear(char *&aux);
vector<char*> stream(vector<char*>cant,uint32_t *&cols,uint32_t *&rows,string file_name);
vector<float> mat(vector<char*> conv);




vector<char> stream(vector<char>cant,uint32_t *&cols,uint32_t *&rows,string file_name){

    char str[5];
    int counter=0;
    char s;
    bool col,row;
    vector<char>vect;
    char *aux=(char*)calloc(sizeof(char),2);
    if (!aux)
    {   
        cout<<"couldnt allocate memory"<<endl;
        exit(1);
    }
    
    FILE *f=fopen(file_name.data(),"r");
    if (!f)
    {
        cout<<"couldnt open file"<<endl;
        exit(1);
    } 
    uint32_t _col,_row;
    int inner_counter=1;
    cout<<"File opened"<<endl;
    s=fgetc(f);
    do
    {
        do
        {
            do
            {
                vect.push_back(s);
                s=fgetc(f);
            } while (s!=',');
            
            vect.push_back(' ');
            cout<<vect.back();
            if (s==',')
            {
                inner_counter++;
            }
            
            
        } while (s!='\n');
            inner_counter=0;
        
    } while (s!=EOF);
    

    cant=vect;
    fclose(f);
    FILE *f1;
    f1=fopen(file_name.data(),"r");
    if (!f1)
    {   
        cout<<"Couldnt open file"<<endl;
        exit(1);
    }
   
    char c;
    c=fgetc(f);
    {
            while (c=!'\n')
            {
                if (c==',')
                {
                _col=col+1;
                }
                c=fgetc(f);
            }
            if(c=='\n'){
                c=fgetc(f);
               _row=_row+1; 
            }
            
    }
    _row+1;
    _col+1;
    cols=&_col;
    rows=&_row;
    cout<<endl<<_col<<','<<_row<<endl;
   cout<<"File closed"<<endl;
    fclose(f);
    vect.clear();
}


void clear(char *&aux){
    aux=(char*)calloc(sizeof(char),2);
    if(!aux){
        cout<<"Couldnt clear memory"<<endl;
        exit(1);
    }
}

vector<float> mat(vector<char> conv){
    vector<float> output(conv.size());
    for (int i = 0; i < conv.size(); i++)
    {
        while (conv[i]!=' ')
        {
            
        }
        
    }
    
    
return output;   
}