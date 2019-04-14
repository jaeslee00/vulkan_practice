/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_framebuffers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 22:17:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/14 22:42:14 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_framebuffers(t_vulkan *vulkan)
{
	uint32_t				i;
	VkImageView				*attachments;
	VkFramebufferCreateInfo	framebuffer_info = {};

	vulkan->frame_buffers = (VkFramebuffer*)malloc(vulkan->swapchain_image_count
								* sizeof(VkFramebuffer));
	attachments = (VkImageView*)malloc(vulkan->swapchain_image_count * sizeof(VkImageView));
	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		attachments[i] = vulkan->buffer[i].view;
		i++;
	}

	framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebuffer_info.renderPass = vulkan->render_pass;
	framebuffer_info.attachmentCount = 1;
	framebuffer_info.pAttachments = attachments;
	framebuffer_info.width = vulkan->swapchain_extent.width;
	framebuffer_info.height = vulkan->swapchain_extent.height;
	framebuffer_info.layers = 1;

	if (vkCreateFramebuffer(vulkan->logical_device,
			&framebuffer_info, NULL, vulkan->frame_buffers) != VK_SUCCESS)
		printf("create framebuffer failed!!\n");
}
