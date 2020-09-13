
#include "db.h"

int main()
{
	using namespace DBProject;

	DB db;

	db.executeQuery("CREATE TABLE donors (ID INT, City STRING, State STRING, IsTeacher BOOL, Value INT);");
	db.executeQuery("INSERT INTO donors (ID, City, State, IsTeacher, Value) VALUES (1, NewYork, NewYork, true, 100);");
	db.executeQuery("INSERT INTO donors (ID, City, State, IsTeacher, Value) VALUES (2, Washington, Washington, true, 200);");

	// TODO make work 'New York' strings
	//db.executeQuery("INSERT INTO donors (ID, City, State, IsTeacher, Value) VALUES (1, 'New York', 'New York', true, 100);");

	return 0;
}
