/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_devices.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:47:58 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 16:18:25 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

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
	printf("device extension %u : %s\n", vk->device_extension_count,
		vk->device_extension_name[0]);
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
	if (check_device_extension_support(vk) == 1)
		printf("swapchain extension is supported in the device\n");
	else
	{
		printf("swapchain extension is not supported!! abort!!\n");
		exit(0);
	}
}

int		physical_device_select(t_vulkan *vk)
{
	vk->gpu_count = 0;
	vkEnumeratePhysicalDevices(vk->instance, &vk->gpu_count, NULL);
	printf("FOUND %u GPUs\n", vk->gpu_count);
	vk->gpu = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * vk->gpu_count); /*TODO replace vector */
	vkEnumeratePhysicalDevices(vk->instance, &vk->gpu_count, vk->gpu);
	check_devices(vk);
	return (1);
}
