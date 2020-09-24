
#include <sstream>
#include "dbTable.h"

namespace DBProject
{
Table::Table(const std::string& singleValue)
{
	static constexpr char SingleValueColName[] = "Value";

	addColumn(SingleValueColName, Type::TypeName::String, std::make_unique<StringType>(""));

	std::vector<std::unique_ptr<InsertionData>> data;
	data.emplace_back(std::make_unique<InsertionData>(SingleValueColName, std::make_unique<StringType>(singleValue)));
	insertRow(data);
}

void Table::addColumn(std::unique_ptr<Column> column)
{
	mColumns.push_back(std::move(column));
}

void Table::addColumn(const std::string& name, Type::TypeName type, std::unique_ptr<Type> defaultValue)
{
	mColumns.push_back(std::make_unique<Column>(name, type, std::move(defaultValue)));

	auto& value = mColumns.back()->defaultValue;
	for (auto&& row : mRows)
	{
		row.push_back(value->clone());
	}
}

void Table::insertRow(std::vector<std::unique_ptr<InsertionData>>& insertionData)
{
	mRows.push_back({});
	auto& newRow = mRows.back();
	newRow.resize(mColumns.size());

	for (auto&& insertionUnit : insertionData)
	{
		int colIndex = -1;
		for (auto index = 0; index < mColumns.size(); index++)
		{
			if (mColumns[index]->name == insertionUnit->colName)
			{
				colIndex = index;
				break;
			}
		}

		// assert if colIndex == -1
		if (colIndex != -1)
		{
			newRow[colIndex] = std::move(insertionUnit->data);
		}
	}
}
std::string Table::getColumnType(const std::string& columnName) const
{
	for (auto&& column : mColumns)
	{
		if (column->name == columnName)
		{
			return getStringFromType(column->type);
		}
	}

	return getStringFromType(Type::TypeName::Void);
}

const std::unique_ptr<Table::Column>& Table::getColumn(const std::string& columnName) const
{
	for (auto&& column : mColumns)
	{
		if (column->name == columnName)
		{
			return column;
		}
	}

	return nullptr;
}

std::string Table::toString() const
{
	std::stringstream ss;
	auto colNum = mColumns.size();

	for (auto i = 0; i < colNum; i++)
	{
		ss << mColumns[i]->name << "\t";
	}

	ss << "\n";
	for (auto&& row : mRows)
	{
		for (auto i = 0; i < colNum; i++)
		{
			ss << row[i]->getValue() << "\t";
		}

		ss << "\n";
	}

	return ss.str();
}

const std::vector<std::unique_ptr<Table::Column>>& Table::getAllColumns() const
{
	return mColumns;
}

const std::vector<Table::Row>& Table::getAllRows() const
{
	return mRows;
}

std::unique_ptr<Table::Column> Table::Column::clone() const
{
	return std::make_unique<Column>(name, type, defaultValue->clone());
}
}
