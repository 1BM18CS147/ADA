#include<bits/stdc++.h>

using namespace std;

vector <int> num;
int uniq(int i)
{
bool digit[10]={false};
int n=i;
while(i)
{
 if(digit[i%10]==false) 
 {
  
  digit[i%10]=true;
  i=i/10;
 }
 else 
 {
  return -2;
 }

}
return n;
}

int main()
{
int L,R,n;
cin>>L>>R;
for(int i=L;i<=R;i++)
{
n=uniq(i);
if(n==-2)continue;
cout<<n<<"\t";
}
cout<<"\n";
return 0;
}
