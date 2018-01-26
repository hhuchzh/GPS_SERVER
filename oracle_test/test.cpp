#include <iostream>
#define LINUXOCCI //避免函数重定义错误
#include <occi.h>
#include <stdio.h>
using namespace std;
using namespace oracle::occi;
int main()
{
   Environment *env=Environment::createEnvironment(Environment::DEFAULT);
   cout<<"begin to connect"<<endl;
   string name = "youtu";
   string pass = "Bagejiadao321";
   string srvName = "121.41.92.30:1521/orcl";
   string date;
   Connection *conn = env->createConnection(name, pass,srvName);
   if(conn)  
	cout<<"success createConnection!"<<endl;  
   else  
	cout<<"failure createConnection!"<<endl;
   
   Statement *stmt = conn->createStatement();  
   string sSQL = "select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss') from dual";  
   stmt->setSQL(sSQL);  
   
   ResultSet *rs = stmt->executeQuery();  
   if(rs->next())  
   {  
	date = rs->getString(1);  
   }  
  
   cout<<"now time :"<<date<<endl;  
   env->terminateConnection(conn);  
   Environment::terminateEnvironment(env);  
   return 0;  
}
