#pragma once

#include "Project.h"

namespace Hazel
{
	class ProjectSerializer
	{
	public:
		ProjectSerializer(Ref<Project> project);

		bool Serializer(const std::filesystem::path& filepath);
		bool Deserializer(const std::filesystem::path& filepath);
	private:
		Ref<Project> m_Project;
	};
}