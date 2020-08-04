#pragma once

#include <memory>
#include <string>

namespace DBProject
{
	class Query
	{
	public:
		enum class Action
		{
			Invalid,
			CreateTable,
			Insert
		};

		Query() = default;
		Query(const std::string& rawQuery)
			: mRawQuery(rawQuery)
		{}

		~Query() = default;

		void parse();

		Action mQueryAction = Action::Invalid;

	private:
		std::string mRawQuery;

	};
};

