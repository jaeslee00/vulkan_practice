/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:45:21 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/14 00:49:07 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	surface_support_check(t_vulkan *vulkan)
{
	uint32_t	index;
	VkBool32	surface_support;

	surface_support = VK_FALSE;
	index = 0;

	while (index < vulkan->queue_family_count) //vulkan->queue_family_count)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(vulkan->gpu[0], index, vulkan->surf, &surface_support);
		if (surface_support != VK_FALSE)
		{
			printf("good surface is supported in the queue of the device\nindex: %u\n", index);
			vulkan->present_queue_family_index = index;
			break ;
		}
		index++;
	}
	printf("index of present queue fimaly : %u\n", index);

	/* retrieve handle of the queue */
	vkGetDeviceQueue(vulkan->logical_device, vulkan->graphics_queue_family_index, 0, &vulkan->graphics_queue);
	vkGetDeviceQueue(vulkan->logical_device, vulkan->present_queue_family_index, 0, &vulkan->present_queue);
}

void	create_surface(t_visualizer *vis, t_vulkan *vulkan)
{
	VkBool32	surfaceSupport;
	if (glfwCreateWindowSurface(vulkan->instance, vis->window, NULL, &vulkan->surf) != VK_SUCCESS)
		printf("failed to crate window surface!\n");
	surface_support_check(vulkan);
}
