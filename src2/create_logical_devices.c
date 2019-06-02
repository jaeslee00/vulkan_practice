/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_logical_devices.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:17:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 16:21:13 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	check_queue_family(t_vulkan *vk)
{
	uint32_t	queue_family_index;
	VkBool32	present_support;
	int			exit_flag;

	vk->queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(vk->gpu[0], &vk->queue_family_count, NULL);
	printf("nbr of queueFamily : %u\n", vk->queue_family_count);
	vk->queue_props =
		(VkQueueFamilyProperties*)malloc(vk->queue_family_count * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(vk->gpu[0], &vk->queue_family_count, vk->queue_props);

	printf("nbr of queues in queueFamily : %u\n", vk->queue_props[0].queueCount);
	printf("capabilities of the queue in the queueFamily : %u\n", vk->queue_props[0].queueFlags);
	/*
		capabilities of the queue in the queueFamily : 1 = VK_QUEUE_GRAPHICS_BIT
		capabilities of the queue in the queueFamily : 2 = VK_QUEUE_COMPUTE_BIT
		capabilities of the queue in the queueFamily : 4 = VK_QUEUE_TRANSFER_BIT
	*/
	queue_family_index = 0;
	exit_flag = 0;
	while (queue_family_index < vk->queue_family_count)
	{
		if (exit_flag == 0b11)
			break ;
		vkGetPhysicalDeviceSurfaceSupportKHR(vk->gpu[0], queue_family_index, vk->surf, &present_support);
		if (vk->queue_props[queue_family_index].queueCount > 0 && present_support)
		{
			exit_flag |= 0b01;
			vk->present_queue_family_index = queue_family_index;
		}
		if (vk->queue_props[queue_family_index].queueCount > 0
			&& vk->queue_props[queue_family_index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			exit_flag |= 0b10;
			vk->graphics_queue_family_index = queue_family_index;
		}
		queue_family_index++;
	}
	printf("index of graphics queue fimaly : %u\n", vk->graphics_queue_family_index);
	printf("index of present queue fimaly : %u\n", vk->present_queue_family_index);
}

void	create_logical_devices(t_vulkan *vk)
{
	float						queue_priority;
	VkPhysicalDeviceFeatures	features; /*TODO must be modified to add functionalities in rasterizer */
	uint32_t					used_queue_family_count;
	VkDeviceQueueCreateInfo		*queue_info;
	VkDeviceCreateInfo			logical_device_info = {};

	queue_priority = 1.0f;
	check_queue_family(vk); /*TODO check if the chosen device supports queue family */
	used_queue_family_count = vk->graphics_queue_family_index == vk->present_queue_family_index ? 1 : 2;
	queue_info = (VkDeviceQueueCreateInfo*)malloc(used_queue_family_count * sizeof(VkDeviceQueueCreateInfo));

	queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info[0].pNext = NULL;
	queue_info[0].queueFamilyIndex = vk->graphics_queue_family_index;
	queue_info[0].queueCount = 1;
	queue_info[0].pQueuePriorities = &queue_priority;
	queue_info[0].flags = 0;

	if (used_queue_family_count == 2)
	{
		queue_info[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_info[1].pNext = NULL;
		queue_info[1].queueFamilyIndex = vk->present_queue_family_index;
		queue_info[1].queueCount = 1;
		queue_info[1].pQueuePriorities = &queue_priority;
		queue_info[1].flags = 0;
	}

	ft_bzero(&features, sizeof(VkPhysicalDeviceFeatures));
	if (vk->dv_feats.fillModeNonSolid)
		features.fillModeNonSolid = VK_TRUE;
	if (vk->dv_feats.samplerAnisotropy)
		features.samplerAnisotropy = VK_TRUE;

	logical_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	logical_device_info.pNext = NULL;
	logical_device_info.queueCreateInfoCount = used_queue_family_count;
	logical_device_info.pQueueCreateInfos = queue_info;
	logical_device_info.pEnabledFeatures = &features;
	logical_device_info.enabledExtensionCount = vk->device_extension_count;
	logical_device_info.ppEnabledExtensionNames = (const char *const *)vk->device_extension_name;

	ft_assert((vkCreateDevice(vk->gpu[0], &logical_device_info,
					NULL, &vk->logical_device) == VK_SUCCESS),
						"failed to create logical device!", "create_logical_device.c", 39);
	printf("Logical device : %u queue(s) used\n", used_queue_family_count);
	vkGetDeviceQueue(vk->logical_device, vk->graphics_queue_family_index, 0, &vk->graphics_queue);
	vkGetDeviceQueue(vk->logical_device, vk->present_queue_family_index, 0, &vk->present_queue);

	free(queue_info);
}
