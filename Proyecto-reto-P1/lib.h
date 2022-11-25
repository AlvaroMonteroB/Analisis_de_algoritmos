/* ▪* Montero Barraza Alvaro David*
 3BV1▪* Ingenieria en IA ▪* ▪*/
#define CVPLOT_HEADER_ONLY
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<vector>
#include<time.h> 
#include"algoritmos.h"
#include<string.h>
#include<cmath>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

//===================================================================
//=================================Estructura========================
//===================================================================

typedef struct{
        float correlation;
        //string id;
        char id[11];

}Tipo_graph;

typedef struct{
    float pendiente;
    int punto;
}punto_pendiente;

typedef struct{
        float *Exp=NULL;
        float *Line=NULL;
        float *Logbn=NULL;
}Tipo_eqn;


//===================================================================
//===========================PROTOTIPOS DE FUNCIONES=================
//===================================================================
vector<float>Capt_tiempos(int ns);
float C_correlacion(vector<float>X,vector<float>Y);
float P_punto(vector<float>X,vector<float>Y);
vector<float>vect_1(int size);
int render_graphic(vector<float>value);
void func_prin();
Tipo_graph tipo(Tipo_graph* a);
vector<float>graph_const(int tam);
vector<float>graph_parabolica(int tam);
vector<float>graph_lineal(int tam);
vector<float>graph_log(int tam);
Tipo_graph* QuickSort(Tipo_graph *array, int inicio, int final);
void analisis(int ns);
void notacion(vector<float> vect,Tipo_graph tipo);
int obtenerMayor(vector<float>Tiempos);
Tipo_eqn BigO(vector<float>tiempos, Tipo_graph tipo);
Tipo_eqn LittleO(vector<float>tiempos,Tipo_graph tipo);
punto_pendiente obtenerMayorfloat(vector<float>Tiempos);
float logbn(float b, float n);
vector<float> get_vector(Tipo_eqn func);
vector<float> transY(vector<float> vect);
vector<float> transX(vector<float>vect);
void Draw_graph(vector<float>Tn, vector<float>Gn);


//===================================================================
//===========================FUNCIONES==============================
//===================================================================


void func_prin(){
    Tipo_graph *comp1=NULL;
    Tipo_graph ret;
    vector<float>tiempos=Capt_tiempos(400);
    cout<<"Parece que aqui es";
    render_graphic(tiempos);
    
    comp1=(Tipo_graph*)malloc(4*sizeof(Tipo_graph));
    
    if (!comp1)
    {   
        exit(5);  
    }
    
    vector<float>constante=graph_const(400);
    vector<float>parabola=graph_parabolica(400);
    vector<float>lineal=graph_lineal(400);
    vector<float>logaritmica=graph_log(400);
    comp1[0].correlation=(float)C_correlacion(tiempos,constante);cout<<comp1[0].correlation;system("pause");//comp1[0].id="Constante";
    strcpy(comp1[0].id,"Constante");
    comp1[1].correlation=(float)C_correlacion(tiempos,parabola);//comp1[1].id._Copy_s();
    strcpy(comp1[1].id,"Parabolica");
    comp1[2].correlation=(float)C_correlacion(tiempos,lineal);//comp1[2].id="Lineal";
    strcpy(comp1[2].id,"Lineal");
    comp1[3].correlation=(float)C_correlacion(tiempos,logaritmica);//comp1[3].id="Logaritmica";
    strcpy(comp1[3].id,"Logaritmica");
    comp1=QuickSort(comp1,0,3);
    for (int i = 0; i < 4; i++)
    {
        cout<<comp1[i].id<<" Correlacion: "<<comp1[i].correlation<<endl;
        
    }

    ret=tipo(comp1);
    free(comp1);
    system("pause");
    system("cls");
    notacion(tiempos,ret);

}


