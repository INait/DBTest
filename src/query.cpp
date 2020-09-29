
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

		if (mQueryCommand == Command::Create)
		{
			++it;
			if (!_parseObject(it->str()))
			{
				return;
			}

			++it;
			mObjectName = it->str();

			++it;

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
			++it;
			if (!_parseObject(it->str()))
			{
				return;
			}

			++it;
			mObjectName = it->str();

			++it;

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
		else if (mQueryCommand == Command::Select)
		{
			while (it->str() != "FROM")
			{
				if (it->str() == "*")
				{
					mQueryData.emplace_back(QueryData{ "*", "", "" });
				}
				else
				{
					mQueryData.emplace_back(QueryData{ it->str(), "", "" });
				}

				++it;
			}

			if (!_parseObject(it->str()))
			{
				return;
			}

			++it;
			mObjectName = it->str();
			mObjectName = std::regex_replace(mObjectName, std::regex(";"), "");

			++it;

			while (it != std::sregex_token_iterator{})
			{
				if (it->str() == "WHERE")
				{
					mSelectQueryInfo.hasConditions = true;

					++it;
					std::string colName = it->str();

					++it;
					// TODO: add <, >, <=, >=
					if (it->str() != "=")
					{
						continue;
					}

					++it;
					std::string colValue = it->str();
					mSelectQueryInfo.conditions.emplace_back(SelectQueryInfo::Conditions{colName, colValue});
				}
				else if (it->str() == "GROUP")
				{
					mSelectQueryInfo.hasGroupBy = true;
					++it;
					if (it->str() == "BY")
					{
						++it;
						mSelectQueryInfo.groupByIndex = atoi(it->str().c_str()) - 1;
					}
				}
				else if (it->str() == "ORDER")
				{
					mSelectQueryInfo.hasOrderBy = true;
					++it;
					if (it->str() == "BY")
					{
						++it;
						mSelectQueryInfo.orderByIndex = atoi(it->str().c_str()) - 1;

						++it;
						if (it->str() == "ASC")
						{
							mSelectQueryInfo.orderByDirection = SelectQueryInfo::OrderByDirection::Asc;
						}
						else if (it->str() == "DESC")
						{
							mSelectQueryInfo.orderByDirection = SelectQueryInfo::OrderByDirection::Desc;
						}
					}
				}
				else if (it->str() == "LIMIT")
				{
					mSelectQueryInfo.hasLimit = true;
					++it;

					mSelectQueryInfo.rowsLimit = atoi(it->str().c_str());
				}

				++it;
			}
		}
		else if (mQueryCommand == Command::Delete)
		{

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
		else if (str == "SELECT")
		{
			mQueryCommand = Command::Select;
			return true;
		}
		else if (str == "DELETE")
		{
			mQueryCommand = Command::Delete;
			return true;
		}
		return false;
	}

	bool Query::_parseObject(const std::string& str)
	{
		if (str == "TABLE" || str == "INTO" || str == "FROM")
		{
			mQueryObject = Object::Table;
			return true;
		}

		return false;
	}
}
