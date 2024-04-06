#pragma once
#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/ImGui/ImGuiLayer.h"

namespace Hazel {

	class Application
	{
	public:
		Application(const std::string& name = "Hazel App");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
	
		void SubmitToMainThread(const std::function<void()>& function);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		void ExecuteMainThreadQueue();
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;

		std::vector<std::function<void()>> m_MainThreadQueue;
		std::mutex m_MainThreadQueueMutex;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

