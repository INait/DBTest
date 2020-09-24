#pragma once

#include <memory>
#include <string>
#include <vector>

#include "types.h"

namespace DBProject
{
	class Table
	{
	public:
		Table() = default;
		~Table() = default;

		explicit Table(const std::string& singleValue);

		Table(const Table&) = delete;
		Table& operator=(const Table&) = delete;

		using Row = std::vector<std::unique_ptr<Type>>;
		struct Column
		{
			Column(const std::string& _name, Type::TypeName _type, std::unique_ptr<Type> _defaultValue)
				: name(_name)
				, type(_type)
				, defaultValue(std::move(_defaultValue))
			{}

			Column(const Column&) = delete;
			Column& operator=(const Column&) = delete;

			std::unique_ptr<Column> clone() const;

			std::string name;
			Type::TypeName type;
			std::unique_ptr<Type> defaultValue;
		};

		struct InsertionData
		{
			InsertionData(const std::string& _colName, std::unique_ptr<Type> _data)
				: colName(_colName)
				, data(std::move(_data))
			{}

			InsertionData(const InsertionData&) = delete;
			InsertionData& operator=(const InsertionData&) = delete;

			std::string colName;
			std::unique_ptr<Type> data;
		};

		void addColumn(std::unique_ptr<Column> column);
		void addColumn(const std::string& name, Type::TypeName type, std::unique_ptr<Type> defaultValue);
		void insertRow(std::vector<std::unique_ptr<InsertionData>>& insertionData);

		std::string getColumnType(const std::string& columnName) const;
		const std::unique_ptr<Column>& getColumn(const std::string& columnName) const;

		std::string toString() const;

		const std::vector<std::unique_ptr<Column>>& getAllColumns() const;
		const std::vector<Row>& getAllRows() const;

	private:
		std::vector<std::unique_ptr<Column>> mColumns;
		std::vector<Row> mRows;
	};
};

