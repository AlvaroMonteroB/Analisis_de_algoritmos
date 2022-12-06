#include<iostream>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
void clear(char *&aux);
vector<char*> stream(vector<char*>cant,uint32_t *&cols,uint32_t *&rows,string file_name);
vector<float> mat(vector<char*> conv);




vector<char*> stream(vector<char*>cant,uint32_t *&cols,uint32_t *&rows,string file_name){

    char str[5];
    int counter=0;
    char s;
    bool col,row;
    vector<char*>vect;
    char aux[2];
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
    cout<<"File opened"<<endl;
    cols=(uint32_t*)calloc(1,sizeof(uint32_t));
    rows=(uint32_t*)calloc(1,sizeof(uint32_t));
    do
    {
        
                do
            {
                    do
                    {   
                        s=fgetc(f);
                        cout<<s;
                        if(s!=','&&s!=EOF){//5,3,5
                        aux[counter]=s;
                        counter++;
                        col=true;
                        }else if(s=='\n'&&s!=EOF){
                            cols[0]++;
                            col=false;
                        }else{
                            col=false;
                        }
                        
                    } while (col);
                    
                    vect.push_back(aux);
                    counter=0;
                    aux[0]=0,aux[1]=0;
                    
                    row=false;
                    rows[0]++;
            } while (row);
            if (s!=EOF)
            {
             col,row=true;
            }
            
            
    } while (s!=EOF);
    cant=vect;
    /*
    rewind(f);
    char c;
    c=fgetc(f);
    cols=(uint32_t*)calloc(1,sizeof(uint32_t));
    rows=(uint32_t*)calloc(1,sizeof(uint32_t));
    cols[0]=(uint32_t)1;
    rows[0]=(uint32_t)1;
    while (c=!EOF)
    {
            while (c=!'\n')
            {
                if (c==',')
                {
                cols[0]+=cols[0];
                }
                c=fgetc(f);
            }
            rows[0]++;
    }*/
    cout<<endl<<cols[0]<<','<<rows[0];
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

vector<float> mat(vector<char*> conv){
    cout<<"Debug2"<<endl;
    vector<float> output(conv.size());
    for (int i = 0; i < conv.size(); i++)
    {
        output[i]=stof(conv[i]);
    }
return output;   
}