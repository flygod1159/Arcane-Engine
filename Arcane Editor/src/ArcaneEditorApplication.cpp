#include <Arcane.h>
#include <Arcane/ArcaneEntryPoint.h>

#include <EditorLayer.h>

class ArcaneEditorApplication : public Arcane::Application
{
public:
	ArcaneEditorApplication(const Arcane::ApplicationSpecification &specification)
		: Application(specification)
	{

	}

	~ArcaneEditorApplication()
	{

	}

	virtual void OnInit() override
	{
		PushLayer(new Arcane::EditorLayer());
	}
};

Arcane::Application* Arcane::CreateApplication(int argc, char **argv)
{
	Arcane::ApplicationSpecification specification;
	specification.Name = "Arcane Editor";
	specification.WindowWidth = 1600;
	specification.WindowHeight = 900;
	specification.VSync = true;
	return new ArcaneEditorApplication(specification);
}
