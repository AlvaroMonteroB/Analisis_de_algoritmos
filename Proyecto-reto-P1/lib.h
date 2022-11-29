/* ▪* Montero Barraza Alvaro David*
 3BV1▪* Ingenieria en IA ▪* ▪*/
//#define CVPLOT_HEADER_ONLY
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
//==========================Estructuras==============================
//===================================================================

typedef struct{
        long double correlation;
        char id[11];
        int band;

}Tipo_graph;

typedef struct{
    long double pendiente;
    int punto;
}punto_pendiente;

typedef struct{
        int band;
        long double func;
}Tipo_eqn;


//===================================================================
//===========================PROTOTIPOS DE FUNCIONES=================
//===================================================================
vector<long double>Capt_tiempos(int ns);
long double C_correlacion(vector<long double>X,vector<long double>Y);
long double P_punto(vector<long double>X,vector<long double>Y);
vector<long double>vect_1(int size);
int render_graphic(const vector<long double>value);
void func_prin();
Tipo_graph tipo(Tipo_graph* a);
vector<long double>graph_const(int tam);
vector<long double>graph_parabolica(int tam);
vector<long double>graph_lineal(int tam);
vector<long double>graph_log(int tam);
Tipo_graph* QuickSort(Tipo_graph *array, int inicio, int final);
void analisis(int ns);
void notacion(const vector<long double> vect,Tipo_graph tipo);
int obtenerMayor(vector<long double>Tiempos);
Tipo_eqn BigO(const vector<long double>tiempos, Tipo_graph tipo);
Tipo_eqn LittleO(const vector<long double>tiempos,Tipo_graph tipo);
Tipo_eqn BigW(const vector<long double>tiempos,Tipo_graph tipo);
punto_pendiente obtenerMayorfloat(const vector<long double>Tiempos);
punto_pendiente Obtenermenordoub(const vector<long double> Tiempos);
long double logbn(long double b, long double n);
vector<long double> get_vector(Tipo_eqn func);
vector<long double> transX(vector<long double>vect);
void Draw_graph(vector<long double>Tn, vector<long double>Gn);


//===================================================================
//===========================FUNCIONES==============================
//===================================================================


