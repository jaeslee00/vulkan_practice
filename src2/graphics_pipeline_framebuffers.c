/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_pipeline_framebuffers.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:39:19 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/13 22:07:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vulkan.h"

void	create_framebuffers(t_vulkan *vk)
{
	uint32_t	index;

	index = 0;
	vk->frame_buffers =
		(VkFramebuffer*)malloc(vk->swapchain_image_count * sizeof(VkFramebuffer));

	while (index < vk->swapchain_image_count)
	{
		VkFramebufferCreateInfo	create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		create_info.renderPass = vk->renderpass;
		create_info.attachmentCount = 2;
		create_info.pAttachments =
			(VkImageView[]){vk->swapchain_imageviews[index], vk->depth_image_view}; // 씨바ㅏ다아아아아알ㄹ 주소르 ㄹ제대ㅗㄹ 안정해줘서 망함
		create_info.width = vk->swapchain_extent.width;
		create_info.height = vk->swapchain_extent.height;
		create_info.layers = 1;
		ft_assert((vkCreateFramebuffer(vk->logical_device,
			&create_info, NULL, &vk->frame_buffers[index]) == VK_SUCCESS),
			"failed to create frame buffers", "example.c", 73);
		index++;
	}
}

void	create_graphics_pipeline(t_vulkan *vk)
{
	VkShaderModule					vertex_shader;
	VkShaderModule					fragment_shader;

	vertex_shader = get_shader_module(vk, "/Users/jaelee/42/vv/vert.spv");
	fragment_shader = get_shader_module(vk, "/Users/jaelee/42/vv/frag.spv");

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
	vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertex_input_info.vertexBindingDescriptionCount = 1;
	vertex_input_info.pVertexBindingDescriptions = &binding_descriptions;
	vertex_input_info.vertexAttributeDescriptionCount = 3;
	vertex_input_info.pVertexAttributeDescriptions =
		(VkVertexInputAttributeDescription[]){
			get_position_attirbutes(), get_color_attributes(), get_tex_coord_attirbutes()};

	VkPipelineInputAssemblyStateCreateInfo	input_assembley_info = {};
	input_assembley_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	input_assembley_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	input_assembley_info.primitiveRestartEnable = VK_FALSE;

	VkPipelineTessellationStateCreateInfo tesselinfo = {};
	tesselinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;

	VkViewport	viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = vk->swapchain_extent.width;
	viewport.height = vk->swapchain_extent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.offset.x = 0;
	scissor.offset.y = 0;
	scissor.extent = vk->swapchain_extent;

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
	rasterizer_info.polygonMode = VK_POLYGON_MODE_LINE;
	rasterizer_info.lineWidth = 1.0f;
	rasterizer_info.cullMode = VK_CULL_MODE_FRONT_AND_BACK; /* TODO study over!! */
	rasterizer_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE; /* TODO study over!! */
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
	color_blend_attachment.blendEnable = VK_TRUE;
	color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	color_blend_attachment.colorBlendOp = VK_BLEND_OP_SUBTRACT;
	color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	color_blend_attachment.alphaBlendOp = VK_BLEND_OP_SUBTRACT;

	VkPipelineDepthStencilStateCreateInfo depth_stencilstate = {};
	depth_stencilstate.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depth_stencilstate.depthTestEnable = VK_TRUE;
	depth_stencilstate.depthWriteEnable = VK_TRUE;
	depth_stencilstate.depthCompareOp = VK_COMPARE_OP_LESS;
	depth_stencilstate.depthBoundsTestEnable = VK_FALSE;
	depth_stencilstate.minDepthBounds = 0.0f; // Optional
	depth_stencilstate.maxDepthBounds = 1.0f; // Optional
	depth_stencilstate.stencilTestEnable = VK_FALSE;

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
	pipeline_layout_info.setLayoutCount = 1;
	pipeline_layout_info.pSetLayouts = &vk->descriptor_set_layout;
	pipeline_layout_info.pushConstantRangeCount = 0;
	pipeline_layout_info.pPushConstantRanges = NULL;

	ft_assert((vkCreatePipelineLayout(vk->logical_device,
		&pipeline_layout_info, NULL, &vk->pipeline_layout) == VK_SUCCESS),
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
	pipeline_info.layout = vk->pipeline_layout;
	pipeline_info.renderPass = vk->renderpass;
	pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipeline_info.basePipelineIndex = -1; // Optional

	ft_assert((vkCreateGraphicsPipelines(vk->logical_device, VK_NULL_HANDLE, 1,
		&pipeline_info, NULL, &vk->graphics_pipeline) == VK_SUCCESS),
			"create graphics pipeline failed.!", "graphics_pipeline.c", 189);

	vkDestroyShaderModule(vk->logical_device, vertex_shader, NULL);
	vkDestroyShaderModule(vk->logical_device, fragment_shader, NULL);
}
