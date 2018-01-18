#include <stdio.h>
#include <sqlite3.h>
#include <iostream>
#include <unistd.h>

using namespace std;

static int callback(void* data, int nCols, char** pData, char** pHead)
{
	bool* showHeadOnce = (bool*)data;
	if ( *showHeadOnce )
	{
		for (int i = 0; i < nCols; ++i)
		{
			cout << pHead[i] << "\t";
		}
		cout << endl;
		*showHeadOnce = false;
	}

	for (int i = 0; i < nCols; ++i)
	{
		cout << pData[i] << "\t";
	}
	cout << endl;

	return 0;
}

int main(int argc, char* argv[])
{
	sqlite3* db;
	char* zErrMsg = 0;
	
	int rv = sqlite3_open("test.db", &db);

	if (rv)
	{
		cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
		return -1;
	}
	else
	{
		cout << "Open database successfully." << endl;
	}

	sqlite3_exec(db, "BEGIN;", 0, 0, 0);

	//Create a new table
	char sql_createTableStr[] = "CREATE TABLE COMPANY(ID INT PRIMARY KEY, NAME TEXT, NUM TEXT);";
	sqlite3_exec(db, sql_createTableStr, 0, 0, 0);

	char sql_insertStr1[] = "INSERT INTO COMPANY VALUES(1, 'Tom', '114');";
	char sql_insertStr2[] = "INSERT INTO COMPANY VALUES(3, 'Jerry', '119');";
	char sql_insertStr3[] = "INSERT INTO COMPANY VALUES(5, 'Chandler', '110');";
	char sql_insertStr4[] = "INSERT INTO COMPANY VALUES(7, 'Monica', '911');";
	char sql_insertStr5[] = "INSERT INTO COMPANY VALUES(9, 'Ross', '135');";
	//char sql_deleteStr[] = "DELETE FROM NAMES \
						   WHERE ID > 6;";
	//char sql_updateStr[] = "UPDATE NAMES \
						   SET ID = 4 \
						   WHERE NAME LIKE 'Chan%';";
	char sql_selectStr[] = "SELECT * FROM COMPANY;";

	//insert informatino into the new table
	sqlite3_exec(db, sql_insertStr1, 0, 0, 0);
	sleep(1);
	sqlite3_exec(db, sql_insertStr2, 0, 0, 0);
	sleep(1);
	sqlite3_exec(db, sql_insertStr3, 0, 0, 0);
	sleep(1);
	sqlite3_exec(db, sql_insertStr4, 0, 0, 0);
	sleep(1);
	sqlite3_exec(db, sql_insertStr5, 0, 0, 0);
	sleep(1);

	//delete line with id greater than 6
	//sqlite3_exec(db, sql_deleteStr, 0, 0, 0);

	//update table content
	//sqlite3_exec(db, sql_updateStr, 0, 0, 0);

	//select and print all entries
	static bool bHeaderOnce = true;
	sqlite3_exec(db, sql_selectStr, callback, &bHeaderOnce, &zErrMsg);
	if (zErrMsg != NULL)
	{
		cout << "w2 select error: " << zErrMsg << endl;
		sqlite3_close(db);
		return -1;
	}


	bool sql_bDelTable = false;
	if (sql_bDelTable)
	{
		char sql_delTableStr[] = "DELETE TABLE NAMES;";
		sqlite3_exec(db, sql_delTableStr, 0, 0, 0);
	}
	
	sqlite3_exec(db, "COMMIT;", 0, 0, 0);

	sqlite3_close(db);

	return 0;
};
