#include <bits/stdc++.h>

struct node{
  int data;
  node *left;
  node *right;
  node *parent;
  enum {red = 0, black = 1} r_b;
};

node* new_node(int &data);
node* new_node(int &&data);

node* insert(node *curr, int data);
void check_uncle_red(node** root,node* curr);
void check_uncle_black(node** root, node* curr);
node* rotate_right(node* curr);
node* rotate_left(node* curr);

#define MARGIN 2 //for pretty print
void print_pretty(node *root, int blanks);
void print_inorder(node *root);

int main(){

  //to check resulting trees:
  //https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
  // theres a bug for <0 numbers on www.cs.usfca.edu
  node *root = nullptr;
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 15);
  root = insert(root, 11);
  root = insert(root, 25);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 0);

  print_pretty(root, 0);
  std::cout << "\n\n\n";
  root = insert(root, -1);

  root = insert(root, -3);
  root = insert(root, -4);
  root = insert(root, 8);
  root = insert(root, -5);

  root = insert(root, 9);
  print_pretty(root, 0);
  std::cout << "\n\n\n";

  //print_pretty(root, 0);

  print_inorder(root);
  return 0;
}


node* new_node(int &data)
{
  node *tmp = new node;
  tmp->data = data;
  tmp->left = nullptr;
  tmp->right = nullptr;
  tmp->parent = nullptr;
  tmp->r_b = node::red;

  return tmp;
}

node* new_node(int &&data)
{
  node *tmp = new node;
  tmp->data = std::move(data);
  tmp->left = nullptr;
  tmp->right = nullptr;
  tmp->parent = nullptr;
  tmp->r_b = node::red;

  return tmp;
}

void print_inorder(node *root)
{
  if(!root)
    return;

  print_inorder(root->left);
  std::cout << root->data << " ";
  print_inorder(root->right);
}

void print_pretty(node *root, int blanks){
   if (!root)
      return;
   blanks += MARGIN;
   print_pretty(root->right, blanks);
   for (int i = MARGIN; i < blanks; i++)
      std::cout << '\t';

   std::cout << root->data << "[" << (root->r_b? "black" : "red") << "]" << '\n';
   print_pretty(root->left, blanks);
}

/*
        x             right r       y
      /   \         ------>       /   \
     y     T2         left r     z     x
    / \             <--------         / \
   z   T1                            T1  T2
*/

node* rotate_left(node* curr)
{
  node *tmp = curr->right;
  curr->right = tmp->left;

  if(tmp->left != nullptr)
    tmp->left->parent = curr;

  tmp->left = curr;
  tmp->parent = curr->parent;
  curr->parent = tmp;

  return tmp;
}

node* rotate_right(node* curr)
{
  node *tmp = curr->left;
  curr->left = tmp->right;

  if(tmp->right != nullptr)
    tmp->right->parent  = curr;

  tmp->right = curr;
  tmp->parent = curr->parent;
  curr->parent = tmp;

  return tmp;
}

