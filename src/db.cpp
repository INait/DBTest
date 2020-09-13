
#include "dbTable.h"
#include "query.h"
#include "db.h"

namespace DBProject
{
	DB::DB()
	{
	}
	void DB::createTable(const std::string& name, std::vector<std::unique_ptr<Table::Column>>& columns)
	{
		if (mTables.find(name) != mTables.end())
		{
			// assert table already exists
			return;
		}

		mTables[name] = std::make_unique<Table>();
		auto& table = mTables[name];

		for (auto&& column : columns)
		{
			table->addColumn(column->name, column->type, std::move(column->defaultValue));
		}
	}

	void DB::insertToTable(const std::string& name, std::vector<std::unique_ptr<Table::InsertionData>>& values)
	{
		if (mTables.find(name) == mTables.end())
		{
			// assert table doesn't exists
			return;
		}

		auto& table = mTables[name];
		table->insertRow(values);
	}

	void DB::executeQuery(const std::string& rawQuery)
	{
		auto query = std::make_unique<Query>(rawQuery);
		query->parse();

		if (query->mQueryCommand == Query::Command::Create)
		{
			std::vector<std::unique_ptr<Table::Column>> columnCreationData;
			for (auto&& queryData : query->mQueryData)
			{
				columnCreationData.emplace_back(std::make_unique<Table::Column>(
					queryData.colName,
					getTypeFromString(queryData.colType),
					createTypedObject(queryData.colType, queryData.value)
					)
				);
			}

			createTable(query->mObjectName, columnCreationData);
		}

		if (query->mQueryCommand == Query::Command::Insert)
		{
			auto table = getTable(query->mObjectName);
			if (!table)
			{
				// assert table doesn't exist
				return;
			}

			std::vector<std::unique_ptr<Table::InsertionData>> insertionData;
			for (auto&& queryData : query->mQueryData)
			{
				insertionData.emplace_back(std::make_unique<Table::InsertionData>(
					queryData.colName,
					createTypedObject(table->getColumnType(queryData.colName), queryData.value)
					)
				);
			}

			insertToTable(query->mObjectName, insertionData);
		}
	}

	const Table* DB::getTable(const std::string& name) const
	{
		auto it = mTables.find(name);
		if (it == mTables.end())
		{
			// assert table doesn't exists
			return nullptr;
		}

		return it->second.get();
	}
}
