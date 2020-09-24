
#include <sstream>
#include "types.h"

namespace DBProject
{
	Type::TypeName getTypeFromString(const std::string& typeName)
	{
		if (typeName == "INT")
		{
			return Type::TypeName::Int;
		}
		else if (typeName == "UINT")
		{
			return Type::TypeName::Uint;
		}
		else if (typeName == "STRING")
		{
			return Type::TypeName::String;
		}
		else if (typeName == "BOOL")
		{
			return Type::TypeName::Bool;
		}

		return  Type::TypeName::Void;
	}

	std::string getStringFromType(Type::TypeName type)
	{
		switch (type)
		{
		case Type::TypeName::Int:
			return "INT";
		case Type::TypeName::Uint:
			return "UINT";
		case Type::TypeName::String:
			return "STRING";
		case Type::TypeName::Bool:
			return "BOOL";
		case Type::TypeName::Void:
		default:
			return "VOID";
		}
	}

	std::unique_ptr<Type> createTypedObject(const std::string& typeName, const std::string& valueStr)
	{
		Type::TypeName type = getTypeFromString(typeName);
		std::unique_ptr<Type> result;

		switch (type)
		{
		case Type::TypeName::Int:
			result = std::make_unique<IntType>();
			break;
		case Type::TypeName::Uint:
			result = std::make_unique<UintType>();
			break;
		case Type::TypeName::String:
			result = std::make_unique<StringType>();
			break;
		case Type::TypeName::Bool:
			result = std::make_unique<BoolType>();
			break;
		case Type::TypeName::Void:
			result = std::make_unique<VoidType>();
			break;
		}

		result->parseValue(valueStr);
		return result;
	}

	void IntType::parseValue(const std::string& valueStr)
	{
		mValue = atoi(valueStr.c_str());
	}

	std::unique_ptr<Type> IntType::clone() const
	{
		auto result = std::make_unique<IntType>();
		result->mValue = mValue;
		return result;
	}

	std::string IntType::getValue() const
	{
		std::stringstream ss;
		ss << mValue;
		return ss.str();
	}

	void UintType::parseValue(const std::string& valueStr)
	{
		mValue = static_cast<uint32_t>(atoi(valueStr.c_str()));
	}

	std::unique_ptr<Type> UintType::clone() const
	{
		auto result = std::make_unique<UintType>();
		result->mValue = mValue;
		return result;
	}

	std::string UintType::getValue() const
	{
		std::stringstream ss;
		ss << mValue;
		return ss.str();
	}

	StringType::StringType(const std::string& valueStr)
		: StringType()
	{
		parseValue(valueStr);
	}

	void StringType::parseValue(const std::string& valueStr)
	{
		mValue = valueStr;
	}

	std::unique_ptr<Type> StringType::clone() const
	{
		auto result = std::make_unique<StringType>();
		result->mValue = mValue;
		return result;
	}

	std::string StringType::getValue() const
	{
		return mValue;
	}

	void BoolType::parseValue(const std::string& valueStr)
	{
		if (valueStr == "true")
		{
			mValue = true;
		}
		else
		{
			mValue = false;
		}
	}
	std::unique_ptr<Type> BoolType::clone() const
	{
		auto result = std::make_unique<BoolType>();
		result->mValue = mValue;
		return result;
	}
	std::string BoolType::getValue() const
	{
		if (mValue == true)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	std::unique_ptr<Type> VoidType::clone() const
	{
		auto result = std::make_unique<VoidType>();
		return result;
	}
	std::string VoidType::getValue() const
	{
		return "";
	}
}
