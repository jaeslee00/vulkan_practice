/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_devices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:47:58 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/22 10:25:39 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	find_graphics_queue_family(t_vulkan *vk)
{
	uint32_t	index;

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
	index = 0;
	while (index < vk->queue_family_count)
	{
		if (vk->queue_props[index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			vk->graphics_queue_family_index = index;
			printf("right queueFamily selected!\n");
			break ;
		}
		index++;
	}
	printf("index of graphics queue fimaly : %u\n", index);
	index = 0;
	while (index < vk->queue_family_count)
	{
		if (vk->queue_props[index].queueFlags & VK_QUEUE_TRANSFER_BIT &&
			index != vk->graphics_queue_family_index)
		{
			vk->transfer_queue_family_index = index;
			printf("right queueFamily selected!\n");
			break ;
		}
		index++;
	}
	printf("index of transfer queue fimaly : %u\n", index);
}

int		check_device_extension_support(t_vulkan *vk)
{
	VkExtensionProperties	*device_extension;
	uint32_t				device_extension_count;
	uint32_t				i;

	vkEnumerateDeviceExtensionProperties(vk->gpu[0], NULL, &device_extension_count, NULL);
	device_extension = (VkExtensionProperties*)malloc(device_extension_count * sizeof(VkExtensionProperties));
	vkEnumerateDeviceExtensionProperties(vk->gpu[0], NULL, &device_extension_count, device_extension);
	i = 0;
	vk->device_extension_count = 0;
	while (i < device_extension_count)
	{
		if (!ft_strcmp(VK_KHR_SWAPCHAIN_EXTENSION_NAME, device_extension[i].extensionName))
		{
			vk->device_extension_name[0] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
			vk->device_extension_count++;
		}
		i++;
	}
	free(device_extension);
	printf("device extension : %s\n", vk->device_extension_name[0]);
	printf("device_extension_count : %u\n", vk->device_extension_count);
	if (vk->device_extension_count > 0)
		return (1);
	return (0);
}

void	check_devices(t_vulkan *vk)
{
	uint32_t	index;
	int			score;

	score = 0;
	index = 0;

	vkGetPhysicalDeviceProperties(vk->gpu[index], &vk->dv_props);
	vkGetPhysicalDeviceFeatures(vk->gpu[index], &vk->dv_feats);
	printf("%s\n", vk->dv_props.deviceName);

	if (vk->dv_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		printf("good it's a GPU!!\n");
	if (!vk->dv_feats.tessellationShader)
		printf("doesn't support tessellation shader... bad..\n");
	score += vk->dv_props.limits.maxImageDimension2D;
	printf("score: %d\n", score);
	if (!vk->dv_feats.geometryShader)
		printf("doesn't support geometry shader... bad..\n");
	printf("fillModeNonSolid : %d\n", vk->dv_feats.fillModeNonSolid);
	if (check_device_extension_support(vk) == 1)
		printf("swapchain extension is supported in the device\n");
	else
		printf("swapchain extension is not supported!! abort!!\n");
}

int		physical_device_select(t_vulkan *vk)
{
	vk->gpu_count = 0;
	vkEnumeratePhysicalDevices(vk->instance, &vk->gpu_count, NULL);
	printf("FOUND %u GPUs\n", vk->gpu_count);
	vk->gpu = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * vk->gpu_count); /*TODO replace vector */
	vkEnumeratePhysicalDevices(vk->instance, &vk->gpu_count, vk->gpu);

	/*TODO recieve properties and features of the vk->gpu */
	check_devices(vk);
	find_graphics_queue_family(vk); /*TODO check if the chosen device supports queue family */
	printf("after queuefamilycheck : %u\n", vk->transfer_queue_family_index);
	return (1);
}
