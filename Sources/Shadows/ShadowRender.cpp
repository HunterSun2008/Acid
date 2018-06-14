#include "ShadowRender.hpp"

#include "Meshes/Mesh.hpp"

namespace fl
{
	ShadowRender::ShadowRender() :
		Component(),
		m_descriptorSet(DescriptorsHandler()),
		m_uniformObject(UniformHandler())
	{
	}

	ShadowRender::~ShadowRender()
	{
	}

	void ShadowRender::Update()
	{
		// Updates uniforms.
		m_uniformObject.Push("transform", GetGameObject()->GetTransform()->GetWorldMatrix());
	}

	void ShadowRender::Load(LoadedValue *value)
	{
	}

	void ShadowRender::Write(LoadedValue *value)
	{
	}

	void ShadowRender::CmdRender(const CommandBuffer &commandBuffer, const Pipeline &pipeline, UniformHandler &uniformScene)
	{
		// Gets required components.
		auto mesh = GetGameObject()->GetComponent<Mesh>();

		if (mesh == nullptr || mesh->GetModel() == nullptr)
		{
			return;
		}

		// Updates descriptors.
		m_descriptorSet.Push("UboScene", uniformScene);
		m_descriptorSet.Push("UboObject", m_uniformObject);
		bool updateSuccess = m_descriptorSet.Update(pipeline);

		if (!updateSuccess)
		{
			return;
		}

		// Draws the object.
		m_descriptorSet.BindDescriptor(commandBuffer);
		mesh->GetModel()->CmdRender(commandBuffer);
	}
}