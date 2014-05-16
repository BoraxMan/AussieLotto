#include <iostream>
using namespace std;

int main()
{
try
  {
    if (2)
      throw;
 else 
   cout << "Should ont see this " << endl;
  }
  catch (...)
    {cout << "Error!" << endl;
      return 1;
    }
    cout << "Should not see this" << endl;
    return 0;
  }
