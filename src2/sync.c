/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 00:09:58 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 04:18:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_sync(t_vulkan *vulkan)
{
	uint32_t	i;

	VkSemaphoreCreateInfo sem_create_info = {};
	sem_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	vulkan->acquire_semaphore =
		(VkSemaphore*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));
	vulkan->release_semaphore =
		(VkSemaphore*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));

	VkFenceCreateInfo		fence_info = {};
	fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	vulkan->fence = (VkFence*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkFence));

	i = 0;
	while (i < MAX_FRAMES_IN_FLIGHT)
	{
		ft_assert(((vkCreateSemaphore(vulkan->logical_device, &sem_create_info, NULL,
				&vulkan->acquire_semaphore[i]) == VK_SUCCESS) &&
			(vkCreateSemaphore(vulkan->logical_device, &sem_create_info, NULL,
				&vulkan->release_semaphore[i]) == VK_SUCCESS) &&
			(vkCreateFence(vulkan->logical_device, &fence_info, NULL,
				&vulkan->fence[i]) == VK_SUCCESS)),
					"failed to create sync obj", "sync.c", 34);
		i++;
	}
}
