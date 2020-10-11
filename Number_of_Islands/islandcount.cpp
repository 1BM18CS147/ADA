#include<bits/stdc++.h>

using namespace std;

class DisSets
{
vector<int> rank,parent;
int n;

public:
DisSets(int n)
{
rank.resize(n);
parent.resize(n);
this->n=n;

makeSet();
}


void makeSet()
{
for(int i=0;i<n;i++)
{
parent[i]=i;
}
}

int find(int x)
{
if(parent[x]!=x)
{
return find(parent[x]);
}
return x;
}


void Union(int x,int y)
{
int xroot =find(x);
int yroot=find(y);

if(xroot==yroot)
{
return;
}


if(rank[xroot]<rank[yroot])
{
parent[xroot]=yroot;
}

else if(rank[yroot]<rank[xroot])
{
parent[yroot]=xroot;
}

else
{
parent[xroot]=yroot;
rank[yroot]=rank[yroot]+1;
}
}
};


int IslandCount(vector<vector<int>>M)
{

int n=M.size();
int m=M[0].size();


DisSets *islands=new DisSets(n*m);


for(int i=0;i<n;i++)
{
for(int j=0;i<m;i++)
{
if(M[i][j]==0)
continue;


if (i + 1 < n && M[i + 1][i] == 1) 
islands->Union(i * (m) + j,(i + 1) * (m) + j); 
if (i - 1 >= 0 && M[i - 1][j] == 1) 
islands->Union(i * (m) + j,(i - 1) * (m) + j); 
if (j + 1 < m && M[i][j + 1] == 1) 
islands->Union(i * (m) + j,(i) * (m) + j + 1); 
if (j - 1 >= 0 && M[i][j - 1] == 1) 
islands->Union(i * (m) + j,(i) * (m) + j - 1); 
if (i + 1 < n && j + 1 < m && M[i + 1][j + 1] == 1) 
islands->Union(i * (m) + j,(i + 1) * (m) + j + 1); 
if (i + 1 < n && j - 1 >= 0 &&M[i + 1][j - 1] == 1) 
islands->Union(i * m + j, (i + 1) * (m) + j - 1); 
if (i - 1 >= 0 && j + 1 < m && M[i - 1][j + 1] == 1) 
islands->Union(i * m + j,(i - 1) * m + j + 1); 
if (i - 1 >= 0 && j - 1 >= 0 &&M[i - 1][j - 1] == 1) 
islands->Union(i * m + j,(i - 1) * m + j - 1); 
} 
} 


int *freq = new int[n * m]; 
    int num = 0; 
    for (int i = 0; i < n; i++) 
    { 
        for (int j = 0; j < m; j++) 
        { 
            if (M[i][j] == 1) 
            { 
                int x = islands->find(i * m + j); 
  
                if (freq[x] == 0) 
                { 
                    num++; 
                    freq[x]++; 
                } 
  
                else
                    freq[x]++; 
            } 
        } 
    } 
    return num; 
} 
  
 
int main() 
{ 
/*
vector<vector<int>>a = {{1, 1, 0, 0, 0}, 
                            {0, 1, 0, 0, 1}, 
                            {1, 0, 0, 1, 1}, 
                            {0, 0, 0, 0, 0}, 
                            {1, 0, 1, 0, 1}}; 
    cout << "Number of Islands is: " 
         <<IslandCount(a) << endl; 

*/
int n,m,temp;
vector<vector<int>>a;
cout<<"Enter Row size\n";
cin>>n;
cout<<"Enter Column size\n";
cin>>m;
cout<<"Enter boolean matrix\n";

for (int i=0;i<n;i++)
{
    vector<int> row;
    for (int j = 0; j < n; j++) 
    {  
        cin >>temp;
        row.push_back(temp); 
    }  
    a.push_back(row);
}
cout << "Number of Islands is: " <<IslandCount(a) << endl;
return 0;
}
