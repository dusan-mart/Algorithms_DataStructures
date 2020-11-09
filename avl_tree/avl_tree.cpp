#include <bits/stdc++.h>


struct node{
  int data;
  node* left;
  node* right;
};

#define MARGIN 2 //for pretty print
void print_pretty(node *root, int blanks);

void print_inorder(node *root);

int height(node *root);
int balance(node *root);

node* insert(node *root, int val);
node* rotate_left(node* curr);
node* rotate_right(node* curr);



int main(){

  node *root = nullptr;
  root = insert(root, 5);
  root = insert(root, 8);
  root = insert(root, 2);
  root = insert(root, 3);
  root = insert(root, 11);
  root = insert(root, 6);

  print_pretty(root, 0);
  std::cout << "\n\n\n";

  root = insert(root, 13);
  root = insert(root, 15);
  root = insert(root, 19);
  root = insert(root, 21);

  std::cout << "before adding >21:" << '\n';
  print_pretty(root, 0);
  std::cout << "\n\n\n";

  root = insert(root, 23);
  std::cout << "root changes after adding 23, right subtree full and height diff >1:" << '\n';
  print_pretty(root, 0);

  std::cout << "Inorder:" << '\n';
  print_inorder(root);
  std::cout << '\n';
  return 0;
}



void print_pretty(node *root, int blanks){
   if (!root)
      return;
   blanks += MARGIN;
   print_pretty(root->right, blanks);
   for (int i = MARGIN; i < blanks; i++)
      std::cout << '\t';
   std::cout << root->data << '\n';
   print_pretty(root->left, blanks);
}


void print_inorder(node *root)
{
  if(!root)
  {
    return;
  }

  print_inorder(root->left);
  std::cout << root->data << "   ";
  print_inorder(root->right);
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

  int bal = balance(curr); //checking balance for all ancestors

  // 4 cases
  //left left
  if((bal > 1) && (balance(curr->left) >= 0))
    return rotate_right(curr);

  //left right
  if((bal > 1) && (balance(curr->left) < 0))
  {
    curr->left = rotate_left(curr->left);
    return rotate_right(curr);
  }

  //right left
  if((bal < -1) && (balance(curr->right) >= 0))
  {
    curr->right = rotate_right(curr->left);
    return rotate_left(curr);
  }

  //right right
  if((bal < -1) && (balance(curr->right) < 0))
    return rotate_left(curr);

  return curr;

}


node* rotate_left(node* curr)
{
  node *tmp = curr->right;
  curr->right = tmp->left;
  tmp->left = curr;

  return tmp;

}
node* rotate_right(node* curr)
{
  node *tmp = curr->left;
  curr->left = tmp->right;
  tmp->right = curr;

  return tmp;
}
