#include<iostream>
using namespace std;



void mergesort(int tam);
void sorting(int *p,int q, int r);
void merge(int *&array,int p, int q, int r);



int main(){
    mergesort(100);
    system("pause");
}

void mergesort(int tam){
    int *array=(int*)calloc(tam,sizeof(int));
    if (!array)
    {
        cout<<"Se termino la memoria"<<endl;
        return;
    }
    
    for (int i = 0; i < tam; i++)
    {
        array[i]=rand();
    }
    cout<<"array original: ";
    for (int i = 0; i < tam; i++)
    {
        cout<<array[i]<<", ";
    }
    cout<<endl;
    
    int q=0;
    int r=tam*sizeof(int)/sizeof(int)-1;
    sorting(array,q,r);
    cout<<"Array ordenado: ";
    for (int i = 0; i < tam; i++)
    {
        cout<<array[i]<<", ";
    }
    cout<<endl;
    
}
void sorting(int *p,int q, int r){//dividir
    if (q<r)
    {
        int div=(q+r)/2;
        sorting(p,q,div);
        sorting(p,div+1,r);
        merge(p,q,div,r);
    }
    
}

void merge(int *&array,int p, int q, int r){//p inicio, q medio, r fin
    int i,j,k;
    int n1=(q-p)+1,n2=(r-q);


    int *L=(int*)calloc(n1,sizeof(int));//creamos 2 sub arreglos
    int *R=(int*)calloc(n2,sizeof(int));
    for (int i = 0; i < n1; i++)
    {
        L[i]=array[i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i]=array[i+q+1];
    }
    
    for (k = p; k < r+1; k++)
        {
            if (i==n1)
            {
                *(array+k)=*(R+j);
                j=j+1;
            }else if(j==n2){
                *(array+k)=*(L+i);
                i=i+1;
            }else if(*(L+i)<=*(R+j)){
                *(array+k)=*(L+i);
                i=i+1;

            }else{
                *(array+k)=*(R+j);
                j=j+1;
            }

        }
}