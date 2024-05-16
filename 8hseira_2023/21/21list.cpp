#include<iostream>
#include<cstdio>
#include<21list.hpp>

using namespace std;



    class list {

public:

 list ():front(nullptr), rear(nullptr){
};                    
 bool empty (){
    return front == NULL;
};            
 int size (){
    int size = 0;
    node *n=front;

    if(front == NULL) return size;
    else
    {
        do{
            size++;
            n = n->next;
        }while(n != NULL);
    }
    return size;
};              
 void add (int k, int x){
    node *n = new node, *p;
    n->info = x;

    if(k == 1)
    {
        if(front == NULL)
        {
            front = n;
            rear = n;
        }
        else
        {
            n->next = front;
            front = n;
        }
        
    }
    else
    {   
        p = front;
        for(int i = 1; i < k-1; i++)
        {
           p = p->next; 
        }

        if(p == rear)
        {
            p->next = n;
            rear = n;
        }
        else
        {
            n->next = p->next;
            p->next = n;
        }
        
        
        
    }
};  
 int get (int k){
    node *n;
    int value;
    n = front;

    if(k == 1)
    {   
        value = n->info;
        return value;
    }
    else
    {
        for(int i = 1; i < k; i++)
        {
            n = n->next;
        }
        value = n->info;
        return value;
    }
    
};          
 void remove (int k){
    node *n, *p;
    n = front;
    if(k == 1)
    {
        front = front->next;
        delete n;
    }
    else
    {
        
        for(int i = 1; i < k; i++)
        {
            p = n;
            n = n->next;
        }

        if(n == rear)
        {
            p->next = NULL;
            rear = p;
            delete n;
        }
        else
        {
            p->next = n->next;
            delete n;
        }
        
    }
    
};      


 private:

 node *front, *rear;
};


int main()
{
    int n, k, x;
    list l;

    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> k >> x;
        l.add(k,x);
    }

    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> k;
        l.remove(k);
    }

    cin >> k;

    cout << l.size() << " " << l.get(k) << endl;
    
}