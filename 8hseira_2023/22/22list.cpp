#include<iostream>
#include<cstdio>
#include"21list.hpp"
using namespace std;

int list::searchMF(int x){  
    int k=2;  
    node *p,*q ;  
    p=head;  
    if(p->info==x)  
    return 1;  
    q=p->next;  
    while(q!=nullptr){  
    if(q->info!=x){  
        p=p->next;  
        q=p->next;  
        k++;  
    }  
    else {  
        p->next=q->next;  
        q->next=head;  
        head=q;  
        return k;  
    }  
    }  
    return 0;  
}  
int main(){  
    list l;  
    int N,M,kN,x,X,sum=0;  
    cin >> N;  
    for(int i=0; i<N; i++) {  
    cin>>kN;  
    cin >>x;  
    l.add(kN,x);}  
    cin>>M;  
    for(int j=0; j<M; j++){  
    cin>>X;  
    sum+=l.searchMF(X);  
    }  
    cout<<sum<<endl;  
}