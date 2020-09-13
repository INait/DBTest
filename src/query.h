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
			Insert
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

	private:
		bool _parseCommand(const std::string& str);
		bool _parseObject(const std::string& str);

		std::string mRawQuery;

	};
};

