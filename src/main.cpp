
#include "db.h"

int main()
{
	using namespace DBProject;

	DB db;

	// TODO: move query to DB
	std::string createQuery = "CREATE TABLE donors (ID INT, City STRING, State STRING, IsTeacher BOOL, Value INT);";
	// TODO: parse query

	std::string tableName = "donors";
	std::vector<std::unique_ptr<Table::Column>> columnCreationData;

	columnCreationData.emplace_back(std::make_unique<Table::Column>("ID",         getTypeFromString("INT"),    createTypedObject("INT", "0")));
	columnCreationData.emplace_back(std::make_unique<Table::Column>("City",       getTypeFromString("STRING"), createTypedObject("STRING", "")));
	columnCreationData.emplace_back(std::make_unique<Table::Column>("State",      getTypeFromString("STRING"), createTypedObject("STRING", "")));
	columnCreationData.emplace_back(std::make_unique<Table::Column>("IsTeacher",  getTypeFromString("BOOL"),   createTypedObject("BOOL", "false")));
	columnCreationData.emplace_back(std::make_unique<Table::Column>("Value",      getTypeFromString("INT"),    createTypedObject("INT", "0")));

	db.createTable(tableName, columnCreationData);

	// TODO: move query to DB
	std::string insertQuery = "INSERT INTO donors (ID, City, State, IsTeacher, Value) VALUES (1, 'New York', 'New York', true, 100)";
	// TODO: parse query

	std::vector<std::unique_ptr<Table::InsertionData>> insertionData;
	insertionData.emplace_back(std::make_unique<Table::InsertionData>("ID", createTypedObject("INT", "1")));
	insertionData.emplace_back(std::make_unique<Table::InsertionData>("City", createTypedObject("STRING", "New York")));
	insertionData.emplace_back(std::make_unique<Table::InsertionData>("State", createTypedObject("STRING", "New York")));
	insertionData.emplace_back(std::make_unique<Table::InsertionData>("IsTeacher", createTypedObject("BOOL", "true")));
	insertionData.emplace_back(std::make_unique<Table::InsertionData>("Value", createTypedObject("INT", "100")));

	db.insertToTable(tableName, insertionData);

	return 0;
}
