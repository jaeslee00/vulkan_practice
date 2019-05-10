/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:45:21 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/10 16:34:19 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void		surface_support_check(t_vulkan *vulkan)
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
}

void	create_surface(t_vulkan *vulkan)
{
	vulkan->surf = NULL;
	ft_assert((glfwCreateWindowSurface(vulkan->instance, vulkan->window, NULL, &vulkan->surf) == VK_SUCCESS),
		"failed to crate window surface!", "surface_create.c", 40);
	surface_support_check(vulkan);
}
