
#include <algorithm>

#include "dbTable.h"
#include "query.h"
#include "db.h"

namespace DBProject
{
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

	void DB::importTableFromCSV(const std::string& name, const std::string& data)
	{
		if (mTables.find(name) != mTables.end())
		{
			// assert table already exists
			return;
		}

		mTables[name] = std::make_unique<Table>();
		auto& table = mTables[name];

		table->createFromCSV(data);
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

	std::unique_ptr<Table> DB::executeQuery(const std::string& rawQuery)
	{
		auto query = std::make_unique<Query>(rawQuery);
		query->parse();

		switch (query->mQueryCommand)
		{
			case Query::Command::Create:
			{
				auto table = getTable(query->mObjectName);
				if (table)
				{
					return std::make_unique<Table>("Table already exists");
				}

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

				return std::make_unique<Table>("Success");
			}

			case Query::Command::Insert:
			{
				auto table = getTable(query->mObjectName);
				if (!table)
				{
					return std::make_unique<Table>("Table doesn't exist");
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

				return std::make_unique<Table>("Success");
			}

			case Query::Command::Select:
			{
				auto table = getTable(query->mObjectName);
				if (!table)
				{
					return std::make_unique<Table>("Table doesn't exist");
				}

				auto& columns = table->getAllColumns();

				auto resultTable = std::make_unique<Table>();
				for (auto&& queryData : query->mQueryData)
				{
					if (queryData.colName == "ALL")
					{
						for (auto&& column : columns)
						{
							resultTable->addColumn(column->clone());
						}
					}
					else
					{
						for (auto&& column : columns)
						{
							if (column->name == queryData.colName)
							{
								resultTable->addColumn(column->clone());
								break;
							}
						}
					}
				}

				auto& rows = table->getAllRows();

				// fill rows
				std::vector<std::unique_ptr<Table::InsertionData>> insertionData;

				std::vector<std::pair<std::string, size_t>> columnIndecesOrder;
				for (auto&& newColumn : resultTable->getAllColumns())
				{
					auto indexIt = std::find_if(columns.begin(), columns.end(),
						[colName = newColumn->name](const std::unique_ptr<Table::Column>& value)
					{
						return value->name == colName;
					});

					if (indexIt == columns.end())
					{
						continue;
					}

					size_t index = std::distance(columns.begin(), indexIt);
					columnIndecesOrder.push_back(std::make_pair(newColumn->name, index));
				}

				for (auto&& row : rows)
				{
					for (auto& columnIndexPair : columnIndecesOrder)
					{
						insertionData.emplace_back(std::make_unique<Table::InsertionData>(
							columnIndexPair.first,
							row[columnIndexPair.second]->clone())
						);
					}

					resultTable->insertRow(insertionData);
				}

				return resultTable;
			}

			case Query::Command::Delete:
			{
				return std::make_unique<Table>("Success");
			}

			default:
			{
				return std::make_unique<Table>("Success");
			}
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