vector<float>Capt_tiempos(int ns){
    int constante=400;
    vector<float>Tiempos(400);
    clock_t estampa;
    int arr[400];
     int *array=(int*)calloc(constante,sizeof(int));
    for (int i = 0; i < constante; i++)
    {
        arr[i]=rand();
    }
    
    int opt=0;
    cout<<"Que algoritmo quieres analizar?"<<endl;
    cout<<"1.-Mergesort"<<endl<<"2.-Quicksort"<<endl<<"3.-Burbuja"<<endl;
    while (opt==0)
    {   
        cin>>opt;
        switch (opt)
    {
        case 1:
                for (int i = 0; i < ns; i++)
            {
                array=arr;
                estampa=clock();
                //Bloque de codigo por analizar
                array=merges(400,array);
                //Termina bloque de codigo
                estampa=clock()-estampa;
                Tiempos[i]=(float)estampa;
                 
            }
            for (int i = 0; i < 10; i++)
                {
                    cout<<array[i]<<", ";
                }
                return Tiempos;
            break;
         case 2:
                for (int i = 0; i < ns; i++)
            {
                array=arr;
                estampa=clock();
                //Bloque de codigo por analizar
                quick(400,array);
                //Termina bloque de codigo
                estampa=clock()-estampa;
                Tiempos[i]=(float)estampa;
                
            }
                for (int i = 0; i < 10; i++)
                {
                    cout<<array[i]<<", ";
                }
                return Tiempos;
            break;
        case 3:
                for (int i = 0; i < ns; i++)
            {
                array=arr;
                estampa=clock();
                //Bloque de codigo por analizar
                burbuja(400,array);
                //Termina bloque de codigo
                estampa=clock()-estampa;
                Tiempos[i]=(float)estampa;
                
            }
            for (int i = 0; i < 10; i++)
                {
                    cout<<array[i]<<", ";
                }
                 return Tiempos;
        
            break;
        default:
    cout<<"Introduce una opción válida"<<endl;
    opt=0;
        break;
    }
    }
    return Tiempos;
    
}

float C_correlacion(vector<float>X,vector<float>Y){
        if (X.size()!=Y.size())
        {
            cout<<"El vector no es del mismo tamaño"<<endl;
        }
        
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
                aux=X[i]*Y[i];
                suma=suma+aux;
            }
            return suma;
        }
        
        return 0;
        
}

vector<float>vect_1(int size){
    vector<float>vect(size);
    for (int i = 0; i < size; i++)
    {
        vect[i]=1;
    }
    return vect;
}

