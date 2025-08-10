#pragma once

#include <yaml-cpp/yaml.h>

#include <functional>
#include <type_traits>

namespace xe
{
	class ISerializable
	{
	public:
		virtual void Serialize(const bool isSaving, YAML::Node& dataNode) = 0; // Save data into the provided node
	};

	// == ISERIALIZABLE OBJECTS == 

	template <typename _Ty>
	typename std::enable_if_t<std::is_base_of_v<ISerializable, _Ty>, void>
		DoSerialize(_Ty& value, const char* name, const bool isSaving, YAML::Node& dataNode)
	{
		YAML::Node& newNode = dataNode[name];
		value.Serialize(isSaving, newNode);
	}

	// == ISERIALIZABLE OBJECTS == 

	template <typename _Ty>
	typename std::enable_if_t<!std::is_base_of_v<ISerializable, _Ty>, void>
		DoSerialize(_Ty& value, const char* name, bool isSaving, YAML::Node& dataNode)
	{
		if (isSaving)
			dataNode[name] = value;
		else
			value = dataNode[name].as<_Ty>();
	}

}

#define SERIALIZE(val) xe::DoSerialize(val, #val, __isSaving, __dataNode)
#define SERIALIZE_METHOD \
virtual void Serialize(const bool __isSaving, YAML::Node& __dataNode) override
