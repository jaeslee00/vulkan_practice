/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_command_buffers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:21:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/13 17:35:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_command_buffers(t_vulkan *vulkan)
{
	uint32_t	i;

	vulkan->command_buffers =
		(VkCommandBuffer*)malloc(vulkan->swapchain_image_count * sizeof(VkCommandBuffer));
	VkCommandBufferAllocateInfo	allocate_info = {};
	allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocate_info.commandPool = vulkan->command_pool;
	allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocate_info.commandBufferCount = vulkan->swapchain_image_count;
	ft_assert((vkAllocateCommandBuffers(vulkan->logical_device, &allocate_info,
				vulkan->command_buffers) == VK_SUCCESS),
					"failed to allocate commandbuffer", "command_buffers.c", 25);

	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		VkCommandBufferBeginInfo	begin_info = {};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	// 	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		vkBeginCommandBuffer(vulkan->command_buffers[i], &begin_info);

		VkClearColorValue		color = {48.f / 255.f, 10.f / 255.f,  36.f / 255.f, 1};
		VkClearValue			clear_color = {color};
		VkRenderPassBeginInfo	begin_pass = {};
		begin_pass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		begin_pass.renderPass = vulkan->renderpass;
		begin_pass.framebuffer = vulkan->frame_buffers[i];
		begin_pass.renderArea.extent.width = vulkan->swapchain_extent.width;
		begin_pass.renderArea.extent.height = vulkan->swapchain_extent.height;
		begin_pass.clearValueCount = 1;
		begin_pass.pClearValues = &clear_color;
			vkCmdBeginRenderPass(vulkan->command_buffers[i], &begin_pass, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(vulkan->command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan->graphics_pipeline);
					VkDeviceSize	offsets[] = {0};
					vkCmdBindVertexBuffers(vulkan->command_buffers[i], 0, 1, &vulkan->vertex_buffer, offsets);
					vkCmdBindIndexBuffer(vulkan->command_buffers[i], vulkan->index_buffer, 0, VK_INDEX_TYPE_UINT32);
				//vkCmdDraw(vulkan->command_buffers[i], vulkan->triangle.length, 1, 0, 0);
				//	vkCmdBindDescriptorSets(vulkan->command_buffers[i],
				//		VK_PIPELINE_BIND_POINT_GRAPHICS, vulkan->pipeline_layout,
				//			0, 1, &vulkan->descriptor_set[i], 0, NULL);
					vkCmdDrawIndexed(vulkan->command_buffers[i], 6, 1, 0, 0, 0);

			vkCmdEndRenderPass(vulkan->command_buffers[i]);

		ft_assert((vkEndCommandBuffer(vulkan->command_buffers[i]) == VK_SUCCESS),
					"failed to recod cmd buffer", "command_buffers", 57);
		i++;
	}
}

void	create_command_pools(t_vulkan *vulkan)
{
	VkCommandPool	command_pool;
	VkCommandPoolCreateInfo cmd_pool_info = {};

	cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_info.queueFamilyIndex = vulkan->graphics_queue_family_index;
	cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	ft_assert((vkCreateCommandPool(vulkan->logical_device, &cmd_pool_info, NULL, &vulkan->command_pool) == VK_SUCCESS),
				"failed to create command pool!", "command_buffers", 67);
}

void	create_command_pool_transfer(t_vulkan *vulkan)
{
	VkCommandPool command_pool;
	VkCommandPoolCreateInfo cmd_pool_info = {};

	cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_info.queueFamilyIndex = vulkan->transfer_queue_family_index;
	printf("transfer_queue index :: %u\n", cmd_pool_info.queueFamilyIndex);
	cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	ft_assert((vkCreateCommandPool(vulkan->logical_device, &cmd_pool_info, NULL, &vulkan->command_pool_transfer) == VK_SUCCESS),
				"failed to create command pool!", "command_buffers", 67);

}
