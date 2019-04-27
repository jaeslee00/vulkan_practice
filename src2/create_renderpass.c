/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_renderpass.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:29:11 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 05:42:58 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_renderpass(t_vulkan *vulkan)
{
	VkAttachmentDescription	attachments[1];
	attachments[0].flags =  0;
	attachments[0].format = vulkan->format;
	attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference	color_attachments_ref = {};
	color_attachments_ref.attachment = 0; /* index of attachments */
	color_attachments_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription	subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &color_attachments_ref;

	// VkSubpassDependency dependency = {};
	// dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	// dependency.dstSubpass = 0;
	// dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	// dependency.srcAccessMask = 0;
	// dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	// dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
	// 								VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo	create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	create_info.attachmentCount = 1;
	create_info.pAttachments = attachments;
	create_info.subpassCount = 1;
	create_info.pSubpasses = &subpass;
	// create_info.dependencyCount = 1;
	// create_info.pDependencies = &dependency;

	ft_assert((vkCreateRenderPass(vulkan->logical_device, &create_info, NULL, &vulkan->renderpass) == VK_SUCCESS),
				"failed to create renderpass", "create_renderpass.c", 55);
}
