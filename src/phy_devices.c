/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_devices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:47:58 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/13 19:33:11 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	surface_support_check(t_vulkan *vulkan)
{
	uint32_t	index;
	VkBool32	surface_support;

	surface_support = VK_FALSE;
	index = 0;

	while (index < 10000000) //vulkan->queue_family_count)
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

void	find_graphics_queue_family(t_vulkan *vulkan)
{
	uint32_t	index;

	vulkan->queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(vulkan->gpu[0], &vulkan->queue_family_count, NULL);
	printf("nbr of queueFamily : %u\n", vulkan->queue_family_count);
	vulkan->queue_props =
		(VkQueueFamilyProperties*)malloc(vulkan->queue_family_count * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(vulkan->gpu[0], &vulkan->queue_family_count, vulkan->queue_props);

	printf("nbr of queues in queueFamily : %u\n", vulkan->queue_props[0].queueCount);
	printf("capabilities of the queue in the queueFamily : %u\n", vulkan->queue_props[0].queueFlags);
	/*
		capabilities of the queue in the queueFamily : 1 = VK_QUEUE_GRAPHICS_BIT
		capabilities of the queue in the queueFamily : 2 = VK_QUEUE_COMPUTE_BIT
		capabilities of the queue in the queueFamily : 4 = VK_QUEUE_TRANSFER_BIT
	*/
	index = 0;
	while (index < vulkan->queue_family_count)
	{
		if (vulkan->queue_props[index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			vulkan->graphics_queue_family_index = index;
			printf("right queueFamily selected!\n");
			break ;
		}
		index++;
	}
	printf("index of graphics queue fimaly : %u\n", index);
}

void	check_devices(t_vulkan *vulkan)
{
	uint32_t	index;
	int			score;

	score = 0;
	index = 0;
	while(index < vulkan->gpu_count)
	{
		vkGetPhysicalDeviceProperties(vulkan->gpu[index], &vulkan->dv_props);
		vkGetPhysicalDeviceFeatures(vulkan->gpu[index], &vulkan->dv_feats);
		printf("%s\n", vulkan->dv_props.deviceName);
		index++;
	}
	if (vulkan->dv_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		printf("good it's a GPU!!\n");
	if (!vulkan->dv_feats.tessellationShader)
		printf("doesn't support tessellation shader... bad..\n");
	score += vulkan->dv_props.limits.maxImageDimension2D;
	printf("score: %d\n", score);
	if (!vulkan->dv_feats.geometryShader)
		printf("doesn't support geometry shader... bad..\n");
}

int		physical_device_select(t_vulkan *vulkan)
{
	VkExtensionProperties	*device_extension;
	uint32_t				device_extension_count;
	uint32_t				i;

	vulkan->gpu_count = 0;
	vkEnumeratePhysicalDevices(vulkan->instance, &vulkan->gpu_count, NULL);
	printf("FOUND %u GPUs\n", vulkan->gpu_count);
	vulkan->gpu = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * vulkan->gpu_count); /*TODO replace vector */
	vkEnumeratePhysicalDevices(vulkan->instance, &vulkan->gpu_count, vulkan->gpu);

	vkEnumerateDeviceExtensionProperties(vulkan->gpu[0], NULL, &device_extension_count, NULL);
	device_extension = (VkExtensionProperties*)malloc(device_extension_count * sizeof(VkExtensionProperties));
	vkEnumerateDeviceExtensionProperties(vulkan->gpu[0], NULL, &device_extension_count, device_extension);

	i = 0;
	while(i < device_extension_count)
	{
		if (!ft_strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, device_extension[i].extensionName))
		{
			vulkan->extension_name[vulkan->enabled_extension_count] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
			vulkan->enabled_extension_count++;
			printf("Swapchain extension is added to extension lists\n");
		}
		i++;
	}
	free(device_extension);

	printf("extension count : %d\n", vulkan->enabled_extension_count);
	for(i=0; i < vulkan->enabled_extension_count; i++)
		printf("extension_name : %s\n", vulkan->extension_name[i]);

	/*TODO recieve properties and features of the vulkan->gpu */
	check_devices(vulkan);
	find_graphics_queue_family(vulkan); /*TODO check if the chosen device supports queue family */
	return (1);
}
