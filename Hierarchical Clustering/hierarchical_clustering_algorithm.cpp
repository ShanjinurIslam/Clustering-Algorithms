#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double calculate_distance(vector<vector<double> > le_values,int m1,int m2,int n)
{
    double sum = 0;
    for(int i=0;i<n;i++){
        sum += pow((le_values[m1][i] - le_values[m2][i]), 2);
    }
    return sqrt(sum);
}

void printGraph(vector<vector<int> > graph){
    for(int i=0;i<graph.size();i++){
        cout << i << ": ";
        for (int j = 0; j < graph[i].size(); j++)
        {
            cout << graph[i][j] << " ";
        }
        cout<<endl;
    }
}

void printExpressionValues(vector<vector<double> > le_values)
{
    for (int i = 0; i < le_values.size(); i++)
    {
        cout << i <<": " ;
        for (int j = 0; j < le_values[i].size(); j++)
        {
            cout << le_values[i][j] <<" ";
        }
        cout<<endl;
    }
}

void printDistanceMatrix(vector<vector<double> > distance_matrix)
{
    for (int i = 0; i < distance_matrix.size(); i++)
    {
        for (int j = 0; j < distance_matrix[i].size(); j++)
        {
            cout << distance_matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    int m,n;
    double value;
    cin>>m>>n;
    vector<vector<double> > le_values(m);
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>value;
            le_values[i].push_back(value);
        }
    }
    

    int number_of_genes = m ;

    vector<vector<double> > distance_matrix(m);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i != j)
            {
                distance_matrix[i].push_back(calculate_distance(le_values, i, j, n));
            }
            else
            {
                distance_matrix[i].push_back(0);
            }
        }
    }
    

    vector<vector<int> > graph(m);
    int number_of_clusters = m;
    while(number_of_clusters>2){

        double min = 1e10;
        int c1,c2 ;
       
        for (int i = 0; i < distance_matrix.size(); i++)
        {
            for (int j = 0; j < distance_matrix.size(); j++)
            {
                if (i != j && distance_matrix[i][j] != -1)
                {
                    if(distance_matrix[i][j]<min){
                        min = distance_matrix[i][j];
                        c1 = i ;
                        c2 = j ;
                    }
                }
            }
        }
        cout<<c1<<" "<<c2<<endl;
        graph[c1].push_back(c2);
        graph[c2].push_back(c1);
        vector<int> c ;
        c.push_back(c1);
        c.push_back(c2);
        graph.push_back(c);
        graph[c1].push_back(graph.size()-1);
        graph[c2].push_back(graph.size()-1);
        //printGraph(graph);
        vector<double> gene_values ;
        for(int i=0;i<n;i++){
            gene_values.push_back(le_values[c1][i]);
            gene_values[i] += le_values[c2][i];
        }
        for (int i = 0; i < n; i++)
        {
            gene_values[i] /= 2;
        }
        le_values.push_back(gene_values);
        //column calculation
        for (int i = 0; i < le_values.size()-1; i++)
        {
            distance_matrix[i].push_back(calculate_distance(le_values, i, le_values.size()-1,n));
        }

        //row calculation
        vector<double> tmp;
        
        for (int i = 0; i < le_values.size() ; i++)
        {
            tmp.push_back(calculate_distance(le_values, le_values.size()-1, i, n));
        }
        distance_matrix.push_back(tmp);
        int last = distance_matrix.size()-1 ;
        for (int i = 0; i < le_values.size(); i++)
        {
            if(distance_matrix[i][0]==-1){
                distance_matrix[last][i] = -1;
                distance_matrix[i][last] = -1;
            }
        }
        //printDistanceMatrix(distance_matrix);
        cout<<endl;
        for (int i = 0; i < distance_matrix[c1].size();i++){
            distance_matrix[c1][i] = -1 ;
        }
        for (int i = 0; i < distance_matrix[c2].size(); i++)
        {
            distance_matrix[c2][i] = -1;
        }
        for (int i = 0; i < distance_matrix.size(); i++)
        {
            distance_matrix[i][c1] = -1;
        }
        for (int i = 0; i < distance_matrix.size(); i++)
        {
            distance_matrix[i][c2] = -1;
        }
        printDistanceMatrix(distance_matrix);
        
        cout<<endl;
        number_of_clusters--;
    }


    cout<<"Final out graph:: "<<endl;
    printGraph(graph);

    return 0;
}
