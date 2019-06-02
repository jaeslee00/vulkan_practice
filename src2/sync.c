/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 00:09:58 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/22 10:20:53 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_sync(t_vulkan *vk)
{
	uint32_t	i;

	VkSemaphoreCreateInfo sem_create_info = {};
	sem_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	vk->acquire_semaphore =
		(VkSemaphore*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));
	vk->release_semaphore =
		(VkSemaphore*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));

	VkFenceCreateInfo		fence_info = {};
	fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	vk->fence = (VkFence*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkFence));

	i = 0;
	while (i < MAX_FRAMES_IN_FLIGHT)
	{
		ft_assert(((vkCreateSemaphore(vk->logical_device, &sem_create_info, NULL,
				&vk->acquire_semaphore[i]) == VK_SUCCESS) &&
			(vkCreateSemaphore(vk->logical_device, &sem_create_info, NULL,
				&vk->release_semaphore[i]) == VK_SUCCESS) &&
			(vkCreateFence(vk->logical_device, &fence_info, NULL,
				&vk->fence[i]) == VK_SUCCESS)),
					"failed to create sync obj", "sync.c", 34);
		i++;
	}
}
