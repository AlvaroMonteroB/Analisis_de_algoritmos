#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<vector>
#include<time.h> 
#include<math.h>
#include<string.h>
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
void BigO(vector<float>tiempos, Tipo_graph tipo);
punto_pendiente obtenerMayorfloat(vector<float>Tiempos);


//===================================================================
//===========================FUNCIONES==============================
//===================================================================


void func_prin(){
    Tipo_graph *comp1=NULL;
    Tipo_graph ret;
    
    int tam=400;
    vector<float>tiempos=Capt_tiempos(tam);
    render_graphic(tiempos);
    
    comp1=(Tipo_graph*)malloc(4*sizeof(Tipo_graph));
    
    if (!comp1)
    {   
        exit(5);  
    }
    
    vector<float>constante=graph_const(tam);
    vector<float>parabola=graph_parabolica(tam);
    vector<float>lineal=graph_lineal(tam);
    vector<float>logaritmica=graph_log(tam);
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
    system("pause");
    system("cls");
    notacion(tiempos,ret);

}


vector<float>Capt_tiempos(int ns){
    vector<float>Tiempos;
    clock_t estampa;
    for (int i = 0; i < ns; i++)
    {
        estampa=clock();
        //Bloque de codigo por analizar
        analisis(ns);
        //Termina bloque de codigo
        estampa=clock()-estampa;
        Tiempos.push_back(float(estampa));
        
    }
    cout<<(float)Tiempos.back()<<endl;
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
    int i=1;
    vector<float>valores;
    while (i<tam+1)
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


int render_graphic(vector<float>value){
        typedef Point_<float> pointfloat;
        int num=obtenerMayor(value);
        Mat fondo(num*20, (int)value.size(), CV_64FC4,
              Scalar(255, 255, 255));
        if (!fondo.data)
        {
            cout<<"couldn't create image"<<endl;
            return 0;
        }
        for (int i = 1; i < value.size(); i++)
        {
            Point ini(i-1,(int)value[i-1]*20);
            Point fin(i,(int)value[i]*20);
            Scalar color(255,0,0);
            line (fondo,ini,fin,color,1);
        }
        
        
        
        namedWindow("Grafica",WINDOW_AUTOSIZE);
        moveWindow("Grafica",300,140);
        imshow("Grafica",fondo);
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
    int opt;
    
    do
    {
    cout<<"Selecciona que notación quieres"<<endl<<"1.-Big O"<<endl<<"2.-Little O"<<endl;
    cout<<"3.-Big Omega"<<endl<<"4.-Little Omega"<<endl<<"5.-Big Theta"<<endl<<"6.-Little Theta"<<endl<<"7.-Salir del programa"<<endl;
    cin>>opt;
    switch (opt)
    {
    case 1:
        BigO(vect, tipo);
        break;
    case 2:
        
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



void BigO(vector<float>tiempos, Tipo_graph tipo){
    float  abj, arr,may;
    punto_pendiente pendiente;
    vector<float> m;
    for (int i = 1; i < tiempos.size(); i++)
    {
        arr=tiempos.back()-0;
        abj=i-0;
        m.push_back(arr/abj);
        }
        pendiente=obtenerMayorfloat(m);
        cout<<"El punto de mayor pendiente es : ("<<pendiente.punto<<", "<<pendiente.pendiente<<")"<<endl;
        if (tipo.id=="Parabolica")
        {
            float exp;
        }
        

    
}