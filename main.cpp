#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double calculate_distance(double **le_values,int m1,int m2,int n)
{
    double sum = 0;
    for(int i=0;i<n;i++){
        sum += pow((le_values[m1][i] - le_values[m2][i]), 2);
    }
    return sqrt(sum);
}

int main()
{
    double **le_values;
    int m,n;
    double value;
    cin>>m>>n;
    le_values = new double*[m];
    for(int i=0;i<m;i++){
        le_values[i] = new double[n];
    }
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>value;
            le_values[i][j] = value;
        }
    }
    

    int number_of_genes = m ;
    double **distance_matrix;
    distance_matrix = new double *[m];
    for (int i = 0; i < m; i++)
    {
        distance_matrix[i] = new double[m];
        
    }

    //calculation of distance_matrix

    for (int i = 0; i < m; i++){
        for(int j=0;j<m;j++){
            if(i!=j){
                distance_matrix[i][j]  = calculate_distance(le_values, i, j, n);
            }
            else{
                distance_matrix[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout<<distance_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
