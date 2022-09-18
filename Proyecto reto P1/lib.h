#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<time.h> 
#include<queue>
#include<math.h>
#include<string.h>
using namespace std;
typedef struct{
        float correlation;
        string id;

}Tipo_graph;
vector<float>Capt_tiempos(int ns);
float C_correlacion(vector<float>X,vector<float>Y);
float P_punto(vector<float>X,vector<float>Y);
vector<float>vect_1(int size);
int render_graphic();
void func_prin();
void tipo(Tipo_graph* a);
vector<float>graph_const(int tam);
vector<float>graph_parabolica(int tam);
vector<float>graph_lineal(int tam);
vector<float>graph_log(int tam);
Tipo_graph* QuickSort(Tipo_graph *array, int inicio, int final);





void func_prin(){
    Tipo_graph *comp1;
    vector<float>tiempos=Capt_tiempos(5);
    int tam=tiempos.size();
    comp1=(Tipo_graph*)calloc(tam,sizeof(Tipo_graph));
    if (!comp1)
    {
        exit;
    }
    
    vector<float>constante=graph_const(tam);
    vector<float>parabola=graph_parabolica(tam);
    vector<float>lineal=graph_lineal(tam);
    vector<float>logaritmica=graph_log(tam);
    comp1[0].correlation=C_correlacion(tiempos,constante);comp1[0].id="Constante";
    comp1[1].correlation=C_correlacion(tiempos,parabola);comp1[1].id="Parabolic";
    comp1[2].correlation=C_correlacion(tiempos,lineal);comp1[2].id="Lineal";
    comp1[3].correlation=C_correlacion(tiempos,logaritmica);comp1[3].id="Logaritmica";
    comp1=QuickSort(comp1,0,tam-1);
    
    tipo(comp1);    
    system("pause");

}


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
        Tiempos.push_back(float(estampa));
        
    }
    return Tiempos;
}

float C_correlacion(vector<float>X,vector<float>Y){
        vector<float>vecx=vect_1(X.size());
        vector<float>vecy=vect_1(Y.size());
        float aux1,aux2;
        float xpy=P_punto(X,Y);
        float xx=P_punto(X,X);
        float yy=P_punto(Y,Y);
        float x1=P_punto(X,vecx);
        float y1=P_punto(Y,vecy);
        float correlacion=0;
        aux1=sqrt(X.size()*xx-(x1*x1));
        aux2=sqrt(Y.size()*yy-(y1*y1));
        if (aux1==0||aux2==0)
        {
            
            return 0;
        }
        
        correlacion=((X.size()*xpy)-(x1*y1))/(aux1*aux2);
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
                X.pop_back();
                Y.pop_back();
            }
            return suma;
        }
        
        return 0;
        
}

vector<float>vect_1(int size){
    vector<float>vect;
    for (int i = 0; i < size; i++)
    {
        vect.push_back(1);
    }
    return vect;
}

void tipo(Tipo_graph* a){
    if (a[0].correlation<0&&a[3].correlation>0)
    {
        float comp=-a[0].correlation;
        if (comp>a[3].correlation)//vemos si en el valor absoluto son mayores o menores
        {
            cout<<"Es de tipo "<<a[0].id<<endl;
        }
    
    }else if(a[0].correlation>0){
            cout<<"Es de tipo "<<a[3].id<<endl;
    }else if(a[3].correlation<0){
            cout<<"Es de tipo"<<a[0].id<<endl;
    }else{
            cout<<"Es de tipo "<<a[3].id<<endl;
    }
    
}


Tipo_graph* QuickSort(Tipo_graph *array, int inicio, int final) {
  int i = inicio, f = final;
  Tipo_graph tmp;
  float x = array[(inicio + final) / 2].correlation;
        do {
            while(array[i].correlation < x && f <= final) {
            i++;
            }
            while(x < array[f].correlation && f > inicio) {
            f--;
            }
            if(i <= f) {
            tmp = array[i];
            array[i] = array[f];
            array[f] = tmp;
            
            i++; f--;
            }
   }         while(i <= f);

        if(inicio < f) {
          QuickSort(array,inicio,f);//algoritmo recursivo
        }

       if(i < final){
         QuickSort(array,i,final);
       }
        return array;
}


        
vector<float>graph_parabolica(int tam){
    vector<float>valores;
    for (int i = 0; i < tam; i++)
    {
        valores.push_back(pow(i,2));
    }
    return valores;
    
}
   
vector<float>graph_lineal(int tam){
    vector<float>valores;
    for (int i = 0; i < tam; i++)
    {
        valores.push_back(i);
    }
    return valores;
}


vector<float>graph_log(int tam){
    float i=.001;
    vector<float>valores;
    while (i<tam)
    {
        valores.push_back(log10(i));
        i++;
    }
    
    return valores;
}


vector<float>graph_const(int tam){
    vector<float>valores;
    for (int  i = 0; i < tam; i++)
    {
        valores.push_back(1);
    }
    return valores;
}