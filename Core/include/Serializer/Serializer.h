#pragma once

#include <vector>
#include <filesystem>

namespace xe
{
	class ISerializable;
	class Serializer
	{
	private:
		struct Entry
		{
			std::string name;
			ISerializable* obj;
		};

	public:
		void AddEntry(ISerializable& obj, const std::string& name);
		void RemoveEntry(const std::string& name);

		void SaveTo(const std::filesystem::path& path);
		void LoadFrom(const std::filesystem::path& path);

	private:
		std::vector<Entry> m_serializables;
	};
}