void check_uncle_red(node** root,node* curr)
{
  //root is always black
  if(curr == *root)
  {
    curr->r_b = node::black;
    return;
  }

  node *parent = curr->parent;
  if((parent->r_b == node::black)|| (curr->r_b == node::black))
    return;

  if(parent == *root)
  {
    parent->r_b = node::black;
    return;
  }
  node *g_parent = parent->parent;
  node* uncle;

  uncle = (g_parent->left == parent)? g_parent->right : g_parent->left;

  //2 cases, uncle red or black
  //nullptrs are black
  if((uncle!= nullptr) && (uncle->r_b == node::red))
  {
    //recoloring, parent and uncle->black, g_parent->red
    g_parent->r_b = node::red;
    g_parent->left->r_b = node::black;
    g_parent->right->r_b = node::black;

    //go up and check g_parent
    check_uncle_red(root,g_parent);
  }
  else
  {
    check_uncle_black(root, curr);
    return;
  }
}
void check_uncle_black(node** root, node* curr)
{
  if(curr == *root)
  {
    curr->r_b = node::black;
    return;
  }

  node *parent = curr->parent;

  if((parent->r_b == node::black) || (curr->r_b == node::black))
    return;

  if(parent == *root)
  {
    parent->r_b = node::black;
    return;
  }


  node *g_parent = parent->parent;
  node* uncle;

  uncle = (g_parent->left == parent)? g_parent->right : g_parent->left;

  if(uncle != nullptr)
    if(uncle->r_b == node::red)
    {
      check_uncle_red(root, curr);
      return;
    }

  //left subtree
  if(g_parent->left == parent)
  {
    //check which side is subtree
    bool ind;
    if(g_parent->parent)
      ind = (g_parent->parent->left == g_parent);

    //left left case(similar to AVL)
    //right rotate g_parent, recolor original g_parent and parent
    if(parent->left == curr)
    {
      g_parent->r_b = node::red;
      parent->r_b = node::black;

      // todo: this whole segment could be put inside rotates???
      //
      if(g_parent == *root)
        *root = rotate_right(g_parent);
      else
      {
        if(ind)
          g_parent->parent->left = rotate_right(g_parent);
        else
          g_parent->parent->right = rotate_right(g_parent);
      }
    }
    //left right
    //left rotate parent, left left case then
    else
    {
      g_parent->r_b = node::red;
      curr->r_b = node::black;

      bool ind;
      if(g_parent->parent)
        ind = (g_parent->parent->left == g_parent);


      if(g_parent->left == parent)
        g_parent->left = rotate_left(parent);
      else
        g_parent->right = rotate_left(parent);
      if(g_parent == *root)
        *root = rotate_right(g_parent);
      else
      {
        if(ind)
          g_parent->parent->left = rotate_right(g_parent);
        else
          g_parent->parent->right = rotate_right(g_parent);
      }
    }
  }
  else//right cases
  {

    bool ind;
    if(g_parent->parent)//make sure g_p is not root
      ind = (g_parent->parent->left == g_parent);

    //right right case
    //left rotate g_p, recolor parent and g_parent
    if(parent->right == curr)
    {
      g_parent->r_b = node::red;
      parent->r_b = node::black;

      if(g_parent == *root)
        *root = rotate_left(g_parent);
      else
      {
        if(ind)
          g_parent->parent->left = rotate_left(g_parent);
        else
          g_parent->parent->right = rotate_left(g_parent);
      }
    }
    else  //right left
    {

      bool ind;
      if(g_parent->parent)//make sure g_p is not root
        ind = (g_parent->parent->left == g_parent);

      g_parent->r_b = node::red;
      curr->r_b = node::black;

      if(g_parent->left == parent)
        g_parent->left = rotate_right(parent);
      else
        g_parent->right = rotate_right(parent);
      if(g_parent == *root)
        *root = rotate_left(g_parent);
      else
      {
        if(ind)
          g_parent->parent->left = rotate_left(g_parent);
        else
          g_parent->parent->right = rotate_left(g_parent);
      }
    }

  }
  check_uncle_black(root, curr->parent);
}
node* insert(node *root, int data)
{
  node* curr = root;
  node* parent = nullptr;
  node* g_parent = nullptr;

  //empty tree
  if(!root)
  {
    node* tmp = new_node(data);
    tmp->r_b = node::black;
    return tmp;
  }

  //classic bst insert
  while(1)
  {
    if(curr->data > data)
    {
      if(curr->left)
      {
        curr = curr->left;
      }
      else
      {
        curr->left = new_node(data);
        curr->left->parent = curr;
        curr = curr->left;
        break;
      }
    }
    if(curr->data < data)
    {
      if(curr->right)
      {
        curr = curr->right;
      }
      else
      {
        curr->right = new_node(data);
        curr->right->parent = curr;
        curr = curr->right;
        break;
      }
    }
    }

    if(curr->parent->r_b == node::black) //parent black, thats ok
      return root;

    g_parent = curr->parent->parent;
    parent = curr->parent;
    node* uncle = (g_parent->left == parent)? g_parent->right : g_parent->left;

    if((uncle != nullptr) && (uncle->r_b == node::red))//if uncle red
    {
      check_uncle_red(&root, curr);
      return root;
    }
    else
    {
      check_uncle_black(&root, curr);
    }
    return root;
}
