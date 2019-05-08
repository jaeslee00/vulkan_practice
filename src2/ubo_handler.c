/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ubo_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:08:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/08 18:48:11 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_ubo(t_vulkan *vulkan)
{
	VkDeviceSize	buffer_size;
	uint32_t		i;

	buffer_size = sizeof(t_ubo);
	vulkan->uniform_buffers =
		(VkBuffer*)malloc(vulkan->swapchain_image_count * sizeof(VkBuffer));
	vulkan->uniform_buffers_memory =
		(VkDeviceMemory*)malloc(vulkan->swapchain_image_count * sizeof(VkDeviceMemory));
	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		create_buffer(vulkan, buffer_size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				&vulkan->uniform_buffers[i], &vulkan->uniform_buffers_memory[i]);
		i++;
	}
}
