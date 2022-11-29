#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#pragma comment(lib, "debug/mysqlcppconn.lib")

using namespace std;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "1234";

int main()
{
	sql::Driver* driver;
	sql::Connection* connection = nullptr;
	sql::Statement* statement = nullptr;
	sql::PreparedStatement* preparedStatement;

	try
	{
		driver = get_driver_instance();
		connection = driver->connect(server, username, password);
		connection->setSchema("homepage"); //use guestbook;
		string Command;
		string id;
		string password;
		string name;
		string Answer;

		cout << "1. 회원가입 " << endl;
		cout << "2. 로그인 " << endl;
		cout << "? " << endl;
		cin >> Command;
		if (Command.compare("1") == 0)
		{
			cout << "id: ";
			cin >> id;

			cout << "password : ";
			cin >> password;

			cout << "이름 : ";
			cin >> name;

			cout << "가입하기(y / n) ?";
			cin >> Answer;

			if (Answer.compare("y") == 0)
			{
				preparedStatement = connection->prepareStatement("select * from user where id = ?");
				preparedStatement->setString(1, id);
				sql::ResultSet* RS = preparedStatement->executeQuery();

				if (RS->rowsCount() > 0)
				{
					cout << "가입 실패" << endl;
				}
				else
				{
					statement = connection->createStatement();
					statement->execute("insert into member ( `id`, `password` ) values ( '" + id + "', sha('" + password + "') ");
					cout << "가입 성공" << endl;
				}
			}
		}
		else if (Command.compare("2") == 0)
		{
			cout << "id: ";
			cin >> id;

			cout << "password : ";
			cin >> password;

			cout << "로그인하기(y / n) ?";
			cin >> Answer;

			if (Answer.compare("y") == 0)
			{
				preparedStatement = connection->prepareStatement("select * from member where id = ? and password = sha(?)");
				preparedStatement->setString(1, id);
				preparedStatement->setString(2, password);

				sql::ResultSet* RS = preparedStatement->executeQuery();

				if (RS->rowsCount() > 0)
				{
					cout << "로그인 성공" << endl;
				}
				else
				{
					cout << "로그인 실패" << endl;
				}
			}
		}
	}
	catch (exception e)
	{
		cout << "error : " << e.what() << endl;
	}

	//stmt = con->createStatement();
	//sql::ResultSet* resultSet = stmt->executeQuery("select * from guestbook limit 5, 5");

	//while (resultSet->next())
	//{
	//}

	//try
	//{

	//}
	//catch (sql::SQLException e)
	//{
	//	cout << "Error message: " << e.what() << endl;
	//	system("pause");
	//	exit(1);
	//}

	//stmt->close();
	//stmt = con->createStatement();
	//sql::ResultSet* resultSet2 = stmt->executeQuery("select * from guestbook order by idx desc limit 0, 5");

	//while (resultSet2->next())
	//{

	//}


	//	delete resultSet;
		//delete resultSet2;
	delete connection;
	system("pause");
	return 0;
}