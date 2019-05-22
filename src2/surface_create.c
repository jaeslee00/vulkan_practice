/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:45:21 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/22 10:25:48 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void		surface_support_check(t_vulkan *vk)
{
	uint32_t	index;
	VkBool32	surface_support;

	surface_support = VK_FALSE;
	index = 0;
	while (index < vk->queue_family_count) //vk->queue_family_count)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(vk->gpu[0], index, vk->surf, &surface_support);
		if (surface_support != VK_FALSE)
		{
			printf("good surface is supported in the queue of the device\nindex: %u\n", index);
			vk->present_queue_family_index = index;
			break ;
		}
		index++;
	}
	printf("index of present queue fimaly : %u\n", index);
}

void	create_surface(t_vulkan *vk)
{
	vk->surf = NULL;
	if (glfwCreateWindowSurface(vk->instance, vk->window, NULL, &vk->surf) != VK_SUCCESS)
		printf("failed to crate window surface!\n");
	surface_support_check(vk);
}
