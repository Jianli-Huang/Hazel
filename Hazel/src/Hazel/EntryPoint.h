#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	printf("1111\n");
	//Hazel::Log::Init();
	//HZ_CORE_WARN("Initialized Log!");
	int a = 4;
	//HZ_INFO("Hello var= {0}", a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}


#endif // HZ_PLATFORM_WINDOWS
