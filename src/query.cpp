
#include <regex>

#include "query.h"

namespace DBProject
{
	void Query::parse()
	{
		static const std::regex reSpace("[\\s,\\(\\)]+");

		std::sregex_token_iterator it(mRawQuery.begin(), mRawQuery.end(), reSpace, -1);
		if (!_parseCommand(it->str()))
		{
			return;
		}

		++it;
		if (!_parseObject(it->str()))
		{
			return;
		}

		++it;
		mObjectName = it->str();

		++it;
		if (mQueryCommand == Command::Create)
		{
			while (it->str() != ";")
			{
				mQueryData.emplace_back(QueryData{});
				auto& data = mQueryData.back();

				data.colName = it->str();
				++it;
				data.colType = it->str();
				++it;
			}
		}
		else if (mQueryCommand == Command::Insert)
		{
			while (it->str() != "VALUES")
			{
				mQueryData.emplace_back(QueryData{});
				auto& data = mQueryData.back();

				data.colName = it->str();
				++it;
			}

			++it;
			size_t index = 0;
			while (it->str() != ";")
			{
				mQueryData[index].value = it->str();
				++it;
				++index;
			}
		}
	}

	bool Query::_parseCommand(const std::string& str)
	{
		if (str == "CREATE")
		{
			mQueryCommand = Command::Create;
			return true;
		}
		else if (str == "INSERT")
		{
			mQueryCommand = Command::Insert;
			return true;
		}

		return false;
	}

	bool Query::_parseObject(const std::string& str)
	{
		if (str == "TABLE" || str == "INTO")
		{
			mQueryObject = Object::Table;
			return true;
		}

		return false;
	}
}
