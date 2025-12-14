#include<bits/stdc++.h>
using namespace std;

int countDigits(int n){
    if(n==0) return 1;
    int count=0;
    while(n!=0){
        n/=10;
        ++count;
    }
    return count;
}

int main(){
    int n=12345;
    cout<<"Number of digits in "<<n<<" is "<<countDigits(n)<<endl;
    return 0;
}