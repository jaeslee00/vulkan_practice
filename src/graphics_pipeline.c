/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:39:19 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/14 23:01:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vulkan.h"

size_t			load_file(char **code, const char *path)
{
	FILE	*file;
	long	file_size;
	char	*spv_code;

	file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	printf("%s file_size : %ld\n", path, file_size);
	spv_code = (char *)malloc(file_size + 1);
	fread(spv_code, file_size, 1, file);
	fclose(file);
	spv_code[file_size] = 0;
	*code = spv_code;
	return ((size_t)file_size);
}

VkShaderModule	get_shader_module(t_vulkan *vulkan, const char *path)
{
	char						*spv_code;
	size_t						size;
	VkShaderModuleCreateInfo	shader_module_info = {};
	VkShaderModule				module;

	size = load_file(&spv_code, path);
	shader_module_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shader_module_info.codeSize = size;
	shader_module_info.pCode = (uint32_t*)spv_code;
	if (vkCreateShaderModule(vulkan->logical_device, &shader_module_info, NULL, &module))
		printf("shader module %s successfully created.\n", path);
	free(spv_code);
	return (module);
}

void	create_graphics_pipeline(t_vulkan *vulkan)
{
	VkShaderModule					vertex_shader;
	VkShaderModule					fragment_shader;
	VkPipelineShaderStageCreateInfo	shader_stage[2];

	vertex_shader = get_shader_module(vulkan, "shaders/vert.spv");
	fragment_shader = get_shader_module(vulkan, "shaders/frag.spv");

	ft_bzero(shader_stage, sizeof(VkPipelineShaderStageCreateInfo));
	shader_stage[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shader_stage[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shader_stage[0].module = vertex_shader;
	shader_stage[0].pName = "main";

	shader_stage[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shader_stage[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shader_stage[1].module = fragment_shader;
	shader_stage[1].pName = "main";

	VkPipelineVertexInputStateCreateInfo	vertex_input_info = {};
	vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertex_input_info.vertexBindingDescriptionCount = 0;
	vertex_input_info.pVertexBindingDescriptions = NULL;
	vertex_input_info.vertexAttributeDescriptionCount = 0;
	vertex_input_info.pVertexAttributeDescriptions = NULL;

	VkPipelineInputAssemblyStateCreateInfo	input_assembley_info = {};
	input_assembley_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	input_assembley_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	input_assembley_info.primitiveRestartEnable = VK_FALSE;

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

	VkPipelineColorBlendStateCreateInfo	color_blend_info = {};
	color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	color_blend_info.logicOpEnable = VK_FALSE;
	color_blend_info.attachmentCount = 1;
	color_blend_info.pAttachments = &color_blend_attachment;
	color_blend_info.blendConstants[0] = 0.0f;
	color_blend_info.blendConstants[1] = 0.0f;
	color_blend_info.blendConstants[2] = 0.0f;
	color_blend_info.blendConstants[3] = 0.0f;

	VkDynamicState	dynamic_state[2];
	dynamic_state[0] = VK_DYNAMIC_STATE_LINE_WIDTH;
	dynamic_state[1] = VK_DYNAMIC_STATE_VIEWPORT;

	VkPipelineDynamicStateCreateInfo	dynamic_state_info = {};
	dynamic_state_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamic_state_info.dynamicStateCount = 2;
	dynamic_state_info.pDynamicStates = dynamic_state;

	VkPipelineLayoutCreateInfo		pipeline_layout_info = {};
	pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipeline_layout_info.setLayoutCount = 0;
	pipeline_layout_info.pSetLayouts = NULL;
	pipeline_layout_info.pushConstantRangeCount = 0;
	pipeline_layout_info.pPushConstantRanges = NULL;

	if (vkCreatePipelineLayout(vulkan->logical_device,
		&pipeline_layout_info, NULL, &vulkan->pipeline_layout) != VK_SUCCESS)
		printf("create pipeline_layout failed... T_T\n");

	VkGraphicsPipelineCreateInfo	pipeline_info = {};
	pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline_info.stageCount = 2;
	pipeline_info.pStages = shader_stage;
	pipeline_info.pVertexInputState = &vertex_input_info;
	pipeline_info.pViewportState = &viewport_state_info;
	pipeline_info.pRasterizationState = &rasterizer_info;
	pipeline_info.pMultisampleState = &multisampling;
	pipeline_info.pColorBlendState = &color_blend_info;
	pipeline_info.pDynamicState = &dynamic_state_info;
	pipeline_info.layout = vulkan->pipeline_layout;
	pipeline_info.renderPass = vulkan->render_pass;
	pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipeline_info.basePipelineIndex = -1; // Optional

	if (vkCreateGraphicsPipelines(vulkan->logical_device, VK_NULL_HANDLE, 1,
		&pipeline_info, NULL, &vulkan->graphics_pipeline) != VK_SUCCESS)
		printf("create graphics pipeline failed.!\n");

	//vkDestroyShaderModule(vulkan->logical_device, vertex_shader, nullptr);
	//vkDestroyShaderModule(vulkan->logical_device, fragment_shader, nullptr);
}
