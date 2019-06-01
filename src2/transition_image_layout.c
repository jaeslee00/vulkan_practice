/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_image_layout.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 21:22:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/29 23:54:24 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	transition_image_layout(t_vulkan *vk, VkImage image, VkFormat format,
			VkImageLayout old_layout, VkImageLayout new_layout)
{
	VkCommandBuffer		command_buffer;

	command_buffer = begin_singletime_commands(vk);

	VkImageMemoryBarrier	barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.image = image;
	barrier.oldLayout = old_layout;
	barrier.newLayout = new_layout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.layerCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
 	barrier.srcAccessMask = 0;
	barrier.dstAccessMask  = 0;

	end_singletime_commands(vk, command_buffer);
}
