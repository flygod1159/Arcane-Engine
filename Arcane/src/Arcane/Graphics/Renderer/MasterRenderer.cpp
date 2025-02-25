#include "arcpch.h"
#include "MasterRenderer.h"

#include <Arcane/Graphics/Renderer/GLCache.h>
#include <Arcane/Scene/Scene3D.h>
#include <Arcane/UI/RuntimePane.h>

namespace Arcane
{
	MasterRenderer::MasterRenderer(Scene3D *scene) : m_ActiveScene(scene),
		m_ShadowmapPass(scene), m_PostProcessPass(scene), m_WaterPass(scene), m_ForwardLightingPass(scene, true), m_EnvironmentProbePass(scene),
		m_DeferredGeometryPass(scene), m_DeferredLightingPass(scene), m_PostGBufferForwardPass(scene)
	{
		m_GLCache = GLCache::GetInstance();
	}

	void MasterRenderer::Init() {
		// State that should never change
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		m_EnvironmentProbePass.pregenerateIBL();
		m_EnvironmentProbePass.pregenerateProbes();
	}

	void MasterRenderer::Render() {
		/* Forward Rendering */
#if FORWARD_RENDER
#if DEBUG_PROFILING
		glFinish();
		m_ProfilingTimer.Reset();
#endif // DEBUG_PROFILING
		ShadowmapPassOutput shadowmapOutput = m_ShadowmapPass.generateShadowmaps(m_ActiveScene->GetCamera(), false);
#if DEBUG_PROFILING
		glFinish();
		RuntimePane::SetShadowmapTimer((float)m_ProfilingTimer.Elapsed());
#endif // DEBUG_PROFILING

		LightingPassOutput lightingOutput = m_ForwardLightingPass.executeLightingPass(shadowmapOutput, m_ActiveScene->GetCamera(), false, true);
		WaterPassOutput waterOutput = m_WaterPass.executeWaterPass(shadowmapOutput, lightingOutput, m_ActiveScene->GetCamera());
		m_PostProcessPass.executePostProcessPass(waterOutput.outputFramebuffer);


		/* Deferred Rendering */
#else
#if DEBUG_PROFILING
		glFinish();
		m_ProfilingTimer.Reset();
#endif // DEBUG_PROFILING
		ShadowmapPassOutput shadowmapOutput = m_ShadowmapPass.generateShadowmaps(m_ActiveScene->GetCamera(), false);
#if DEBUG_PROFILING
		glFinish();
		RuntimePane::SetShadowmapTimer((float)m_ProfilingTimer.Elapsed());
#endif // DEBUG_PROFILING

		GeometryPassOutput geometryOutput = m_DeferredGeometryPass.executeGeometryPass(m_ActiveScene->GetCamera(), false);
		PreLightingPassOutput preLightingOutput = m_PostProcessPass.executePreLightingPass(geometryOutput, m_ActiveScene->GetCamera());
		LightingPassOutput deferredLightingOutput = m_DeferredLightingPass.executeLightingPass(shadowmapOutput, geometryOutput, preLightingOutput, m_ActiveScene->GetCamera(), true);
		LightingPassOutput postGBufferForward = m_PostGBufferForwardPass.executeLightingPass(shadowmapOutput, deferredLightingOutput, m_ActiveScene->GetCamera(), false, true);
		WaterPassOutput waterOutput = m_WaterPass.executeWaterPass(shadowmapOutput, postGBufferForward, m_ActiveScene->GetCamera());
		m_PostProcessPass.executePostProcessPass(waterOutput.outputFramebuffer);

#endif
	}
}
