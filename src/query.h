#pragma once

#include <memory>
#include <string>

namespace DBProject
{
	class Query
	{
	public:
		enum class Command
		{
			Invalid,
			Create,
			Insert,
			Select,
			Delete
		};

		enum class Object
		{
			Invalid,
			Table
		};

		struct QueryData
		{
			std::string colName;
			std::string colType;
			std::string value;
		};

		struct SelectQueryInfo
		{
			enum class OrderByDirection
			{
				Asc,
				Desc
			};

			struct Conditions
			{
				std::string colName;
				std::string value;
			};

			bool hasLimit = false;
			uint32_t rowsLimit = std::numeric_limits<uint32_t>::max();

			bool hasGroupBy = false;
			uint32_t groupByIndex = 0;

			bool hasOrderBy = false;
			uint32_t orderByIndex = 0;
			OrderByDirection orderByDirection = OrderByDirection::Asc;

			bool hasConditions = false;
			std::vector<Conditions> conditions;
		};

		Query() = default;
		Query(const std::string& rawQuery)
			: mRawQuery(rawQuery)
		{}

		~Query() = default;

		void parse();

		Command mQueryCommand = Command::Invalid;
		Object mQueryObject = Object::Invalid;
		std::string mObjectName;
		std::vector<QueryData> mQueryData;

		SelectQueryInfo mSelectQueryInfo;
	private:
		bool _parseCommand(const std::string& str);
		bool _parseObject(const std::string& str);

		std::string mRawQuery;

	};
};

