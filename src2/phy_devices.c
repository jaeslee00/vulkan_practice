/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_devices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:47:58 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/02 13:44:30 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

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
	index = 0;
	while (index < vulkan->queue_family_count)
	{
		if (vulkan->queue_props[index].queueFlags & VK_QUEUE_TRANSFER_BIT &&
			index != vulkan->graphics_queue_family_index)
		{
			vulkan->transfer_queue_family_index = index;
			printf("right queueFamily selected!\n");
			break ;
		}
		index++;
	}
	printf("index of transfer queue fimaly : %u\n", index);
}

int		check_device_extension_support(t_vulkan *vulkan)
{
	VkExtensionProperties	*device_extension;
	uint32_t				device_extension_count;
	uint32_t				i;

	vkEnumerateDeviceExtensionProperties(vulkan->gpu[0], NULL, &device_extension_count, NULL);
	device_extension = (VkExtensionProperties*)malloc(device_extension_count * sizeof(VkExtensionProperties));
	vkEnumerateDeviceExtensionProperties(vulkan->gpu[0], NULL, &device_extension_count, device_extension);
	i = 0;
	vulkan->device_extension_count = 0;
	while (i < device_extension_count)
	{
		if (!ft_strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, device_extension[i].extensionName))
		{
			vulkan->device_extension_name[0] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
			vulkan->device_extension_count++;
		}
		i++;
	}
	free(device_extension);
	printf("device extension : %s\n", vulkan->device_extension_name[0]);
	printf("device_extension_count : %u\n", vulkan->device_extension_count);
	if (vulkan->device_extension_count > 0)
		return (1);
	return (0);
}

void	check_devices(t_vulkan *vulkan)
{
	uint32_t	index;
	int			score;

	score = 0;
	index = 0;

	vkGetPhysicalDeviceProperties(vulkan->gpu[index], &vulkan->dv_props);
	vkGetPhysicalDeviceFeatures(vulkan->gpu[index], &vulkan->dv_feats);
	printf("%s\n", vulkan->dv_props.deviceName);

	if (vulkan->dv_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		printf("good it's a GPU!!\n");
	if (!vulkan->dv_feats.tessellationShader)
		printf("doesn't support tessellation shader... bad..\n");
	score += vulkan->dv_props.limits.maxImageDimension2D;
	printf("score: %d\n", score);
	if (!vulkan->dv_feats.geometryShader)
		printf("doesn't support geometry shader... bad..\n");
	printf("fillModeNonSolid : %d\n", vulkan->dv_feats.fillModeNonSolid);
	if (check_device_extension_support(vulkan) == 1)
		printf("swapchain extension is supported in the device\n");
	else
		printf("swapchain extension is not supported!! abort!!\n");
}

int		physical_device_select(t_vulkan *vulkan)
{
	vulkan->gpu_count = 0;
	vkEnumeratePhysicalDevices(vulkan->instance, &vulkan->gpu_count, NULL);
	printf("FOUND %u GPUs\n", vulkan->gpu_count);
	vulkan->gpu = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * vulkan->gpu_count); /*TODO replace vector */
	vkEnumeratePhysicalDevices(vulkan->instance, &vulkan->gpu_count, vulkan->gpu);

	/*TODO recieve properties and features of the vulkan->gpu */
	check_devices(vulkan);
	find_graphics_queue_family(vulkan); /*TODO check if the chosen device supports queue family */
	printf("after queuefamilycheck : %u\n", vulkan->transfer_queue_family_index);
	return (1);
}
