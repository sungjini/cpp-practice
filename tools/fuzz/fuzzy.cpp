#include <cstdio>

std::size_t find_newline(const char *str)
{
 std::size_t loc = 0;
 /*
  * 
  */
 while (str[loc] != '\n') {
  ++loc;
 }

 return loc;
}

int main()
{
 //return find_newline("Hello\n");
 return find_newline("Hello");
}
