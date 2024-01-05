// C++ program to find minimum value node in binary search
// Tree.

#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct node {
	int data;
	struct node* left;
	struct node* right;
};

/* Helper function that allocates a new node
with the given data and NULL left and right
pointers. */
struct node* newNode(int data)
{
	struct node* node
		= (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return (node);
}

/* Give a binary search tree and a number,
inserts a new node with the given number in
the correct place in the tree. Returns the new
root pointer which the caller should then use
(the standard trick to avoid using reference
parameters). */
struct node* insert(struct node* node, int data)
{
	/* 1. If the tree is empty, return a new,
		single node */
	if (node == NULL){
		node=newNode(data);
		return (node=newNode(data));}
	else {
		/* 2. Otherwise, recur down the tree */
		if (data <= node->data)
			node->left = insert(node->left, data);
		else
			node->right = insert(node->right, data);

		/* return the (unchanged) node pointer */
		return node;
	}
}

/* Given a non-empty binary search tree,
inorder traversal for the tree is stored in
the vector sortedInorder.
Inorder is LEFT,ROOT,RIGHT*/
void inorder(struct node* node, vector<int>& sortedInorder)
{
	if (node == NULL)
		return;
	/* first recur on left child */
	inorder(node->left, sortedInorder);

	/* then insert the data of node */
	sortedInorder.push_back(node->data);

	/* now recur on right child */
	inorder(node->right, sortedInorder);
};

int noSmaller(node root, int k)
{
	vector<int> sortedInorder;
	inorder(
		root,
		sortedInorder);
    while (k>sortedInorder[0]){
        sortedInorder.pop_back();
    };
    return (sortedInorder[0]);
};
