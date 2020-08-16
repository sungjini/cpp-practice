#include <iostream>
#include <stdio.h>
#include <iostream>
#include <functional>

int main()
{
 int i;
 if (i > 0)
  std::cout << "over\n";
 [out = std::ref(std::cout << "Hello ")]() { out.get() << "World\n"; }();

 return 0;
}
