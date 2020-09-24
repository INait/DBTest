#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "dbTable.h"

namespace DBProject
{
	class DB
	{
	public:
		DB() = default;
		DB(const DB&) = delete;
		DB& operator=(const DB&) = delete;

		void createTable(const std::string& name, std::vector<std::unique_ptr<Table::Column>>& columns);

		void insertToTable(const std::string& name, std::vector<std::unique_ptr<Table::InsertionData>>& values);

		std::unique_ptr<Table> executeQuery(const std::string& rawQuery);

		const Table* getTable(const std::string& name) const;
	private:

		std::unordered_map<std::string, std::unique_ptr<Table>> mTables;
	};

};

