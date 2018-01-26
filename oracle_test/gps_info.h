/*
 * * A simple OCCI test application
 * * This file contains the Employees class declaration
 * */
 
#include <iostream>
#include <occi.h>
#include <iomanip>
 
using namespace oracle::occi;
using namespace std;

class Employees {
public:
   Employees();
   virtual ~Employees();
 
   void List();

private:
   Environment *env;
   Connection  *con;

   string user;
   string passwd;
   string db;
 };
 
 Employees::Employees()
 {
   /*
 *    * connect to the test database as the HR
 *       * sample user and use the EZCONNECT method
 *          * of specifying the connect string. Be sure
 *             * to adjust for your environment! The format
 *                * of the string is host:port/service_name
 *                */
 
   user = "scott";
   passwd = "tiger";
  db = "127.0.0.1:1522/orcl";
 
   env = Environment::createEnvironment(Environment::DEFAULT);
 
   try
   {
     con = env->createConnection(user, passwd, db);
   }
   catch (SQLException& ex)
   {
     cout << ex.getMessage();
 
     exit(EXIT_FAILURE);
   }
}

 Employees::~Employees()
 {
   env->terminateConnection (con);

   Environment::terminateEnvironment (env);
 }
 
 void Employees::List()
{
  /*
 *    * simple test method to select data from
 *       * the employees table and display the results
 *       */
 
   Statement *stmt = NULL;
   ResultSet *rs = NULL;
   string sql = "select EMPNO, ENAME, JOB " \
                "from EMP order by EMPNO";
 
   try
   {
     stmt = con->createStatement(sql);
   }
  catch (SQLException& ex)
  {
     cout << ex.getMessage();
   }
 
   if (stmt)
   {
     try
     {
      stmt->setPrefetchRowCount(32);

      rs = stmt->executeQuery();
    }
    catch (SQLException& ex)
     {
      cout << ex.getMessage();
    }
 
    if (rs)
    {
      cout << endl << setw(8) << left << "EMPNO"
            << setw(22) << left << "ENAME"
           << setw(27) << left << "JOB"
           << endl;
       cout << setw(8) << left << "======"
            << setw(22) << left << "===================="
            << setw(27) << left << "========================="
           << endl;
 
       while (rs->next()) {
        cout << setw(8) << left << rs->getInt(1)
            << setw(22) << left << (rs->isNull(2) ? "n/a" : rs->getString(2))
              << setw(27) << left << rs->getString(3)
              << endl;
      }

       cout << endl;
       stmt->closeResultSet(rs);
     }
     con->terminateStatement(stmt);
   }
 }
