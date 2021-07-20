#pragma once

#include <Arcane.h>

#include <Arcane/Editor/ConsolePanel.h>
#include <Arcane/Editor/EditorViewport.h>
#include <Arcane/Editor/ScenePanel.h>

namespace Arcane
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTime) override;

		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event &event) override;

		void NewScene();
		void OpenScene(const std::string& filepath);
	private:
		Scene3D *m_EditorScene;

		EditorViewport m_EditorViewport;
		ConsolePanel m_ConsolePanel;
		ScenePanel m_ScenePanel;
	};
}
