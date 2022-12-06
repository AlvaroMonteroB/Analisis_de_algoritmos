#include<iostream>
#include"filestream.h"
#include"matrix.h"
#include<vector>
using namespace std;

//usar split para el archivo
int main(){
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


//create a dinamic variable 

}