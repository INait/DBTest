#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>

#include "dbTable.h"

namespace DBProject
{
	class DB
	{
	public:
		DB();
		DB(const DB&) = delete;
		DB& operator=(const DB&) = delete;

		void createTable(const std::string& name, std::vector<std::unique_ptr<Table::Column>>& columns);

		void insertToTable(const std::string& name, std::vector<std::unique_ptr<Table::InsertionData>>& values);

		void executeQuery(const std::string& rawQuery);
	private:

		std::unordered_map<std::string, std::unique_ptr<Table>> mTables;
	};

};

