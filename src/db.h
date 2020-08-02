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

		template<typename ... T>
		void createTable(const std::string& name, const std::initializer_list<std::string>& columnNames);

		template<typename ... T>
		void insertToTable(const std::string& name, T... values);
	private:

		std::unordered_map<std::string, std::unique_ptr<TableInterface>> mTables;
	};

	template<typename ...T>
	inline void DB::createTable(const std::string& name, const std::initializer_list<std::string>& columnNames)
	{
		auto table = std::make_unique<Table<T...>>(columnNames);
		mTables[name] = std::unique_ptr<TableInterface>(static_cast<TableInterface*>(table.release()));
	}

	template<typename ...T>
	inline void DB::insertToTable(const std::string& name, T ...values)
	{
		auto tableSearched = mTables.find(name);
		if (tableSearched == mTables.end())
		{
			std::cout << "Table `" << name << "` not found" << std::endl;
		}

		auto table = tableSearched->second.get();
		if (auto castTable = dynamic_cast<Table<T...>*>(table))
		{
			castTable->insert(values...);
		}

	}
};

