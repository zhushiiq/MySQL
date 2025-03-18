#pragma once
#include <mysql/mysql.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
class DataManage
{
public:
	DataManage();
	std::vector<std::map<std::string, std::string>> executeQuery(MYSQL* conn, const char* query);
private:
};

