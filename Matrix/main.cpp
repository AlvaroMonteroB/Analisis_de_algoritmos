#include<iostream>
#include"filestream.h"
#include"matrix.h"
#include<vector>
using namespace std;

void read_file();
void input_data();


//usar split para el archivo
int main(){
    int opt;
    cout<<"1.-Leer de un archivo"<<endl<<"2.-Introducir matrices"<<endl;
    cin>>opt;
    switch (opt)
    {
    case 1:
        read_file();
        break;
    case 2:
        input_data();
        break;
    default:
        break;
    }



}

void read_file(){
    string mat1="mat1.txt";
    string mat2="mat2.txt";
    uint32_t *row, *col;
    vector<char*> str;
    vector<float> vect1;

    str=stream(str,col,row,mat1);
    if (!str.empty())
    {
        cout<<"si existe"<<endl;
        cout<<str.size()<<endl;
    }
    
    for (int i = 0; i < str.size(); i++)
    {
        cout<<str[i]<<' ';
        if (i%3==0)
        {
            cout<<endl;
        }
        
    }
    cout<<"Debug1"<<endl;
    vect1=mat(str);
    Matrix mat_1(col[0],row[0]);
    SMatrix smat_1(col[0],row[0]);
    mat_1._vals=vect1;
    smat_1._vals=vect1;

    str.clear();
    vect1.clear();
    mat_1.display();
    system("pause");
    
    str=stream(str,col,row,mat2);
    vect1=mat(str);
    Matrix mat_2(col[0],row[0]);
    SMatrix smat_2(col[0],row[0]);
    mat_2._vals=vect1;
    smat_2._vals=vect1;
    str.clear();
    vect1.clear();

    mat_1.multiply(mat_2);

}

void input_data(){
    int tam[3]; 
    cout<<"Introduce el tamaño de la matriz nxm"<<endl; 
    for (int i = 0; i < 2; i++)
    {
        
        cin>>tam[i];
        
    }
    tam[2]=tam[0]*tam[1];
        vector<float>vect1(tam[2]);
        cout<<"Introduce las componentes"<<endl;
        for (int j = 0; j < tam[2]; j++)
        {
            cin>>vect1[j];
        }
    Matrix mat1(tam[0],tam[1]);
    mat1._vals=vect1;
      cout<<"Introduce el tamaño de otra matriz nxm"<<endl; 
    for (int i = 0; i < 2; i++)
    {
        
        cin>>tam[i];
        
    }
     tam[2]=tam[0]*tam[1];
        vect1.resize(tam[2]);
        cout<<"Introduce las componentes"<<endl;
        for (int j = 0; j < tam[2]; j++)
        {
            cin>>vect1[j];
        }
        Matrix mat2(tam[0],tam[1]);
        mat2._vals=vect1;

        Matrix out=mat1.multiply(mat2);
        out.display();

    

}