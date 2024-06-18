#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Passenger{
    int age;
    string date;
    float weight;
};

void print2D(Passenger** p, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Passenger tmp = p[i][j];
            cout << tmp.weight << ' ';
        }
        cout << endl;
    }
}

Passenger*** readFile(string file_name, int &p, int &m, int &n)
{
    ifstream fi;
    fi.open(file_name);
    if(!fi.is_open()) return NULL;

    string line_info;

    getline(fi, line_info, ' ');
    p = stoi(line_info);

    getline(fi, line_info, ' ');
    m = stoi(line_info);

    getline(fi, line_info, ' ');
    n = stoi(line_info);

    Passenger*** pas;
    pas = new Passenger**[p];
    for(int i = 0; i < p; i++)
    {
        pas[i] = new Passenger*[m];
        for(int j = 0; j < m; j++)
        {
            pas[i][j] = new Passenger[n];
        }
    }


    for(int k = 0; k < p; k++)
    {
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                Passenger tmp;

                getline(fi, line_info, ' ');
                tmp.age = stoi(line_info);

                getline(fi, tmp.date, ' ');

                getline(fi, line_info, '\n');
                tmp.weight = stof(line_info);

                pas[k][i][j] = tmp;
            }
        }
    }

     fi.close();
    return pas;

}

void print3D(Passenger*** P, int p, int m, int n)
{
    for(int k = 0; k < p; k++)
    {
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cout << P[k][i][j].age << ' ';
            }
            cout << endl;
        }
        cout << endl << "--------------" << endl;
    }
}

float SumOfMaxtrix(Passenger***P , int x, int y, int k, int i, int j)
{
    float sum = 0;
    for(int a = i; a < x + i; a++)
    {
        for(int b = j; b < y + j; b++)
        {
            sum += P[k][a][b].weight;
        }
    }
    return sum;
}

Passenger** findMinWeight(Passenger*** P, int p, int m, int n, int x, int y)
{
    if(x > m || y > n) return NULL;
    Passenger** subP;
    subP = new Passenger**[p];
    for(int i = 0; i < p; i++)
    {
        subP[i] = new Passenger*[x];
        for(int j = 0; j < x; j++)
        {
            subP[i][j] = new Passenger[y];
        }
    }

    int index_i = 0;
    int index_j = 0;
    int index_k = 0;
    float minWeight = 10000;

    for(int k = 0; k < p; k++)
    {
        for(int i = 0; i < m - x + 1; i++)
        {
            for(int j = 0; j < n - y + 1; j++)
            {
                float sumWeight = SumOfMaxtrix(P, x, y, k, i , j);
                if(sumWeight < minWeight)
                {
                    minWeight = sumWeight;
                    index_i = i;
                    index_j = j;
                    index_k = k;
                }
            }
        }
    }


    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            subP[i][j] = P[index_k][i+index_i][j+index_j];
        }
    }
    return subP;
}


int main()
{
    Passenger*** pas;
    int p, m, n;
    pas = readFile("F:\\Source CodeBlock\\ReiewTest1\\ReviewTest1\\train.txt", p, m ,n);    
    Passenger** subP;
    subP = findMinWeight(pas, p, m, n, 2, 2);
    print2D(subP, 2, 2);

    return 0;
}
