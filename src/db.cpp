
#include "dbTable.h"
#include "query.h"
#include "db.h"

namespace DBProject
{
	DB::DB()
	{
	}
	void DB::executeQuery(const std::string& rawQuery)
	{
		auto query = std::make_unique<Query>(rawQuery);
		query->parse();
	}
}
