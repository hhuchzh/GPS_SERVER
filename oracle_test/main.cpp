#include "Employees.h"

 using namespace std;
 using namespace oracle::occi;

 int main (void)
 {
   /*
 *    * create an instance of the Employees class,
 *       * invoke the List member, delete the instance,
 *          * and prompt to continue...
 *          */
 
   Employees *pEmployees = new Employees();
 
   pEmployees->List();

   delete pEmployees;
 
   cout << "ENTER to continue...";
 
   cin.get();
 
   return 0;
 }
