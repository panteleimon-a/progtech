#include <iostream>  
#include <algorithm>  
  
using namespace std;

class node {  
  public :   
    int data ;  
    node* left ;  
    node* right;} ;

class BST {  
      public:  
        void Preorder(node* root);  
        void Inorder(node* root);  
        void Postorder(node* root);  
        int min(node* root);  
        int maxV(node* root);  
        node* Getnewnode(int data);  
        node* insert(node* root,int data);  
        int height (node* root);  
        int getlevel(node *ptr,int val,int level);  
        int search(node* root,int data , int counter);  
    };  
  
void BST::Preorder(node* root)  
{  
  if(root==NULL)  
    return;  
  printf("%d ", root ->data);  
  Preorder(root->left);  
  Preorder(root->right);  
}  
void BST::Inorder(node* root)  
{  
  if(root==NULL)  
    return;  
  Inorder(root->left);  
  printf("%d " , root->data);  
  Inorder(root->right);  
}  
void BST::Postorder(node* root)  
{  
  if(root==NULL)  
    return;  
  Postorder(root->left);  
  Postorder(root->right);  
  printf("%d ", root->data);  
}  
node* BST::Getnewnode(int data)  
{  
  node* newnode= new node();  
  newnode->data=data;  
  newnode->left=NULL;  
  newnode->right=NULL;  
  return newnode;  
}  
node* BST::insert(node* root , int data)  
{  
  if(root==NULL)  
    root= Getnewnode(data);  
  if(data<root->data)  
    root->left=insert(root->left,data);  
  if(data>root->data)  
    root->right=insert(root->right,data);  
  return root;  
}  
int BST::min(node* root)  
{  
  node* temp=root;  
  while(temp->left!=NULL)  
  {  
    temp=temp->left;  
  }  
  return temp->data;  
}  
int BST::maxV(node* root)  
{  
  node* temp=root;  
  while(temp->right!=NULL)  
  {  
    temp=temp->right;  
  }  
  return temp->data;  
}  
int BST::height(node* root)  
{  
  if(root==NULL)  
  {return 0;  
  }  
  return 1+max(height(root->left),height(root->right));  
      }  
      int BST:: getlevel(node *ptr,int val,int level){  
      if (ptr==NULL)  
      return 0;  
      if (ptr->data==val)  
      return level ;  
      return getlevel(ptr->left , val , level+1) | getlevel(ptr->right, val, level+1);  
      }  
      int BST::search(node* root,int data , int counter){  
      if(root==NULL)  
      return 0;  
      if(data==root->data)  
      return counter;   
      else if (data<root->data)  
      {  
      return search(root->left,data,++counter);  
      }  
      else if(data>root->data)  
      {  
      return search(root->right,data,++counter);  
      }
      else{
        return 0;
      }
}  
int main ()   
{ int N,x,M,*value;  
  BST tree;  
  node* root=NULL;  
  scanf("%d" , &N);  
  for(int i=0; i<N; i++)  
  {  
    scanf("%d",&x);  
  root=tree.insert(root,x);  
}  
scanf("%d", &M);  
value=new(nothrow) int [M];  
for(int i=0; i<M; i++)  
{  
  scanf("%d" , &value[i]);  
}  
printf("%d\n",tree.height(root));  
printf("%d %d\n",tree.min(root),tree.maxV(root));  
for (int j=0; j<M; j++)  
{  
  if(j!=M-1)  
    printf("%d " , tree.search(root,value[j],1));  
  else printf("%d",tree.search(root,value[j],1));  
      }  
      printf("\n");  
      tree.Inorder(root);  
      printf("end\n");  
      tree.Preorder(root);  
      printf("end\n");  
      tree.Postorder(root);  
      printf("end\n");  
};