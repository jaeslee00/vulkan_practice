/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ubo_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:08:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/17 19:09:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_ubo(t_vulkan *vk)
{
	VkDeviceSize	buffer_size;
	uint32_t		i;

	buffer_size = sizeof(t_ubo);
	vk->uniform_buffers =
		(VkBuffer*)malloc(vk->swapchain_image_count * sizeof(VkBuffer));
	vk->uniform_buffers_memory =
		(VkDeviceMemory*)malloc(vk->swapchain_image_count * sizeof(VkDeviceMemory));
	i = 0;
	while (i < vk->swapchain_image_count)
	{
		create_buffer(vk, buffer_size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				&vk->uniform_buffers[i], &vk->uniform_buffers_memory[i]);
		i++;
	}
}