Tipo_graph tipo(Tipo_graph* a){
    if (a[0].correlation<=0&&a[3].correlation>=0)
    {
        float comp=-a[0].correlation;
        if (comp>a[3].correlation)//vemos si en el valor absoluto son mayores o menores
        {
            cout<<"Es de tipo "<<a[0].id<<endl;
            return a[0];
        }else{
            cout<<"Es de tipo "<<a[3].id<<endl;
            return a[3];
        }
    
    }else if(a[0].correlation>0){
            cout<<"Es de tipo "<<a[3].id<<endl;
            return a[3];
    }else if(a[3].correlation<0){ 
            cout<<"Es de tipo"<<a[0].id<<endl;
            return a[0];
    }else{
            cout<<"Es de tipo "<<a[3].id<<endl;
            return a[3];
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
    vector<float>valores(tam);
    for (int i = 0; i < tam; i++)
    {
        valores[i]=(pow(i,2));
    }
    return valores;
    
}
   
vector<float>graph_lineal(int tam){
    vector<float>valores(tam);
    for (int i = 0; i < tam; i++)
    {
        valores[i]=(i);
    }
    return valores;
}


vector<float>graph_log(int tam){
    int i=1;
    vector<float>valores(tam);
    while (i<tam+1)
    {
        valores[i-1]=(log10(i));
        i++;
    }
    
    return valores;
}


vector<float>graph_const(int tam){
    vector<float>valores;
    valores.resize(tam);
    for (int  i = 0; i < tam; i++)
    {
        valores[i]=(1);
    }
    return valores;
}


int render_graphic(vector<float>value){
        typedef Point_<float> pointfloat;
        value=transY(value);
        Mat matriz(600,450,CV_64FC4,Scalar(255, 255, 255));
        if (!matriz.data)
        {
            cout<<"couldn't create image"<<endl;
            return 0;
        }
            value=transY(value);
        for (int i = 1; i < value.size(); i++)
            
        {
            Point ini((i-1)+50,(int)value[i-1]*20);
            Point fin(i+50,(int)value[i]*20);
            Scalar color(255,0,0);
            line (matriz,ini,fin,color,1);
        }
        
        
        
        namedWindow("Grafica",WINDOW_AUTOSIZE);
        moveWindow("Grafica",300,140);
        imshow("Grafica",matriz);
        waitKey(0); 
        cout<<"Grafico generado "<<endl;
        return 0;
    
        
}


void analisis(int ns){
        for (int i = 0; i < 10; i++)
        {
            cout<<"hola";
        }
        
        
        
    
       
}


void notacion(vector<float> vect, Tipo_graph tipo){
    int opt=0;
    Tipo_eqn tip;
    vector<float>val;
    do
    {
    cout<<"Selecciona que notación quieres"<<endl<<"1.-Big O"<<endl<<"2.-Little O"<<endl;
    cout<<"3.-Big Omega"<<endl<<"4.-Little Omega"<<endl<<"5.-Big Theta"<<endl<<"6.-Little Theta"<<endl<<"7.-Salir del programa"<<endl;
    cin>>opt;
    switch (opt)
    {
    case 1:
        tip=BigO(vect, tipo);
        val=get_vector(tip);
        break;
    case 2:
        tip=LittleO(vect,tipo);
        val=get_vector(tip);
        break;
    case 3:
        
        break;
    case 4:
        
        break;
    case 5:
        
        break;
    case 6:
        
        break;
    case 7:
        break;
    default:
    cout<<"Introduce una opcion valida"<<endl;
        break;
    }
     vector<float>Gn=get_vector(tip);
     Draw_graph(vect,Gn);

    } while (opt<7);
    
}

int obtenerMayor(vector<float>Tiempos){
    int Mayor=0;
    for (int i=0; i<Tiempos.size(); i++) {
        if(i==0)
            Mayor=Tiempos[i];
        else{
            if(Tiempos[i]>Mayor)
                Mayor=Tiempos[i];
        }
    }
    return Mayor;
}


punto_pendiente obtenerMayorfloat(vector<float>Vect){
    punto_pendiente Mayor;
    for (int i=0; i<Vect.size(); i++) {
        if(i==0)
            Mayor.pendiente=Vect[i];
        else{
            if(Vect[i]>Mayor.pendiente)
                Mayor.pendiente=Vect[i];
                Mayor.punto=i;
        }
    }
    return Mayor;
}


Tipo_eqn LittleO(vector<float>tiempos,Tipo_graph tipo){//TODO hacerle bien
        float  abj, arr;
    Tipo_eqn result;
    punto_pendiente pendiente;
    vector<float> m;
    m.reserve((int)tiempos.size());
    for (int i = 1; i < tiempos.size(); i++)
    {
        arr=tiempos.back()-0;
        abj=(int)(i-0);
        m[i]=(int)(arr/abj);
        }
        pendiente=obtenerMayorfloat(m);
        cout<<"El punto de mayor pendiente es : ("<<pendiente.punto<<", "<<tiempos[pendiente.punto]<<")"<<endl;
        cout<<"La pendiente obtenida es: "<<pendiente.pendiente<<endl;
        if (tipo.id=="Parabolica")
        {
            float e;
            e=logbn(pendiente.punto,tiempos[pendiente.punto]);
            cout<<"La ecuacion de tu funcion es: O(X^"<<e<<") "<<endl;
            result.Exp=&e;
            return result;
            
        }else if(tipo.id=="Lineal"){

            float e;
            e=pendiente.pendiente;

            result.Line=&e;
            cout<<"La ecuacion de tu funcion es: O("<<e<<"X)"<<endl;
            return result;

        }else if(tipo.id=="Logaritmica"){
            
            
        }   
        return result;
    
}


Tipo_eqn BigO(vector<float>tiempos, Tipo_graph tipo){
    float  abj, arr;
    Tipo_eqn result;
    punto_pendiente pendiente;
    vector<float> m(tiempos.size());
    for (int i = 1; i < tiempos.size(); i++)
    {
        arr=tiempos.back()-0;
        abj=(float)(i-0);
        m[i]=(float)(arr/abj);
        }
        pendiente=obtenerMayorfloat(m);
        cout<<"El punto de mayor pendiente es : ("<<pendiente.punto<<", "<<tiempos[pendiente.punto]-50<<")"<<endl;
        cout<<"La pendiente obtenida es: "<<pendiente.pendiente<<endl;
        if (tipo.id=="Parabolica")
        {
            float e;
            e=logbn(pendiente.punto,tiempos[pendiente.punto]);
            cout<<"La ecuacion de tu funcion es: O(X^"<<e<<") "<<endl;
            result.Exp=&e;
        }else if(tipo.id=="Lineal"){

            float e;
            e=pendiente.pendiente;
            cout<<"La ecuacion de tu funcion es: O("<<e<<"X)"<<endl;
            result.Line=&e;

        }else if(tipo.id=="Logaritmica"){
            float e=pow(pendiente.punto,1/tiempos[pendiente.punto]);
            cout<<"La ecuacion de tu funcion es: O(Log("<<e<<")(X)";
            result.Logbn=&e;
            
        }else{
            cout<<"Su ecuacion es lineal";
        }
        cout<<"Aqui va bien";
        return result;
    
}


float logbn(float b, float n){
    return log(n)/log(b);
}


vector<float> get_vector(Tipo_eqn func){
        vector<float>fin(400);
        if (func.Exp)
        {
            for (int i = 0; i < 400; i++)
            {
                fin[i]=pow(i,(*func.Exp));
            }
            
        }else if(func.Line){
            for (int i = 0; i < 400; i++)
            {
                fin[i]=(*func.Line)*i;
            }
            
        }else if(func.Logbn){
            for (int i = 1; i < 401; i++)
            {
                fin[i]=logbn((*func.Logbn),i);
            }
            
        }
        return fin;
        
}


vector<float> transY(vector<float> vect){//Se transforman las coordenadas de los pixeles
    int cons=600;
    vector<float> fin(vect.size());
    for (int i = 0; i < vect.size(); i++)
    {
        fin[i]=600-vect[i]-50;
    }
    
    return fin;
}


vector<float>transX(vector<float>vect){
        int cons=50;
        vector<float> fin;
        fin.reserve(400);
        for (int i = 0; i < 400; i++)
        {
            fin[i]=vect[i]+50;
        }
        
        return fin;
}


void Draw_graph(vector<float>Tn, vector<float>Gn){
    Mat image(600,800,CV_64FC4,Scalar(255, 255, 255));
    if(!image.data){
        cout<<"Couldnt create image";
        return;
    }
    for (int i = 1; i < Tn.size(); i++)
            
        {
            Point ini((i-1)+50,(int)Tn[i-1]*20);
            Point fin(i+50,(int)Tn[i]*20);
            Scalar color(255,0,0);
            line (image,ini,fin,color,1);
        }
    for (int i = 1; i < Tn.size(); i++)
            
        {
            Point ini((i-1)+50,(int)Gn[i-1]*20);
            Point fin(i+50,(int)Gn[i]*20);
            Scalar color(0,0,255);
            line (image,ini,fin,color,1);
        }


}