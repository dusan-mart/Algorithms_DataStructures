#include <bits/stdc++.h>

#define ALPHABET 26

struct node{
  node* letter[ALPHABET];
  bool end_of_word;
};


node* new_node();
void insert(node* curr, std::string &str);
bool search(node* head, std::string &str);
void print_inorder(node *head, std::string str, int level);
node *remove(node *head, std::string str, int level = 0);
bool is_empty_node(node *curr);


int main(){

  node* head = new_node();
  int ind = 1;

  while(ind)
  {
    std::cout << "0. stop\n1. insert\n2. print\n3. remove\n4. search\n\n";

    std::cout << "pick action: ";
    std::cin >> ind;
    std::cout << '\n';

    if(ind == 1)
    {
      std::cout << "word to insert into trie:" << '\n';

      std::string str;
      std::cin >> str;

      insert(head, str);
      std::cout << '\n';
    }

    if(ind == 2)
    {
      std::cout << "-------------Lexicon--------------" << '\n';

      std::string str;
      print_inorder(head, str, 0);

      std::cout << "----------------------------------" << "\n\n";
    }
    if(ind == 3)
    {
      std::cout << "word to remove from trie:" << '\n';

      std::string str;
      std::cin >> str;

      if(!search(head, str))
        std::cout << '\n' <<"!!! word not in lexicon !!!" << "\n\n";
      head = remove(head, str);
      if(!head)
        head = new_node();
    }

    if(ind == 4)
    {
      std::cout << "word to search for in trie:" << '\n';

      std::string str;
      std::cin >> str;

      if(search(head, str))
        std::cout << "found" << '\n';
      else
        std::cout << "not found" << '\n';
    }
  }//while

  return 0;

}



node* new_node()
{
  node *tmp = new node;
  tmp->end_of_word = false;
  for(int i = 0; i < ALPHABET; ++i)
    tmp->letter[i] = nullptr;

  return tmp;
}

void insert(node* curr, std::string &str)
{

  for(unsigned i = 0; i < str.length(); ++i)
  {
    int index = str[i] - 'a';

    // If path doesn't exist
    if(!curr->letter[index])
    {
      curr->letter[index] = new_node();
    }
    curr = curr->letter[index];
  }

  curr->end_of_word = true;
}


bool search(node* head, std::string &str)
{
  node* curr = head;
  //check if path exists
  for(unsigned i = 0; i < str.length(); ++i)
  {
    int index = str[i] - 'a';

    if(curr->letter[index])
      curr = curr->letter[index];
    else//if it doesn't, word not present
      return false;
  }

  return (curr != nullptr)&&(curr->end_of_word);
}


void print_inorder(node *curr, std::string str, int level)
{
  if(curr->end_of_word)
    std::cout << str << '\n';

  for(unsigned i = 0; i < ALPHABET; ++i)
  {
    if(curr->letter[i])
    {
      str+= i + 'a';
      print_inorder(curr->letter[i], str, level+1);
      str.pop_back(); //clears old character from same level
    }
  }

}


node *remove(node *curr, std::string str, int level)
{

  if(!curr)
    return nullptr;

  if(static_cast<int>(str.length()) == level)
  {
    if(curr->end_of_word)
      curr->end_of_word = false;

    if(is_empty_node(curr))
    {
      delete curr;
      curr = nullptr;
    }

    return curr;
  }

  //if not last character, go further
  int index = str[level] - 'a';
  curr->letter[index] = remove(curr->letter[index], str, level + 1);

  //backtrack check if any of previous characters need to be deleted
  //if deleted word is only on current path
  if((curr->end_of_word == false) && is_empty_node(curr))
  {
    delete curr;
    curr = nullptr;
  }
  return curr;
}


bool is_empty_node(node *curr)
{
  bool ind = false;
  for(int i = 0; i < ALPHABET; ++i)
    if(curr->letter[i] != nullptr)
      ind = true;

  return !ind;
}
