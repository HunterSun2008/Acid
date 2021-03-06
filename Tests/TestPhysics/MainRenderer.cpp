#include "MainRenderer.hpp"

#include <Fonts/RendererFonts.hpp>
#include <Gizmos/RendererGizmos.hpp>
#include <Guis/RendererGuis.hpp>
#include <Devices/Keyboard.hpp>
#include <Meshes/RendererMeshes.hpp>
#include <Models/Shapes/ModelSphere.hpp>
#include <Particles/RendererParticles.hpp>
#include <Post/Deferred/RendererDeferred.hpp>
#include <Post/Filters/FilterCrt.hpp>
#include <Post/Filters/FilterDefault.hpp>
#include <Post/Filters/FilterDof.hpp>
#include <Post/Filters/FilterEmboss.hpp>
#include <Post/Filters/FilterFxaa.hpp>
#include <Post/Filters/FilterGrain.hpp>
#include <Post/Filters/FilterLensflare.hpp>
#include <Post/Filters/FilterPixel.hpp>
#include <Post/Filters/FilterSsao.hpp>
#include <Post/Filters/FilterTiltshift.hpp>
#include <Post/Filters/FilterTone.hpp>
#include <Post/Filters/FilterVignette.hpp>
#include <Post/Pipelines/PipelineBlur.hpp>
#include <Renderer/Renderer.hpp>
#include <Scenes/Scenes.hpp>
#include <Shadows/RendererShadows.hpp>

namespace test
{
	MainRenderer::MainRenderer()
	{
	}

	void MainRenderer::Start()
	{
		std::vector<RenderStage *> renderStages = {};

		std::vector<Attachment> renderpassImages0 = {
			Attachment(0, "shadows", Attachment::Type::Image, false, VK_FORMAT_R8_UNORM)
		};
		std::vector<SubpassType> renderpassSubpasses0 = {
			SubpassType(0, {0})
		};
		renderStages.emplace_back(new RenderStage(RenderpassCreate(renderpassImages0, renderpassSubpasses0, 4096, 4096)));

		std::vector<Attachment> renderpassImages1 = {
			Attachment(0, "depth", Attachment::Type::Depth, false),
			Attachment(1, "swapchain", Attachment::Type::Swapchain),
			Attachment(2, "position", Attachment::Type::Image, false, VK_FORMAT_R16G16B16A16_SFLOAT),
			Attachment(3, "diffuse", Attachment::Type::Image, false, VK_FORMAT_R8G8B8A8_UNORM),
			Attachment(4, "normal", Attachment::Type::Image, false, VK_FORMAT_R16G16B16A16_SFLOAT),
			Attachment(5, "material", Attachment::Type::Image, false, VK_FORMAT_R8G8B8A8_UNORM),
			Attachment(6, "resolved", Attachment::Type::Image, false, VK_FORMAT_R8G8B8A8_UNORM)
		};
		std::vector<SubpassType> renderpassSubpasses1 = {
			SubpassType(0, {0, 2, 3, 4, 5}),
			SubpassType(1, {0, 6}),
			SubpassType(2, {0, 1})
		};
		renderStages.emplace_back(new RenderStage(RenderpassCreate(renderpassImages1, renderpassSubpasses1)));
		Renderer::Get()->SetRenderStages(renderStages);

		auto &rendererContainer = GetRendererContainer();
		rendererContainer.Clear();

	//	rendererContainer.Add<RendererShadows>(Pipeline::Stage(0, 0));

		rendererContainer.Add<RendererMeshes>(Pipeline::Stage(1, 0));

		rendererContainer.Add<RendererDeferred>(Pipeline::Stage(1, 1), RendererDeferred::Type::Simple);
		rendererContainer.Add<RendererParticles>(Pipeline::Stage(1, 1));

		rendererContainer.Add<FilterFxaa>(Pipeline::Stage(1, 2));
	//	rendererContainer.Add<FilterTone>(Pipeline::Stage(1, 2));
	//	rendererContainer.Add<FilterSsao>(Pipeline::Stage(1, 2));
	//	auto sceneBlur = rendererContainer.Add<PipelineBlur>(Pipeline::Stage(1, 2), 1.8f, FilterBlur::Type::_5, false, 0.6f, 1.0f);
	//	rendererContainer.Add<FilterDof>(Pipeline::Stage(1, 2), sceneBlur, 1.11f);
	//	rendererContainer.Add<FilterEmboss>(Pipeline::Stage(1, 2));
	//	rendererContainer.Add<FilterCrt>(Pipeline::Stage(1, 2));
	//	rendererContainer.Add<FilterLensflare>(Pipeline::Stage(1, 2));
	//	rendererContainer.Add<FilterTiltshift>(Pipeline::Stage(1, 2));
	//	rendererContainer.Add<FilterPixel>(Pipeline::Stage(1, 2), 8.0f);
		rendererContainer.Add<FilterVignette>(Pipeline::Stage(1, 2));
		rendererContainer.Add<FilterGrain>(Pipeline::Stage(1, 2));
		rendererContainer.Add<FilterDefault>(Pipeline::Stage(1, 2), true);
	//	rendererContainer.Add<RendererGizmos>(Pipeline::Stage(1, 2));
		rendererContainer.Add<RendererGuis>(Pipeline::Stage(1, 2));
		rendererContainer.Add<RendererFonts>(Pipeline::Stage(1, 2));
	}

	void MainRenderer::Update()
	{
		auto &renderpassCreate0 = Renderer::Get()->GetRenderStage(0)->GetRenderpassCreate();
		renderpassCreate0.SetWidth(Shadows::Get()->GetShadowSize());
		renderpassCreate0.SetHeight(Shadows::Get()->GetShadowSize()); // * RendererShadows::NUM_CASCADES

	//	auto &renderpassCreate1 = Renderer::Get()->GetRenderStage(1)->GetRenderpassCreate();
	//	renderpassCreate1.SetScale(0.75f);

	//	Renderer::Get()->GetRenderer<FilterVignette>(true)->SetEnabled(Keyboard::Get()->GetKey(KEY_I));
	}
}
