#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

class Matrix{
    public:
        uint32_t _cols;
        uint32_t _rows;
        vector<float>_vals;
    public:
    Matrix(uint32_t cols, uint32_t rows)
    :_cols(cols),
     _rows(rows),
     _vals({}){
        _vals.resize(cols*rows,0.0f);  
     }
     void display();
     float &at(uint32_t col, uint32_t row){
        return _vals[row*_cols+row];
     }
     Matrix multiply(Matrix& Target){
            assert(_cols==Target._rows);
            Matrix output(Target._cols,_rows);
            for (uint32_t i = 0; i < output._rows; i++)
            {
                for (uint32_t j = 0; j < output._cols; j++)
                {
                    double result= 0.0f;
                    for (uint32_t k = 0; k < _cols; k++)
                        {
                            result+=at(k,i) * Target.at(j,k);
                           
                        }
                     output.at(j,i)=result;
                }
                
                
                
            }
            return output;
            
     }
     Matrix add(Matrix &target){
        assert(_rows==target._rows&&_cols==target._cols);
        Matrix output(target._cols,_rows);
        for (size_t i = 0; i < output._rows; i++)
        {
            for (size_t j = 0; j < output._cols; i++)
            {
                output.at(j,i)=at(j,i)+target.at(j,i);
            }
            
        }
        return output;
     }
     

     Matrix multiplyScaler(float s){
        Matrix output(_cols,_rows);
        for(uint32_t i;i<_rows;i++){
            for (uint32_t j = 0; j < _cols; j++)
            {
                output.at(j,i)=at(j,i)*s;
            }
        }
        return output;

     }
     Matrix addScaler(float s){
         Matrix output(_cols,_rows);
        for(uint32_t i;i<_rows;i++){
            for (uint32_t j = 0; j < _cols; j++)
            {
                output.at(j,i)=at(j,i)+s;
            }
        }
        return output;
     }

     Matrix negative(){
        Matrix output(_cols,_rows);
        for(uint32_t i;i<_rows;i++){
            for (uint32_t j = 0; j < _cols; j++)
            {
                output.at(j,i)=-at(j,i);
            }
        }
        return output;
     }

     Matrix transpose(){
        Matrix output(_rows,_cols);
        for (uint32_t i = 0; i <_rows; i++)
        {
            for (uint32_t j = 0; i < _cols; i++)
            {
                output.at(i,j)=at(j,i);
            
            }
        return output;
            }
     }
};


class SMatrix{
    public:
    vector<float> _vals;
    uint32_t    _cols;
    uint32_t    _rows;
    public:
     SMatrix(uint32_t cols, uint32_t rows)
        :_cols(cols),
        _rows(rows),
        _vals({})
        {_vals.resize(cols*rows);}
        public:
    SMatrix multiply(SMatrix &target);
    float  &at(uint32_t col,uint32_t row){
        return _vals[row*_cols+col];
    }
    SMatrix brute_force(SMatrix &target);
};

//smultiplication of two matrix by strassen
SMatrix SMatrix::multiply(SMatrix &target){
    assert((_cols==target._rows)&&(_rows==target._cols));
    SMatrix output(target._cols,_rows);
    if ((target._cols==_rows)&&(target._rows))
    {
        brute_force(target);
    }
    




    }


    void Matrix::display(){
        for (uint32_t i = 0; i < _rows*_cols; i++)
        {
            
                cout<<_vals[i]<<' ';
            
            cout<<endl;
        }
        
    }


    SMatrix SMatrix::brute_force(SMatrix &Target){
            assert(_cols==Target._rows);
            SMatrix output(Target._cols,_rows);
            for (uint32_t i = 0; i < output._rows; i++)
            {
                for (uint32_t j = 0; j < output._cols; j++)
                {
                    double result= 0.0f;
                    for (uint32_t k = 0; k < _cols; k++)
                        {
                            result+=at(k,i) * Target.at(j,k);
                           
                        }
                     output.at(j,i)=result;
                }
                
                
                
            }
            return output;
            
     }
    