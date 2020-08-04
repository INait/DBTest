
#include "query.h"

namespace DBProject
{
	void Query::parse()
	{
		auto check = mRawQuery.find("CREATE TABLE");
		if (check != std::string::npos)
		{
			mQueryAction = Action::CreateTable;
		}

		check = mRawQuery.find("INSERT");
		if (check != std::string::npos)
		{
			mQueryAction = Action::Insert;
		}
	}
}
