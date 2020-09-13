
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
			table->AddColumn(column->name, column->type, std::move(column->defaultValue));
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
		table->InsertRow(values);
	}

	void DB::executeQuery(const std::string& rawQuery)
	{
		auto query = std::make_unique<Query>(rawQuery);
		query->parse();
	}
}
