/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_buffers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:21:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/26 02:22:59 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
/*
void	create_command_buffers(t_vulkan *vulkan)
{
	VkCommandBufferAllocateInfo		alloc_info = {};
	uint32_t						index;

	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.commandPool = vulkan->command_pool;
	alloc_info.commandBufferCount = vulkan->swapchain_image_count;
	vulkan->command_buffers = (VkCommandBuffer*)malloc(vulkan->swapchain_image_count *
								sizeof(VkCommandBuffer));

	if (vkAllocateCommandBuffers(vulkan->logical_device, &alloc_info,
									vulkan->command_buffers) != VK_SUCCESS)
		printf("allocating command buffers failed\n");
	index = 0;
	while (index < vulkan->swapchain_image_count)
	{
		 VkCommandBufferBeginInfo begin_info = {};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		begin_info.pInheritanceInfo = NULL; // Optional

		if (vkBeginCommandBuffer(vulkan->command_buffers[index], &begin_info) != VK_SUCCESS)
		{
			printf("failed to begin recording command buffer!\n");
		}
		VkRenderPassBeginInfo render_pass_info = {};
		render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		render_pass_info.renderPass = vulkan->render_pass;
		render_pass_info.framebuffer = vulkan->frame_buffers[index];
		render_pass_info.renderArea.offset.x = 0;
		render_pass_info.renderArea.offset.y = 0;
		render_pass_info.renderArea.extent = vulkan->swapchain_extent;

		VkClearValue clear_color = {0.0f, 0.0f, 0.0f, 1.0f};

		render_pass_info.clearValueCount = 1;
		render_pass_info.pClearValues = &clear_color;
		vkCmdBeginRenderPass(vulkan->command_buffers[index], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(vulkan->command_buffers[index], VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan->graphics_pipeline);
		vkCmdDraw(vulkan->command_buffers[index], 3, 1, 0, 0);
		vkCmdEndRenderPass(vulkan->command_buffers[index]);
		if (vkEndCommandBuffer(vulkan->command_buffers[index]) != VK_SUCCESS)
		{
			printf("failed to record command buffer!\n");
		}
		index++;
	}
	printf("nbr of cmd buffers : %u\n", index);
}*/

void	create_command_pools(t_vulkan *vulkan)
{
	VkCommandPool	command_pool;
	VkCommandPoolCreateInfo cmd_pool_info = {};

	cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_info.queueFamilyIndex = vulkan->graphics_queue_family_index;
	cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	if (vkCreateCommandPool(vulkan->logical_device, &cmd_pool_info, NULL, &vulkan->command_pool) != VK_SUCCESS)
	{
		printf("failed to create command pool!\n");
	}
}
