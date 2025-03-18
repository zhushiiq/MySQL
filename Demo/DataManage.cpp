#include "DataManage.h"

DataManage::DataManage()
{
    MYSQL* conn;

    const char* server = "192.168.1.22";
    const char* user = "root";
    const char* password = "123456";
    const char* database = "testdb";

    conn = mysql_init(nullptr);

    if (conn == nullptr) {
        std::cerr << "mysql_init() failed\n";
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, nullptr, 0) == nullptr) {
        std::cerr << "mysql_real_connect() failed. Error: " << mysql_error(conn) << "\n";
        mysql_close(conn);
    }

    std::cout << "Connected to MySQL server successfully!\n";

    // 查询数据
    const char* selectQuery = "SELECT * FROM users";
    std::cout << "Executing select query: " << selectQuery << "\n";
    std::vector<std::map<std::string, std::string>> queryResult = executeQuery(conn, selectQuery);


    for (const auto& row : queryResult) {
        for (const auto& field : row) {
            std::cout << field.first << ": " << field.second << " ";
        }
        std::cout << "\n";
    }

    mysql_close(conn);
}

std::vector<std::map<std::string, std::string>> DataManage::executeQuery(MYSQL* conn, const char* query)
{
    std::vector<std::map<std::string, std::string>> result;
    if (mysql_query(conn, query))
    {
        std::cerr << "Query failed. Error: " << mysql_error(conn) << "\n";
        return result;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == nullptr)
    {
        if (mysql_field_count(conn) == 0) {
            std::cout << "Query executed successfully. Affected rows: " << mysql_affected_rows(conn) << "\n";
        }
        else {
            std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << "\n";
        }
        return result;
    }

    // 获取字段名
    MYSQL_FIELD* fields = mysql_fetch_fields(res);
    int numFields = mysql_num_fields(res);

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr) {
        std::map<std::string, std::string> rowData;
        for (int i = 0; i < numFields; ++i) {
            rowData[fields[i].name] = row[i] ? row[i] : "NULL";
        }
        result.push_back(rowData);
    }

    mysql_free_result(res);
    return result;
}
