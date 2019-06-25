#include "pch.h"

#include <graphics/Window.h>
#include <graphics/renderer/MasterRenderer.h>
#include <scene/Scene3D.h>
#include <ui/DebugPane.h>
#include <ui/RuntimePane.h>
#include <utils/Time.h>

int main() {
	// Prepare the engine

	// PS: Make sure your using the right bit version for your dlls
	// For android replace librenderdoc.so with libVkLayer_GLES_RenderDoc.so
	std::string dir = std::experimental::filesystem::current_path().string();
	RENDERDOC_API_1_4_0* m_RenderdocApi = nullptr;
	pRENDERDOC_GetAPI RENDERDOC_GetAPI;
	void* mod = nullptr;

#ifdef _WIN32
	mod = LoadLibrary("renderdoc.dll");
#elif (__Linux__)	
	void* mod = dlopen("librenderdoc.so", RTLD_NOW | RTLD_NOLOAD);
#endif

	if (!mod)
		return 0;

#ifdef _WIN32
	RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)GetProcAddress((HMODULE)mod, "RENDERDOC_GetAPI");
#elif (__linux__)	
	RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)dlsym(mod, "RENDERDOC_GetAPI");
#endif
	
	int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_4_0, (void**)&m_RenderdocApi);
	assert(ret == 1);

	m_RenderdocApi->SetLogFilePathTemplate((dir + "/logs/").c_str());

	// To start a frame capture, call StartFrameCapture.
	// You can specify NULL, NULL for the device to capture on if you have only one device and
	// either no windows at all or only one window, and it will capture from that device.
	// See the documentation below for a longer explanation
	//if (m_RenderdocApi)
	//	m_RenderdocApi->StartFrameCapture(NULL, NULL);


	// Stop screen capture
	//if (m_RenderdocApi)
	//	m_RenderdocApi->EndFrameCapture(NULL, NULL);

	arcane::Window window("Arcane Engine", WINDOW_X_RESOLUTION, WINDOW_Y_RESOLUTION);
	arcane::TextureLoader::initializeDefaultTextures();
	arcane::Scene3D scene(&window);
	arcane::MasterRenderer renderer(&scene);
	arcane::InputManager manager;

	// Prepare the UI
	arcane::RuntimePane runtimePane(glm::vec2(256.0f, 90.0f));
	arcane::DebugPane debugPane(glm::vec2(256.0f, 115.0f));

	// Initialize the renderer
	renderer.init();

	arcane::Time deltaTime;
	while (!window.closed()) {
		deltaTime.update();

#if DEBUG_ENABLED
		if (debugPane.getWireframeMode())
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

		window.clear();
		ImGui_ImplGlfwGL3_NewFrame();

		scene.onUpdate((float)deltaTime.getDeltaTime());
		renderer.render();

		// Display panes
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		runtimePane.render();
		debugPane.render();

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		// Window and input updating
		window.update();
	}
	
	return 0;
}
