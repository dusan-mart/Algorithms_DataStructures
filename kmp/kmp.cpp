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

  int i = 0; //text counter
  int j = -1;//pattern counter
  while(i < text.length() && (j+1) < pattern.length())
  {
    if(text[i] == pattern[j+1])
    {
      i++;
      j++;
    }
    else
    {
      //if no previous matches, go further in text
      if(j == -1)
        i++;
      //look into table and set pattern counter
      //text counter not advancing in this case
      else
        j = lps[j];
    }
  }
  
  if((j+1) == pattern.length())
    return i - pattern.length();
  else
    return -1;

}

// search for longest proper prefix which is also suffix
//  for "abc", proper prefixes are "" "a" "ab", and suffixes are "" "c" "bc" "abc"
void make_lps(std::string pattern,std::vector<int> &lps)
{
  //we start from second element
  //we use -1 instead of 0 for convenience
  //beacuse of (j+1) < pattern.length() in while in kmp
  int i = 1;
  int curr_match = -1;
  lps.push_back(-1);

  //go through pattern, count matches and push them into table
  while(i < pattern.length())
  {
    if(pattern[i] == pattern[curr_match+1])
    {
      curr_match++;
      lps.push_back(curr_match);
      i++;
    }
    else//reset counter
    {
      curr_match = -1;
      lps.push_back(curr_match);
      i++;
    }
  }


}
