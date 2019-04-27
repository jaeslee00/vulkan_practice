/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:39:19 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 11:25:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vulkan.h"

VkVertexInputBindingDescription get_binding_description(void)
{
	VkVertexInputBindingDescription binding_descriptions = {};

	binding_descriptions.binding = 0;
	binding_descriptions.stride = sizeof(t_vertex);
	binding_descriptions.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return (binding_descriptions);
}

VkVertexInputAttributeDescription *get_attr_description(void)
{
	VkVertexInputAttributeDescription	*attr_descriptions;

	attr_descriptions =
		(VkVertexInputAttributeDescription*)malloc(2 * sizeof(VkVertexInputAttributeDescription));

	attr_descriptions[0].binding = 0;
	attr_descriptions[0].location = 0;
	attr_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attr_descriptions[0].offset = offsetof(t_vertex, pos);

	attr_descriptions[1].binding = 0;
	attr_descriptions[1].location = 1;
	attr_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attr_descriptions[1].offset = offsetof(t_vertex, color);
	return (attr_descriptions);
}

void	create_graphics_pipeline(t_vulkan *vulkan)
{
	VkShaderModule					vertex_shader;
	VkShaderModule					fragment_shader;

	vertex_shader = get_shader_module(vulkan, "shaders/vert.spv");
	fragment_shader = get_shader_module(vulkan, "shaders/frag.spv");

	VkPipelineShaderStageCreateInfo vtx_shader_info = {};
	vtx_shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vtx_shader_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vtx_shader_info.module = vertex_shader;
	vtx_shader_info.pName = "main";

	VkPipelineShaderStageCreateInfo frag_shader_info = {};
	frag_shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	frag_shader_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	frag_shader_info.module = fragment_shader;
	frag_shader_info.pName = "main";

	VkPipelineShaderStageCreateInfo shader_stages[2];
	shader_stages[0] = vtx_shader_info;
	shader_stages[1] = frag_shader_info;



	VkPipelineVertexInputStateCreateInfo	vertex_input_info = {};
	VkVertexInputBindingDescription			binding_descriptions;
	VkVertexInputAttributeDescription		*attr_descriptions;

	binding_descriptions = get_binding_description();
	attr_descriptions = get_attr_description();
	vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertex_input_info.vertexBindingDescriptionCount = 1;
	vertex_input_info.pVertexBindingDescriptions = &binding_descriptions;
	vertex_input_info.vertexAttributeDescriptionCount = 2;
	vertex_input_info.pVertexAttributeDescriptions = attr_descriptions;

	VkPipelineInputAssemblyStateCreateInfo	input_assembley_info = {};
	input_assembley_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	input_assembley_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	input_assembley_info.primitiveRestartEnable = VK_FALSE;

	VkPipelineTessellationStateCreateInfo tesselinfo = {};
	tesselinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

	VkViewport	viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = vulkan->swapchain_extent.width;
	viewport.height = vulkan->swapchain_extent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset.x = 0;
	scissor.offset.y = 0;
	scissor.extent = vulkan->swapchain_extent;

	VkPipelineViewportStateCreateInfo	viewport_state_info = {};
	viewport_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewport_state_info.viewportCount = 1;
	viewport_state_info.pViewports = &viewport;
	viewport_state_info.scissorCount = 1;
	viewport_state_info.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo	rasterizer_info = {};
	rasterizer_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer_info.depthClampEnable = VK_FALSE;
	rasterizer_info.rasterizerDiscardEnable = VK_FALSE;
	rasterizer_info.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer_info.lineWidth = 1.0f;
	rasterizer_info.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer_info.depthBiasEnable = VK_FALSE;
	rasterizer_info.depthBiasConstantFactor = 0.0f;
	rasterizer_info.depthBiasClamp = 0.0f;
	rasterizer_info.depthBiasSlopeFactor = 0.0f;

	VkPipelineMultisampleStateCreateInfo	multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f; // Optional
	multisampling.pSampleMask = NULL; // Optional
	multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	multisampling.alphaToOneEnable = VK_FALSE; // Optional

	VkPipelineColorBlendAttachmentState color_blend_attachment = {};
	color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
		VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	color_blend_attachment.blendEnable = VK_FALSE;
	color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	color_blend_attachment.colorBlendOp = VK_BLEND_OP_SUBTRACT;
	color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	color_blend_attachment.alphaBlendOp = VK_BLEND_OP_SUBTRACT;

	VkPipelineDepthStencilStateCreateInfo depth_stencilstate = {};
	depth_stencilstate.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;


	VkPipelineColorBlendStateCreateInfo	color_blend_info = {};
	color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	color_blend_info.logicOpEnable = VK_FALSE;
	color_blend_info.attachmentCount = 1;
	color_blend_info.pAttachments = &color_blend_attachment;
	color_blend_info.blendConstants[0] = 0.0f;
	color_blend_info.blendConstants[1] = 0.0f;
	color_blend_info.blendConstants[2] = 0.0f;
	color_blend_info.blendConstants[3] = 0.0f;

	VkPipelineLayoutCreateInfo		pipeline_layout_info = {};
	pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipeline_layout_info.setLayoutCount = 0;
	pipeline_layout_info.pSetLayouts = NULL;
	pipeline_layout_info.pushConstantRangeCount = 0;
	pipeline_layout_info.pPushConstantRanges = NULL;

	ft_assert((vkCreatePipelineLayout(vulkan->logical_device,
		&pipeline_layout_info, NULL, &vulkan->pipeline_layout) == VK_SUCCESS),
			"create pipeline_layout failed... T_T", "graphics_pipeline.c", 169);

	VkGraphicsPipelineCreateInfo	pipeline_info = {};
	pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline_info.stageCount = sizeof(shader_stages) / sizeof(shader_stages[0]);
	pipeline_info.pStages = shader_stages;
	pipeline_info.pVertexInputState = &vertex_input_info;
	pipeline_info.pInputAssemblyState = &input_assembley_info;
	pipeline_info.pTessellationState = &tesselinfo;
	pipeline_info.pViewportState = &viewport_state_info;
	pipeline_info.pRasterizationState = &rasterizer_info;
	pipeline_info.pMultisampleState = &multisampling;
	pipeline_info.pDepthStencilState = &depth_stencilstate;
	pipeline_info.pColorBlendState = &color_blend_info;
	pipeline_info.layout = vulkan->pipeline_layout;
	pipeline_info.renderPass = vulkan->renderpass;
	pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipeline_info.basePipelineIndex = -1; // Optional

	ft_assert((vkCreateGraphicsPipelines(vulkan->logical_device, VK_NULL_HANDLE, 1,
		&pipeline_info, NULL, &vulkan->graphics_pipeline) == VK_SUCCESS),
			"create graphics pipeline failed.!", "graphics_pipeline.c", 189);

	vkDestroyShaderModule(vulkan->logical_device, vertex_shader, NULL);
	vkDestroyShaderModule(vulkan->logical_device, fragment_shader, NULL);
}


/*
    void create_graphics_pipeline(t_vulkan *vulkan)
{
        VkShaderModule vertShaderModule = get_shader_module(vulkan, "./shaders/vert.spv");
        VkShaderModule fragShaderModule = get_shader_module(vulkan, "./shaders/frag.spv");

        VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertShaderStageInfo.module = vertShaderModule;
        vertShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragShaderStageInfo.module = fragShaderModule;
        fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexBindingDescriptionCount = 0;
        vertexInputInfo.vertexAttributeDescriptionCount = 0;

        VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = vulkan->swapchain_extent.width;
        viewport.height = vulkan->swapchain_extent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor = {};
        scissor.offset.x = 0;
		scissor.offset.y = 0;
        scissor.extent = vulkan->swapchain_extent;

        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer = {};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling = {};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending = {};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pushConstantRangeCount = 0;

        vkCreatePipelineLayout(vulkan->logical_device, &pipelineLayoutInfo, NULL, &vulkan->pipeline_layout);

        VkGraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = vulkan->pipeline_layout;
        pipelineInfo.renderPass = vulkan->renderpass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        vkCreateGraphicsPipelines(vulkan->logical_device, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &vulkan->graphics_pipeline);
}
*/
