#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

class Matrix{
    public:
    vector<float> _vals;
    uint32_t    _cols;
    uint32_t    _rows;
    public:
    Matrix(uint32_t cols, uint32_t rows)
        :_cols(cols),
        _rows(rows),
        _vals({})
        {
        _vals.resize(_cols*_rows);
        }

    float  &at(uint32_t col,uint32_t row){
        return _vals[row*_cols+col];
    }


    Matrix multiply(Matrix& target){
        assert(_cols==target._rows);
        Matrix output(target._cols,_rows);
        for (int i = 0; i < output._rows; i++)
        {
            for (int j = 0; j < output._cols; j++)
            {
                float result= 0.0f;
                for (int k = 0; k < _cols; k++)
                {
                    result+= at(k,i)*target.at(j,k);
                }
                output.at(j,i)=result;
            }
            
        }
        return output;

    }
    void display();

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
};

//smultiplication of two matrix by strassen
SMatrix SMatrix::multiply(SMatrix &target){
    assert(_cols==target._rows);
    SMatrix output(target._cols,_rows);
    if(_cols==1){
        output.at(0,0)=at(0,0)*target.at(0,0);
        return output;}




    }


    void Matrix::display(){
        for (uint32_t i = 0; i < _cols; i++)
        {
            for (uint32_t j = 0; j < _rows; j++)
            {
                cout<<at(i,j)<<' ';
            }
            cout<<endl;
        }
        
    }