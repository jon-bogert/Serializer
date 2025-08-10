#include "Serializer/Serializer.h"

#include "Serializer/ISerializable.h"

#include <fstream>
#include <unordered_map>

void xe::Serializer::AddEntry(ISerializable& obj, const std::string& name)
{
	Entry& entry = m_serializables.emplace_back();
	entry.name = name;
	entry.obj = &obj;
}

void xe::Serializer::RemoveEntry(const std::string& name)
{
	auto result = std::find_if(m_serializables.begin(), m_serializables.end(), [&](const Entry& e) { return e.name == name; });
	if (result == m_serializables.end())
		return;

	m_serializables.erase(result);
}

void xe::Serializer::SaveTo(const std::filesystem::path& path)
{
	YAML::Node root;
	for (Entry& entry : m_serializables)
	{
		YAML::Node& node = root[entry.name];
		entry.obj->Serialize(true, node);
	}
	
	std::ofstream file(path);
	file << root;
}

void xe::Serializer::LoadFrom(const std::filesystem::path& path)
{
	std::ifstream file(path);
	YAML::Node root = YAML::Load(file);

	for (Entry& entry : m_serializables)
	{
		if (!root[entry.name].IsDefined())
			continue;

		YAML::Node& node = root[entry.name];
		entry.obj->Serialize(false, root[entry.name]);
	}
}
