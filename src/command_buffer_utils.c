/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_buffer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:55:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/17 19:09:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

VkCommandBuffer	begin_singletime_commands(t_vulkan *vk)
{
	VkCommandBufferAllocateInfo	alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandPool = vk->command_pool;
	alloc_info.commandBufferCount = 1;

	VkCommandBuffer				command_buffer;
	vkAllocateCommandBuffers(vk->logical_device, &alloc_info, &command_buffer);

	VkCommandBufferBeginInfo	begin_info = {};
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(command_buffer, &begin_info);

	return (command_buffer);
}

void			end_singletime_commands(t_vulkan *vk, VkCommandBuffer command_buffer)
{
	vkEndCommandBuffer(command_buffer);

	VkSubmitInfo	submit_info = {};
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &command_buffer;

	vkQueueSubmit(vk->graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
	vkQueueWaitIdle(vk->graphics_queue);

	vkFreeCommandBuffers(vk->logical_device, vk->command_pool, 1, &command_buffer);
}
