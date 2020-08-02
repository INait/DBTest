#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <array>
#include <unordered_map>

namespace DBProject
{
	class TableInterface
	{
	public:
		TableInterface() = default;
		virtual ~TableInterface() = default;
	};

	template<typename ... Types>
	class Table : public TableInterface
	{
	public:
		Table() = default;
		Table(std::initializer_list<std::string> columnNames)
			: mColumnNames(columnNames)
		{
		}

		~Table() = default;

		template<typename ... Types>
		void insert(Types... values)
		{
			mRows.push_back(std::make_tuple(values...));
		}

	private:
		uint16_t mColumnsCount = sizeof... (Types);
		std::vector<std::string> mColumnNames;

		std::vector<std::tuple<Types...>> mRows;
	};

};

