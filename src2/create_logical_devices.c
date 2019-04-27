/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_devices.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:17:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 13:20:58 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


void	create_logical_devices(t_vulkan *vulkan)
{
	float						queue_priority;
	VkPhysicalDeviceFeatures	features; /*TODO must be modified to add functionalities in rasterizer */
	VkDeviceQueueCreateInfo		queue_info[2];
	VkDeviceCreateInfo			logical_device_info = {};

	queue_priority = 1.0f;

	queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info[0].pNext = NULL;
	queue_info[0].queueFamilyIndex = vulkan->graphics_queue_family_index;
	printf("trns qu : %u\n", queue_info[0].queueFamilyIndex);
	queue_info[0].queueCount = 1;
	queue_info[0].pQueuePriorities = &queue_priority;
	queue_info[0].flags = 0;

	queue_info[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info[1].pNext = NULL;
	queue_info[1].queueFamilyIndex = vulkan->transfer_queue_family_index;
	printf("trns qu : %u\n", queue_info[1].queueFamilyIndex);
	queue_info[1].queueCount = 1;
	queue_info[1].pQueuePriorities = &queue_priority;
	queue_info[1].flags = 0;

	logical_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	logical_device_info.pNext = NULL;
	logical_device_info.queueCreateInfoCount = 2;
	logical_device_info.pQueueCreateInfos = queue_info;
	ft_memset(&features, VK_FALSE, sizeof(features));
	logical_device_info.pEnabledFeatures = &features;
	logical_device_info.enabledExtensionCount = vulkan->device_extension_count;
	logical_device_info.ppEnabledExtensionNames = (const char *const *)vulkan->device_extension_name;

	ft_assert((vkCreateDevice(vulkan->gpu[0], &logical_device_info,
					NULL, &vulkan->logical_device) == VK_SUCCESS),
						"failed to create logical device!", "create_logical_device.c", 39);
	printf("nbr of queues in the queueFamily : %u\n", vulkan->queue_props[0].queueCount);
	vulkan->queue_family_indices[0] = 0;
	vulkan->queue_family_indices[1] = 1;
}
