﻿#include <iostream>
#include <vector>
#include <map>

class SqlSelectQueryBuilder {
private:
    std::string table;
    std::vector<std::string> column;
    std::map<std::string, std::string> condition;
public:
    std::string BuildQuery() {
        std::string query = "SELECT ";
        if (column.size() == 0) {
            query += "* ";
        }
        else {
            for (auto& it : column) {
                it != column.back() ? query += it + ", " : query += it + " ";
            }
        }

        query += "FROM " + table;

        if (condition.size() != 0) {
            query += " WHERE ";
            for (auto& it : condition) {
                query += it.first + "=" + it.second + " AND ";
            }
        }
        query.resize(query.size() - 5);

        return query += ";";
    }

    SqlSelectQueryBuilder& AddColumn(std::string value) noexcept {
        column.push_back(value);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (auto& it : columns) {
            column.push_back(it);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(std::string value) noexcept {
        table = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(std::string key, std::string value) noexcept {
        condition[key] = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (auto& it : kv) {
            condition[it.first] = it.second;
        }
        return *this;
    }


};

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({"name", "phone"});
    query_builder.AddFrom("students");
    query_builder.AddWhere({ { "id", "42" }, { "name", "John" } });

    std::cout << query_builder.BuildQuery() << std::endl;

}
