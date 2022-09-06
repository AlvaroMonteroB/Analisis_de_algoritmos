#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
vector<float>Capt_tiempos(int ns);


vector<float>Capt_tiempos(int ns){
    vector<float>Tiempos;
    clock_t estampa;
    for (int i = 0; i < ns; i++)
    {
        estampa=clock();
        cout<<"Hola"<<endl;
        estampa=clock()-estampa;
        Tiempos.push_back((float)estampa);
    }
    return Tiempos;
}