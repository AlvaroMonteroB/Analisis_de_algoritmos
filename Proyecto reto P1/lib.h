#include<iostream>
#include<vector>
#include<ctime>
#include<queue>
#include<math.h>
using namespace std;
vector<float>Capt_tiempos(int ns);
float C_correlacion(vector<float>X,vector<float>Y);
float P_punto(vector<float>X,vector<float>Y);
vector<float>vect_1(int size);
int render_graphic();
void tipo(float a,float b,float c,float d);


typedef struct Tipo_graph{
        float correlation;
        int id;

}Graph;

vector<float>Capt_tiempos(int ns){
    vector<float>Tiempos;
    clock_t estampa;
    for (int i = 0; i < ns; i++)
    {
        estampa=clock();
        //Bloque de codigo por analizar
        cout<<"Hola"<<endl;
        //Termina bloque de codigo
        estampa=clock()-estampa;
        Tiempos.push_back((float)estampa);
    }
    return Tiempos;
}

float C_correlacion(vector<float>X,vector<float>Y){
        vector<float>vecx=vect_1(X.size());
        vector<float>vecy=vect_1(Y.size());
        int aux1,aux2;
        float xpy=P_punto(X,Y);
        float xx=P_punto(X,X);
        float yy=P_punto(Y,Y);
        float x1=P_punto(X,vecx);
        float y1=P_punto(Y,vecy);
        float correlacion=0;
        aux1=sqrt(X.size()*xx-(x1*x1));
        aux2=sqrt(Y.size()*yy-(y1*y1));
        correlacion=(X.size()*xpy-x1*y1)/(aux1*aux2);

        return correlacion;

}


float P_punto(vector<float>X,vector<float>Y){
        int size_x,size_y;
        float suma=0,aux;
        size_x=X.size();
        size_y=Y.size();
        if (size_x==size_y)
        {
            for (int i = 0; i < size_x; i++)
            {
                aux=X.back()*Y.back();
                suma=suma+aux;
            }
            return suma;
        }
        return ;
        
}

vector<float>vect_1(int size){
    vector<float>vect;
    for (int i = 0; i < size; i++)
    {
        vect.push_back(1);
    }
    return vect;
}

void tipo(float a,float b,float c,float d){
    priority_queue<float>Valores;
    Valores.push(a);Valores.push(b);Valores.push(c);Valores.push(d);
    float highest,lowest;
    highest=Valores.top();
    for (int i = 0; i < 3; i++)
    {
        Valores.pop();
    }
    lowest=Valores.top();
    if (lowest<0&&highest>0)
    {
        if (-lowest<highest)
        {
            
         }
    }else if(lowest>0&&highest>0){
            
            
    }else if (lowest<0&&highest<0)
    {
        
    }


}