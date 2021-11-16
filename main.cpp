#include <cstdlib>
#include <iostream>
#include "Contestant.h"


using namespace std;

int main() {

  srand(11);
  Contestant c1,c2;
  c1.prepare();
  c2.prepare();

  Codemon code1("Name","Type",100,10);
  Codemon code2("Name2","Type2",100,10);

  Item i1("Name","Purpose",100);
  Item i2("Name2","Purpose2",100);

  c1 += code1;
  c1 + code2;
  
  c1 -= code1;
  c1 - code2;

  c1 += i1;
  c1 +i2;

  c1 -= i1;
  c1 - i2;

  string name = (c1 *c2).getName();
  cout << "Winner is " << name << endl;

  c1("heal");
  c2("heal");
}
