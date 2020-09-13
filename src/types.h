#pragma once

#include <string>
#include <memory>

namespace DBProject
{
	class Type
	{
	public:
		enum class TypeName
		{
			Void,
			Int,
			Uint,
			String,
			Bool
		};

		Type() = default;
		explicit Type(TypeName typeName) : mTypeName(typeName) {}

		virtual ~Type() = default;
		virtual void parseValue(const std::string& valueStr) = 0;
		virtual std::unique_ptr<Type> clone() const = 0;

	protected:
		TypeName mTypeName = TypeName::Void;
	};

	class IntType : public Type
	{
	public:
		IntType()
			: Type(TypeName::Int)
		{}

		void parseValue(const std::string& valueStr) override;
		std::unique_ptr<Type> clone() const override;
	private:
		int32_t mValue = int32_t{};
	};

	class UintType : public Type
	{
	public:
		UintType()
			: Type(TypeName::Uint)
		{}

		void parseValue(const std::string& valueStr) override;
		std::unique_ptr<Type> clone() const override;

	private:
		uint32_t mValue = uint32_t{};
	};

	class StringType : public Type
	{
	public:
		StringType()
			: Type(TypeName::String)
		{}

		void parseValue(const std::string& valueStr) override;
		std::unique_ptr<Type> clone() const override;

	private:
		std::string mValue = std::string{};
	};

	class BoolType : public Type
	{
	public:
		BoolType()
			: Type(TypeName::Bool)
		{}

		void parseValue(const std::string& valueStr) override;
		std::unique_ptr<Type> clone() const override;

	private:
		bool mValue = false;
	};

	class VoidType : public Type
	{
	public:
		VoidType()
			: Type(TypeName::Void)
		{}

		void parseValue(const std::string& valueStr) override {};
		std::unique_ptr<Type> clone() const override;
	};

	Type::TypeName getTypeFromString(const std::string& typeName);
	std::unique_ptr<Type> createTypedObject(const std::string& typeName, const std::string& valueStr);
};

