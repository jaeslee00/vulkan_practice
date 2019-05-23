/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_command_buffers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:21:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/22 11:54:20 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_command_buffers(t_vulkan *vk)
{
	uint32_t	i;

	vk->command_buffers =
		(VkCommandBuffer*)malloc(vk->swapchain_image_count * sizeof(VkCommandBuffer));
	VkCommandBufferAllocateInfo	allocate_info = {};
	allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocate_info.commandPool = vk->command_pool;
	allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocate_info.commandBufferCount = vk->swapchain_image_count;
	ft_assert((vkAllocateCommandBuffers(vk->logical_device, &allocate_info,
				vk->command_buffers) == VK_SUCCESS),
					"failed to allocate commandbuffer", "command_buffers.c", 25);

	i = 0;
	while (i < vk->swapchain_image_count)
	{
		VkCommandBufferBeginInfo	begin_info = {};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	// 	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		vkBeginCommandBuffer(vk->command_buffers[i], &begin_info);

		VkClearColorValue		color = {48.f / 255.f, 10.f / 255.f,  36.f / 255.f, 1};
		VkClearValue			clear_color = {color};
		VkRenderPassBeginInfo	begin_pass = {};
		begin_pass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		begin_pass.renderPass = vk->renderpass;
		begin_pass.framebuffer = vk->frame_buffers[i];
		begin_pass.renderArea.extent.width = vk->swapchain_extent.width;
		begin_pass.renderArea.extent.height = vk->swapchain_extent.height;
		begin_pass.clearValueCount = 1;
		begin_pass.pClearValues = &clear_color;
			vkCmdBeginRenderPass(vk->command_buffers[i], &begin_pass, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(vk->command_buffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vk->graphics_pipeline);
				VkDeviceSize	offsets[] = {0};
				vkCmdBindVertexBuffers(vk->command_buffers[i], 0, 1, &vk->vertex_buffer, offsets);
				vkCmdBindIndexBuffer(vk->command_buffers[i], vk->index_buffer, 0, VK_INDEX_TYPE_UINT32);
				vkCmdBindDescriptorSets(vk->command_buffers[i],
					VK_PIPELINE_BIND_POINT_GRAPHICS, vk->pipeline_layout,
						0, 1, &vk->descriptor_sets[i], 0, NULL);

				vkCmdDrawIndexed(vk->command_buffers[i], 12, 1, 0, 0, 0);

			vkCmdEndRenderPass(vk->command_buffers[i]);

		ft_assert((vkEndCommandBuffer(vk->command_buffers[i]) == VK_SUCCESS),
					"failed to recod cmd buffer", "command_buffers", 57);
		i++;
	}
}

void	create_command_pools(t_vulkan *vk)
{
	VkCommandPool	command_pool;
	VkCommandPoolCreateInfo cmd_pool_info = {};

	cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_info.queueFamilyIndex = vk->graphics_queue_family_index;
	cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	ft_assert((vkCreateCommandPool(vk->logical_device, &cmd_pool_info, NULL, &vk->command_pool) == VK_SUCCESS),
				"failed to create command pool!", "command_buffers", 67);
}

void	create_command_pool_transfer(t_vulkan *vk)
{
	VkCommandPool command_pool;
	VkCommandPoolCreateInfo cmd_pool_info = {};

	cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmd_pool_info.queueFamilyIndex = vk->transfer_queue_family_index;
	printf("transfer_queue index :: %u\n", cmd_pool_info.queueFamilyIndex);
	cmd_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	ft_assert((vkCreateCommandPool(vk->logical_device, &cmd_pool_info, NULL, &vk->command_pool_transfer) == VK_SUCCESS),
				"failed to create command pool!", "command_buffers", 67);

}
