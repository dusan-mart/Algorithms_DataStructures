#include <bits/stdc++.h>


int kmp(std::string text, std::string pattern);
void make_lps(std::string pattern,std::vector<int> &lps);



int main(){

  std::string text;
  std::string pattern;

  std::cout << "enter text:" << '\n';
  getline(std::cin, text);

  std::cout << "enter pattern:" << '\n';
  getline(std::cin, pattern);

  int n = kmp(text, pattern);
  if(n != -1)
  {
    std::cout << "pattern found starting from index: " << n << '\n';
  }
  else
  {
    std::cout << "pattern not found" << '\n';
  }
  return 0;
}



int kmp(std::string text, std::string pattern)
{
  std::vector<int> lps;
  make_lps(pattern, lps);

  int i = 0;
  int j = -1;
  while(i < text.length() && (j+1) < pattern.length())
  {
    if(text[i] == pattern[j+1])
    {
      i++;
      j++;
    }
    else
    {
      if(j == -1)
        i++;
      else
        j = lps[j];
    }
  }
  if((j+1) == pattern.length())
    return i - pattern.length();
  else
    return -1;

}


void make_lps(std::string pattern,std::vector<int> &lps)
{
  int i = 1;
  int curr_match = -1;
  lps.push_back(-1);
  while(i < pattern.length())
  {
    if(pattern[i] == pattern[curr_match+1])
    {
      curr_match++;
      lps.push_back(curr_match);
      i++;
    }
    else
    {
        curr_match = -1;
        lps.push_back(curr_match);
        i++;
    }
  }


}
