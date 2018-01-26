#include <iostream>
#include <occi.h>
#include <stdio.h>
using namespace std;
using namespace oracle::occi;
int main()
{
  Environment *env=Environment::createEnvironment();
  string name = "youtu";
  string pass = "Bagejiadao321";
  string srvName = "121.41.92.30:1521/orcl";
  try
  {
    Connection *conn = env->createConnection(name, pass, srvName);
    if(conn)
    	cout<<"conn success"<<endl;
    else
       cout<<"create connection failed"<<endl;

    //数据操作,创建Statement对象
    Statement *pStmt = NULL;    // Statement对象
    pStmt = conn->createStatement();
    if(NULL == pStmt){
	printf("createStatement error.\n");
	return -1;
    }
    printf("connect DB successfully\n");
    //查询数据库时间
    std::string strTemp;
    ResultSet *pRs = pStmt->executeQuery( "SELECT TO_CHAR(SYSDATE, 'YYYY-MM-DD HH24:MI:SS') FROM DUAL");
    while(pRs->next()) {
	strTemp = pRs->getString(1);
	printf("db time:%s.\n", strTemp.c_str());
    // int类型取值用getInt()
	break;
                   }
	pStmt->closeResultSet(pRs);
	//--------插入---------
        // 指定DML为自动提交
	pStmt->setAutoCommit(TRUE);
	// 设置执行的SQL语句
        //pStmt->setSQL("INSERT INTO TA (ID, NAME) VALUES (1, 'ZS')");
       	pStmt->setSQL("INSERT INTO B_GPS_INFO (device_id, latitude, longitude, heading, speed, lat_type, lng_type, cell_id,  gps_time) VALUES (77777777, 567955, 345623, 1, 56, 3, 2, 67866,'4567')");
       	pStmt->setSQL("INSERT INTO B_GPS_INFO (device_id, latitude,longitude,heading,speed,lat_type,lng_type,cell_id,gps_time) VALUES (4444444, 432443,65432,2,50,3435,498,123456,to_date('2004/05/07 13:23:44','yyyy/mm/dd hh24:mi:ss'))");

	// 执行SQL语句
	unsigned int nRet = pStmt->executeUpdate();
	if(nRet == 0) {
		printf("executeUpdate insert error.\n");
        }
	// 终止Statement对象
	conn->terminateStatement(pStmt);
	env->terminateConnection(conn);
  }
  catch(SQLException e)
  {
    cout<<e.what()<<endl;
  }

  Environment::terminateEnvironment(env);
  cout<<"end!"<<endl;
  return 0;
}
