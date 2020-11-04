#include <bits/stdc++.h>


struct node{
  int data;
  node* left;
  node* right;
};

node* insert(node *root);
int height(node *root);
int balance(node *root);

int main(){



  return 0;
}

int height(node *root)
{
  if(!root)
    return -1;
  return std::max(height(root->left),height(root->right)) + 1;
}

int balance(node *root)
{
  return height(root->left) - height(root->right);
}

node* insert(node *curr, int val)
{
  if(!curr)
  {
    node *tmp = new node;
    tmp->data = val;
    tmp->right = nullptr;
    tmp->left = nullptr;
    return tmp;
  }

  if(curr->data > val)
    curr->left = insert(curr->left, val);
  else
    curr->right = insert(curr->right, val);

  int bal = balance(curr);
  if(abs(bal) < 1)
    return curr;

  if((bal > 1) && (balance(curr->left) >= 0))
    return rotate_right(curr);

  if((bal > 1) && (balance(curr->left) < 0))
  {
    curr->left = rotate_left(curr->left);
    return rotate_right(curr);
  }

  if((bal < -1) && (balance(curr->right) >= 0))
  {
    curr->right = rotate_right(curr->left);
    return rotate_left(curr);
  }

  if((bal < -1) && (balance(curr->right) < 0))
    return rotate_left(curr);
}
