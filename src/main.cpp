
#include "db.h"

int main()
{
	DBProject::DB db;

	db.createTable<uint32_t, std::string, std::string, bool, uint32_t>("donors", { "ID", "City", "State", "IsTeacher", "Value" });
	db.insertToTable<uint32_t, std::string, std::string, bool, uint32_t>("donors", 1, "New York", "New York", true, 100);


	db.executeQuery("CREATE TABLE");
	return 0;
}
