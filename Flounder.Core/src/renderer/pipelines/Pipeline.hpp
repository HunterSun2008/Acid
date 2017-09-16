﻿#pragma once

#include <string>

#include "../../platforms/glfw/GlfwVulkan.hpp"
#include "../../shaders/Shader.hpp"

namespace Flounder
{
	enum PipelineType
	{
		PipelinePolygon,
		PipelineNoDepthTest,
		PipelineMrt,
		PipelineMultiTexture
	};

	struct VertexInputState
	{
		uint32_t bindingDescriptionCount;
		uint32_t attributeDescriptionCount;
		VkVertexInputBindingDescription* pVertexBindingDescriptions;
		VkVertexInputAttributeDescription* pVertexAttributeDescriptions;
	};

	/// <summary>
	/// Class that represents a Vulkan pipeline.
	/// </summary>
	class Pipeline
	{
	private:
		static const std::vector<VkDynamicState> DYNAMIC_STATES;

		std::string m_name;
		PipelineType m_pipelineType;
		VertexInputState m_vertexInputState;
		Shader *m_shader;

		VkPipeline m_pipeline;
		VkPipelineLayout m_pipelineLayout;

		VkPipelineInputAssemblyStateCreateInfo m_inputAssemblyState;
		VkPipelineRasterizationStateCreateInfo m_rasterizationState;
		VkPipelineColorBlendAttachmentState m_blendAttachmentState;
		VkPipelineColorBlendStateCreateInfo m_colourBlendState;
		VkPipelineDepthStencilStateCreateInfo m_depthStencilState;
		VkPipelineViewportStateCreateInfo m_viewportState;
		VkPipelineMultisampleStateCreateInfo m_multisampleState;
		VkPipelineDynamicStateCreateInfo m_dynamicState;
	public:
		/// <summary>
		/// Creates a new pipeline.
		/// </summary>
		/// <param name="name"> The pipelines name. </param>
		Pipeline(const std::string &name, const PipelineType &pipelineType, const VertexInputState &vertexInputState, Shader *shader);

		/// <summary>
		/// Deconstructor for the pipeline.
		/// </summary>
		~Pipeline();

		/// <summary>
		/// Creates the pipeline.
		/// </summary>
		void Create(const VkDevice *logicalDevice, VkRenderPass renderPass);

		/// <summary>
		/// Cleans up the shapipelineder.
		/// </summary>
		void Cleanup(const VkDevice *logicalDevice);
	private:
		void CreateAttributes();

		void CreatePipelineLayout(const VkDevice *logicalDevice);

		void CreatePolygonPipeline(const VkDevice *logicalDevice, VkRenderPass renderPass);

		void CreateNoDepthTestPipeline(const VkDevice *logicalDevice, VkRenderPass renderPass);

		void CreateMrtPipeline(const VkDevice *logicalDevice, VkRenderPass renderPass);

		void CreateMultiTexturePipeline(const VkDevice *logicalDevice, VkRenderPass renderPass);
	public:
		/// <summary>
		/// Gets the loaded name for the pipeline.
		/// </summary>
		/// <returns> The pipelines name. </returns>
		std::string GetName() const { return m_name; }

		VkPipeline GetPipeline() const { return m_pipeline; }

		VkPipelineLayout GetPipelineLayout() const { return m_pipelineLayout; }
	};
}
