#pragma once

#include <Arcane/Core/LayerStack.h>
#include <Arcane/Core/Events/Event.h>
#include "Arcane/Core/Events/ApplicationEvent.h"
#include <Arcane/Util/Singleton.h>

#include <Arcane/UI/DebugPane.h>
#include <Arcane/UI/RuntimePane.h>
#include <Arcane/UI/WaterPane.h>

namespace Arcane
{
	class Window;
	class Layer;
	class Scene3D;
	class MasterRenderer;
	class InputManager;
	class ImGuiLayer;

	struct ApplicationSpecification
	{
		std::string Name = "Arcane";
		uint32_t WindowWidth = 1920, WindowHeight = 1080;
		uint32_t RenderResolutionWidth = WindowWidth, RenderResolutionHeight = WindowHeight;
		bool VSync = true;
		bool EnableImGui = true;
	};

	class Application : public Singleton
	{
	public:
		Application(const ApplicationSpecification &specification);
		virtual ~Application();

		static inline Application& GetInstance() { return *s_Instance; }
		inline Window* GetWindow() { return m_Window; }

		void Run();
		void Close();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate(float deltaTime) {}

		virtual void OnEvent(Event &event);

		void PushLayer(Layer *layer);
		void PushOverlay(Layer *overlay);
		void RenderImGui();

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

		static const char* GetConfigName();
		static const char* GetPlatformName();
	private:
		bool OnWindowClose(WindowCloseEvent &event);
	private:
		ApplicationSpecification m_Specification;

		Window *m_Window;
		Scene3D *m_Scene3D;
		MasterRenderer *m_Renderer;
		InputManager *m_Manager;
		LayerStack m_LayerStack;

		bool m_Running = true;
		bool m_Minimized = false;

		ImGuiLayer *m_ImGuiLayer;

		static Application *s_Instance;

		// Temp Location
		Arcane::RuntimePane m_RuntimePane;
		Arcane::DebugPane m_DebugPane;
		Arcane::WaterPane m_WaterPane;
	};

	// Implemented by the client
	Application* CreateApplication(int argc, char** argv);
}
