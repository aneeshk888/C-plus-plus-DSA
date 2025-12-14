#include <bits/stdc++.h>
using namespace std;

int PalindromeNumber(int n){
    int rev=0,temp=n;
    while(temp!=0){
        rev=(rev*10)+(temp%10);
        temp/=10;
    }
    return rev;

    if(rev==n){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    int n=8008;
    if(PalindromeNumber(n)){
        cout<<n<<" is a palindrome number."<<endl;
    }
    else{
        cout<<n<<" is not a palindrome number."<<endl;
    }
    return 0;
}