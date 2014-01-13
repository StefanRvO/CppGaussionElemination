#include<iostream>
#include<random>
#include<stdlib.h>
#include<array>
#include<time.h>
#include<string>
#include<sstream>
#define ARRAYSIZE 100
using namespace std;

template <size_t size_y>
void PrintMatrix(double Matrix[][size_y],int Width,int Height) {
for(int i=0;i<Height;i++) {
    for(int j=0;j<Width;j++) {
        cout << Matrix[i][j] << "\t";
        }
    cout<<endl;
    }
}

void MultiplyRow(double Row[],int Width,double Scalar) {
    for(int i=0;i<Width;i++) {
        Row[i]=Row[i]*Scalar;
        }
    }
template <size_t size_y>
void AddRow(double Matrix[][size_y],int RowNR1,int RowNR2,double multi=1) {
    for(int i=0;i<size_y;i++) {
        Matrix[RowNR2][i]+=Matrix[RowNR1][i]*multi;
        }
    }

template <size_t size_y>
void SwitchRow(double Matrix[][size_y],int RowNR1,int RowNR2){
    double bufrow[size_y]= {0};
    for(int i=0;i<size_y;i++) {
        bufrow[i]=Matrix[RowNR1][i];
        }
    for(int i=0;i<size_y;i++) {
     Matrix[RowNR1][i]=Matrix[RowNR2][i];
     }
    for(int i=0;i<size_y;i++) {
        Matrix[RowNR2][i]=bufrow[i];
        }
    }
template <size_t size_y>
void ZeroRowsBelow(double Matrix[][size_y], int RowNR, int CollumnNR) {
    for(int i=0;i<size_y-RowNR-2;i++) {
        if(Matrix[RowNR][CollumnNR]!=0) {
            AddRow(Matrix,RowNR,i+1+RowNR,-Matrix[i+1+RowNR][CollumnNR]/Matrix[RowNR][CollumnNR]);
            }
        }
    }
template <size_t size_y>
void SolveMatrix(double Matrix[][size_y],int Width,int Height) {
    //Bring to Row-Echelon form
    for(int i=0;i<Height;i++) {
        ZeroRowsBelow(Matrix,i,i);
        }
    //Make Row-Echelon
    for(int i=0;i<Height;i++) {
        if(Matrix[i][i]!=0) {
            MultiplyRow(Matrix[i],Width,1/Matrix[i][i]);
        }
    }
    for(int i=0;i<Height;i++) {
        for(int j=0;j<i;j++) {
            if(Matrix[i][i]!=0) {
               AddRow(Matrix,i,j,-Matrix[j][i]/Matrix[i][i]);
                }
            }
        }
    }
template <size_t size_y>
bool IsRowEchelon(double Matrix[][size_y],int Width,int Height) {
    for(int i=0;i<Height;i++) {
        if(Matrix[i][i]!=1 or  Matrix[i][i]!=0) {
            return(0);
            }
        }
    return(1);
    }
template <size_t size_y>
void zerofunc(double Matrix[][size_y],int Width,int Height) {
    for(int i=0;i<Height;i++) {
        for(int j=0;j<Width;j++) {
            if(Matrix[i][j]<0.000000001 && Matrix[i][j]>-0.000000001) {
                Matrix[i][j]=0;
                }
            }
        }
    }
int main() {
srand(time(NULL));
//double Matrix[5][6]={{1,2,3,4,5,7},{7,6,7,8,9,1},{2,3,3,4,5,6},{7,8,9,1,5,2},{3,4,5,8,6,7}};
double Matrix[ARRAYSIZE][ARRAYSIZE+1]={0};
for(int i=0;i<ARRAYSIZE;i++) {
    for(int j=0;j<ARRAYSIZE+1;j++) {
        Matrix[i][j]=rand()%1000;
        }
    }
    


int Height=(sizeof(Matrix)/sizeof(*Matrix));
int Width=(sizeof(Matrix[0])/sizeof(*Matrix[0]));

//cout << (sizeof(Matrix)/sizeof(*Matrix)) << endl;
//cout << (sizeof(Matrix[0])/sizeof(*Matrix[0])) << endl;
PrintMatrix(Matrix,Width,Height);
cout <<endl;
do {
    SolveMatrix(Matrix,Width,Height);
}
while(IsRowEchelon(Matrix,Width,Height));
//make "almost zero > zero"
zerofunc(Matrix,Width,Height);
PrintMatrix(Matrix,Width,Height);
return(0);

}