void func_prin(){
    Tipo_graph *comp1=NULL;
    Tipo_graph ret;
    
    vector< long double>tiempos=Capt_tiempos(400);
    for (int i = 0; i < 400; i++)
    {
        cout<<tiempos[i]<<',';
        if(i%10==0){
            cout<<endl;
        }
    }
    
    render_graphic(tiempos);
    
    comp1=(Tipo_graph*)malloc(4*sizeof(Tipo_graph));
    
    if (!comp1)
    {   
        exit(5);  
    }
    
    vector<long double>constante=graph_const(400);
    vector<long double>parabola=graph_parabolica(400);
    vector<long double>lineal=graph_lineal(400);
    vector<long double>logaritmica=graph_log(400);
    comp1[0].correlation=C_correlacion(tiempos,constante);cout<<comp1[0].correlation;system("pause");//comp1[0].id="Constante";
    strcpy(comp1[0].id,"Constante");
    comp1[0].band=0;
    comp1[1].correlation=C_correlacion(tiempos,parabola);//comp1[1].id._Copy_s();
    strcpy(comp1[1].id,"Parabolica");
    comp1[1].band=1;
    comp1[2].correlation=C_correlacion(tiempos,lineal);//comp1[2].id="Lineal";
    strcpy(comp1[2].id,"Lineal");
    comp1[2].band=2;
    comp1[3].correlation=C_correlacion(tiempos,logaritmica);//comp1[3].id="Logaritmica";
    strcpy(comp1[3].id,"Logaritmica");
    comp1[3].band=3;
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


vector<long double>Capt_tiempos(int ns){
    int constante=400;
    vector<long double>Tiempos(400);
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
                Tiempos[i]=(long double)estampa;
                 
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
                Tiempos[i]=(long double)estampa;
                
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
                Tiempos[i]=(long double)estampa;
                
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

long double C_correlacion(vector<long double>X,vector<long double>Y){
        if (X.size()!=Y.size())
        {
            cout<<"El vector no es del mismo tamaño"<<endl;
        }
        
        vector<long double>vecx=vect_1((int)X.size());
        vector<long double>vecy=vect_1((int)Y.size());
        long double aux1,aux2;
        long double xpy=P_punto(X,Y);
        long double xx=P_punto(X,X);
        long double yy=P_punto(Y,Y);
        long double x1=P_punto(X,vecx);
        long double y1=P_punto(Y,vecy);
        long double correlacion=0;
        aux1=sqrt(X.size()*xx-(x1*x1));
        aux2=sqrt(Y.size()*yy-(y1*y1));
        if (aux1==0||aux2==0)
        {
            
            return 0;
        }
        
        correlacion=((X.size()*xpy)-(x1*y1))/(aux1*aux2);
        return correlacion;

}


long double P_punto(vector<long double>X,vector<long double>Y){
        int size_x,size_y;
        long double suma=0,aux;
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

vector<long double>vect_1(int size){
    vector<long double>vect(size);
    for (int i = 0; i < size; i++)
    {
        vect[i]=1;
    }
    return vect;
}

Tipo_graph tipo(Tipo_graph* a){
    if (a[0].correlation<=0&&a[3].correlation>=0)
    {
        long double comp=-a[0].correlation;
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
  long double x = array[(inicio + final) / 2].correlation;
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


        
vector<long double>graph_parabolica(int tam){
    vector<long double>valores(tam);
    for (int i = 0; i < tam; i++)
    {
        valores[i]=(pow(i,2));
    }
    return valores;
    
}
   
vector<long double>graph_lineal(int tam){
    vector<long double>valores(tam);
    for (int i = 0; i < tam; i++)
    {
        valores[i]=(i);
    }
    return valores;
}


vector<long double>graph_log(int tam){
    int i=1;
    vector<long double>valores(tam);
    while (i<tam+1)
    {
        valores[i-1]=(log10(i));
        i++;
    }
    
    return valores;
}


vector<long double>graph_const(int tam){
    vector<long double>valores;
    valores.resize(tam);
    for (int  i = 0; i < tam; i++)
    {
        valores[i]=(1);
    }
    return valores;
}
//==========================================================================================================
//==================================1ST RENDER FUNCTION=====================================================
//==========================================================================================================

int render_graphic(const vector<long double>value){
        typedef Point_<long double> pointfloat;
        Mat matriz(600,450,CV_64FC4,Scalar(255, 255, 255));
        if (!matriz.data)
        {
            cout<<"couldn't create image"<<endl;
            return 0;
        }
        for (int i = 1; i < value.size(); i++)
            
        {
            Point ini((i-1)+50,(int)value[i-1]);
            Point fin(i+50,(int)value[i]);
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


void notacion(const vector<long double> vect, Tipo_graph tipo){
    int opt=0;
    Tipo_eqn tip={};
    vector<long double>val;
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
     vector<long double>Gn=get_vector(tip);
     Draw_graph(vect,Gn);

    } while (opt<7);
    
}

int obtenerMayor(const vector<long double>Tiempos){
    int Mayor=0;
    for (int i=0; i<Tiempos.size(); i++) {
        if(i==0)
            Mayor=Tiempos[i];
        else{
            if(Tiempos[i]>Mayor)
                Mayor=Tiempos[i];
        }
    }
    system("pause");
    return Mayor;   
}


punto_pendiente obtenerMayorfloat(const vector<long double>Vect){//vector de pendientes
    punto_pendiente Mayor;
    Mayor.pendiente=Vect[0];
    Mayor.punto=0;
    for (int i=1; i<Vect.size(); i++) {
            if(Vect[i]>Mayor.pendiente){
                cout<<i<<' ';
                Mayor.pendiente=Vect[i];
                Mayor.punto=i;
            }
    }
    cout<<"Tiempo mayor"<<Mayor.punto<<','<<Mayor.pendiente<<endl;
    return Mayor;
}


Tipo_eqn LittleO(const vector<long double>tiempos,Tipo_graph tipo){//TODO hacerle bien
        long double  abj, arr;
    Tipo_eqn result={};
    punto_pendiente pendiente;
    vector<long double> m(tiempos.size());
    for (int i = 1; i < tiempos.size(); i++)
    {
        abj=(long double)(i);if(abj==0)
        if(abj==0){
            m[i]=0;
        }else{
            m[i]=(long double)(tiempos[i]/abj);
        }
        
        }
        pendiente=obtenerMayorfloat(m);
        cout<<"El punto de mayor pendiente es : ("<<pendiente.punto<<", "<<tiempos[pendiente.punto]<<")"<<endl;
        cout<<"La pendiente obtenida es: "<<pendiente.pendiente<<endl;
        if (tipo.id=="Parabolica")
        {
            long double e;
            e=logbn(pendiente.punto,tiempos[pendiente.punto]);
            cout<<"La ecuacion de tu funcion es: O(X^"<<e<<") "<<endl;
            result.func=e;
            return result;
            
        }else if(tipo.id=="Lineal"){

            long double e;
            e=pendiente.pendiente;

            result.func=e;
            result.band=0;
            cout<<"La ecuacion de tu funcion es: O("<<e<<"X)"<<endl;
            return result;

        }else if(tipo.id=="Logaritmica"){
            
            
        }   
        return result;
    
}


Tipo_eqn BigO(const vector<long double>tiempos, Tipo_graph tipo){//0 const// 1 parabola//2 lineal//3 logaritmica
    long double  abj;
    Tipo_eqn result={};
    punto_pendiente pendiente;
    vector<long double> m(tiempos.size());
    for (int i = 0; i < tiempos.size(); i++)
    {
        abj=(long double)(i);
        if(abj==0){
            m[i]=0;
        }else{
            m[i]=tan((long double)(tiempos[i]/abj));
        }
        
        }
        pendiente=obtenerMayorfloat(m);
        cout<<"El punto de mayor pendiente es : ("<<pendiente.punto<<", "<<tiempos[pendiente.punto]<<")"<<endl;
        cout<<"La pendiente obtenida es: "<<pendiente.pendiente<<endl;
        if (tipo.band==1)
        {
            long double e;
            e=logbn(pendiente.punto,tiempos[pendiente.punto]);
            if(e==0){
                cout<<"La ecuacion de tu funcion es O(1)"<<endl;
                result.band=0;
            }else{
            cout<<"La ecuacion de tu funcion es: O(X^"<<e<<") "<<endl;
                result.band=1;
            } result.func=e;
            
        }else if(tipo.band==2){

            long double e;
            e=pendiente.pendiente;
            cout<<"La ecuacion de tu funcion es: O("<<e<<"X)"<<endl;
            result.band=2;
            result.func=e;

        }else if(tipo.band==3){
            long double e=pow(pendiente.punto,1/tiempos[pendiente.punto]);
            cout<<"La ecuacion de tu funcion es: O(Log("<<e<<")(X)";
            result.band=3;
            result.func=e;
            
        }else if(tipo.band==0){
            cout<<"Su ecuacion es constante"<<endl;
            result.band=0;
            long double e=0;
            result.func=e;
        }
        system("pause");
        return result;
    
}


long double logbn(long double b, long double n){
    if(log(b)==0){
        return 0;
    }
    if(b<0){
        return 0;
    }else if(n<0){
        return 0;
    }
    return log(n)/log(b);
}


vector<long double> get_vector(Tipo_eqn func){//0 const// 1 parabola//2 lineal//3 logaritmica
        vector<long double>fin(400);
        if (func.band==1)
        {
            for (int i = 0; i < 400; i++)
            {
                fin[i]=pow(i,(func.func));
            }
            
        }else if(func.band==2){
            for (int i = 0; i < 400; i++)
            {
                fin[i]=(func.func)*i;
            }
            
        }else if(func.band==3){
            for (int i = 1; i < 401; i++)
            {
                fin[i-1]=logbn((func.func),i);
            }
            
        }else if(func.band==0){
            fin=vect_1(fin.size());
        }
        return fin;
        
}




vector<long double>transX(vector<long double>vect){
        int cons=50;
        vector<long double> fin;
        fin.reserve(400);
        for (int i = 0; i < 400; i++)
        {
            fin[i]=vect[i]+50;
        }
        
        return fin;
}


void Draw_graph(const vector<long double>Tn, const vector<long double>Gn){
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

//const, parab, line, log