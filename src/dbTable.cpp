#include "dbTable.h"

namespace DBProject
{
void Table::AddColumn(const std::string& name, Type::TypeName type, std::unique_ptr<Type> defaultValue)
{
	mColumns.push_back(std::make_unique<Column>(name, type, std::move(defaultValue)));

	auto& value = mColumns.back()->defaultValue;
	for (auto&& row : mRows)
	{
		row.push_back(value->clone());
	}
}

void Table::InsertRow(std::vector<std::unique_ptr<InsertionData>>& insertionData)
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
}
