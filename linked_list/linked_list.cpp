#include <bits/stdc++.h>


class linked_list{
public:
  linked_list();
  linked_list(std::initializer_list<int> vals);

  ~linked_list();
  linked_list(const linked_list &other);
  linked_list& operator =(const linked_list other);
  linked_list(linked_list &&other);
  linked_list& operator =(linked_list &&other);

  int operator [](size_t index) const;
  friend void swap(linked_list &first, linked_list &second);

  void push_front(int val);
  int pop_front();

  void push_back(int val);
  int pop_back();

  void remove(int val);
  size_t get_size() const;
  void print();
private:
  struct node{
    node(int val = 0, std::unique_ptr<node> && p = nullptr)
      : data(val), next(std::move(p)){}
    int data;
    std::unique_ptr<node> next;
  };

  std::unique_ptr<node> head;
  size_t size = 0;

  node* at(size_t index) const;
};


int main() {

  linked_list ll;//viable ll{}, !ll()-sees as funcdef
  ll.push_back(5);
  ll.push_back(6);
  ll.push_front(7);
  linked_list ll1;

  ll1 = ll;
  std::cout << "copy assigment:\n";
  ll1.print();

  linked_list l3{1,2,3,4,5};
  std::cout << "list with init list:\n";
  l3.print();

  l3.remove(4);
  l3.pop_front();
  std::cout << "list after remove and pop:\n";
  l3.print();

  return 0;
}

linked_list::linked_list()
{
  head = nullptr;
}


linked_list::linked_list(std::initializer_list<int> vals)
{
  for(auto it = vals.begin(); it != vals.end(); ++it)
  {
    push_back(*it);
  }
}


linked_list::~linked_list()
{
  while(head)
  {
    auto tmp = std::move(head);
    head = std::move(tmp->next);
    size--;
  }
}


linked_list::linked_list(const linked_list &other)
{
  size_t s = other.get_size();
  for(size_t i = 0; i < s; ++i)
    push_back(other[i]);


}


linked_list& linked_list::operator =(linked_list other)//taken by value, possible optimization
{                                                     // !!!RVO!!!
    swap(*this, other);
    return *this;
}


linked_list::linked_list(linked_list &&other)
{
  swap(*this, other);
}


linked_list& linked_list::operator =(linked_list &&other)
{
  swap(*this, other);
  return *this;
}


int linked_list::operator [](size_t index) const
{
  return at(index)->data;
}


void swap(linked_list &first, linked_list &second){
  using std::swap; //useless here, but good practice
                  //more details: questions/3279543 on SO

  swap(first.head, second.head);
  swap(first.size, second.size);
}


void linked_list::push_front(int val)
{
  auto tmp = std::make_unique<node>(val, std::move(head));
  head = std::move(tmp);
  size++;
}


int linked_list::pop_front()
{
  if(head)
  {
    auto tmp = std::move(head);
    head = std::move(tmp->next);
    size--;
    return tmp->data;
  }
  else
  {
    std::cout << "empty list" << '\n';
    return 0;
  }
}


void linked_list::push_back(int val)
{
  auto tmp = std::make_unique<node>(val);
  if(head)
  {
    auto i = head.get();
    while(i->next)
    {
      i = i->next.get();
    }
    i->next = std::move(tmp);
  }
  else//empty list
  {
    head = std::move(tmp);
  }
  size++;
}


int linked_list::pop_back()
{
  if(head)
  {
    auto tmp = head.get();
    for(size_t i = 0;i < size-1; ++i)
    {
      tmp = tmp->next.get();
    }

    auto old_back = std::move(tmp->next);
    tmp->next = nullptr;
    size--;
    return old_back->data;
  }
  else//empty list
  {
    std::cout << "empty list" << '\n';
    return 0;
  }
}


linked_list::node* linked_list::at(size_t index) const
{
  if(!head)
    return nullptr;

  auto tmp = head.get();

  for(size_t i = 0; i < index; ++i)
  {
    tmp = tmp->next.get();
    if(!tmp)
      return nullptr;
  }
  return tmp;
}


void linked_list::remove(int val)
{
  auto tmp = head.get();
  while((tmp->next != nullptr) && (tmp->next->data != val))
  {
    tmp = tmp->next.get();
  }
  if(tmp->next)
  {
    auto for_del = std::move(tmp->next);
    tmp->next = std::move(for_del->next);
    size--;
  }
  else
  {
    std::cout << "value not found\n";
  }
  return;
}


size_t linked_list::get_size() const
{
  return size;
}

void linked_list::print()
{
  for(size_t i = 0; i < size; ++i)
  {
    std::cout << at(i)->data << "\n";
  }
}
