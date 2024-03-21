#include "hzpch.h"
#include "ScriptGlue.h"
#include "ScriptingEngine.h"

#include "Hazel/Core/UUID.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Scene/Scene.h"
#include "Hazel/Scene/Entity.h"


#include "mono/metadata/object.h"

#include "glm/gtx/string_cast.hpp"

namespace Hazel
{
#define HZ_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Hazel.InternalCalls::" #Name, Name)

	static void NativeLog(MonoString* string, int parameter)
	{
		char* cStr = mono_string_to_utf8(string);
		std::string str(cStr);
		mono_free(cStr);
		std::cout << str << " " << parameter << "\n";
	}

	static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* ourResult)
	{
		std::cout << glm::to_string(*parameter) << "\n";
		*ourResult = glm::cross(*parameter, glm::vec3(parameter->x, parameter->y, -parameter->z));
	}

	static float NativeLog_VectorDot(glm::vec3* parameter)
	{
		std::cout << glm::to_string(*parameter) << "\n";
		return glm::dot(*parameter, *parameter);
	}

	static void Entity_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);
		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	static void Entity_SetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		Entity entity = scene->GetEntityByUUID(entityID);
	   entity.GetComponent<TransformComponent>().Translation = *outTranslation;
	}

	static bool Input_IsKeyDown(int keycode)
	{
		return Input::IsKeyPressed(keycode);
	}

	void ScriptGlue::RegisterFunctions()
	{
		HZ_ADD_INTERNAL_CALL(NativeLog);
		HZ_ADD_INTERNAL_CALL(NativeLog_Vector);
		HZ_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		HZ_ADD_INTERNAL_CALL(Entity_GetTranslation);
		HZ_ADD_INTERNAL_CALL(Entity_SetTranslation);

		HZ_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}