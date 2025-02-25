#pragma once

#include <Arcane/Platform/OpenGL/Framebuffer/Framebuffer.h>
#include <Arcane/Platform/OpenGL/Framebuffer/GBuffer.h>

namespace Arcane
{
	enum RenderPassType {
		MaterialRequired,
		NoMaterialRequired
	};

	struct ShadowmapPassOutput {
		glm::mat4 directionalLightViewProjMatrix;
		Framebuffer *shadowmapFramebuffer;
	};

	struct LightingPassOutput {
		Framebuffer *outputFramebuffer;
	};

	struct WaterPassOutput
	{
		Framebuffer *outputFramebuffer;
	};

	struct GeometryPassOutput {
		GBuffer *outputGBuffer;
	};

	struct PreLightingPassOutput {
		Texture *ssaoTexture;
	};
}
