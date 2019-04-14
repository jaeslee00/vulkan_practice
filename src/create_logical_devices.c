/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_devices.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:17:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/14 00:22:03 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


void	create_logical_devices(t_vulkan *vulkan)
{
	float						queue_priority;
	VkPhysicalDeviceFeatures	features;
	VkDeviceQueueCreateInfo		queue_info = {};
	VkDeviceCreateInfo			logical_device_info = {};

	queue_priority = 1.0f;
	queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info.pNext = NULL;
	queue_info.queueFamilyIndex = vulkan->graphics_queue_family_index;
	queue_info.queueCount = 1;
	queue_info.pQueuePriorities = &queue_priority;

	logical_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	logical_device_info.pNext = NULL;
	logical_device_info.queueCreateInfoCount = 1;
	logical_device_info.pQueueCreateInfos = &queue_info;
	ft_memset(&features, VK_FALSE, sizeof(features));
	logical_device_info.pEnabledFeatures = &features;
	logical_device_info.enabledExtensionCount = vulkan->device_extension_count;
	logical_device_info.ppEnabledExtensionNames = (const char *const *)vulkan->device_extension_name;

	if (vkCreateDevice(vulkan->gpu[0], &logical_device_info, NULL, &vulkan->logical_device) != VK_SUCCESS)
		printf("failed to create logical device!\n");
	printf("createDevice Success\n");
	printf("nbr of queues in the queueFamily : %u\n", vulkan->queue_props[0].queueCount);
}
