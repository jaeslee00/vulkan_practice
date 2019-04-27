/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapchain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:48:02 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 13:07:20 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	swapchain_create(t_vulkan *vulkan)
{
	uint32_t					image_count;
	VkSwapchainCreateInfoKHR	swapchain_info = {};

	printf("max imagecount : %u\n", vulkan->surf_capabilities.maxImageCount);
	printf("min imagecount : %u\n", vulkan->surf_capabilities.minImageCount);
	printf("suppored composite alpha in surface : %d\n", vulkan->surf_capabilities.supportedCompositeAlpha);
	swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_info.surface = vulkan->surf;
	swapchain_info.minImageCount = 2;
	swapchain_info.imageFormat = vulkan->format;
	swapchain_info.imageColorSpace = vulkan->color_space;
	swapchain_info.imageArrayLayers = 1; /* always 1 unless creating stereoscopic 3D app */
	swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchain_info.imageExtent = vulkan->swapchain_extent;
	swapchain_info.queueFamilyIndexCount = 0;
	swapchain_info.pQueueFamilyIndices = NULL;
	swapchain_info.preTransform = vulkan->surf_capabilities.currentTransform; /* it can differ*/
	swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_info.presentMode = vulkan->present_mode;
	swapchain_info.clipped = VK_TRUE;
	swapchain_info.oldSwapchain = VK_NULL_HANDLE;
	ft_assert((vkCreateSwapchainKHR(vulkan->logical_device, &swapchain_info, NULL, &vulkan->swapchain) == VK_SUCCESS),
		"failed to create swapchain!!", "swapchain.c", 39);
}

void	check_available_format_colorspace(t_vulkan *vulkan)
{
	for (int i=0; i < 3; i++)
	{
		printf("available format : %u\n", vulkan->surf_formats[0].format);
		printf("available colorSpace : %u\n", vulkan->surf_formats[0].colorSpace);
	}
	vulkan->format = vulkan->surf_formats[0].format;
	vulkan->color_space = vulkan->surf_formats[0].colorSpace;
}

void	swapchain_query(t_visualizer *vis, t_vulkan *vulkan)
{
	VkSurfaceCapabilitiesKHR	surf_capabilities;
	uint32_t					format_count;
	uint32_t					present_mode_count;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkan->gpu[0], vulkan->surf, &vulkan->surf_capabilities);
	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan->gpu[0], vulkan->surf, &format_count, NULL);
	if (format_count == 0)
	{
		printf("surface formats missing\n");
		exit(0);
	}
	printf("format_count : %u\n", format_count);

	vulkan->surf_formats = (VkSurfaceFormatKHR*)malloc(format_count * sizeof(VkSurfaceFormatKHR));
	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan->gpu[0], vulkan->surf, &format_count, vulkan->surf_formats);
	check_available_format_colorspace(vulkan);

	vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan->gpu[0], vulkan->surf, &present_mode_count, NULL);
	printf("present_mode_count : %u\n", present_mode_count);
	if (present_mode_count == 0)
	{
		printf("present_mode missing\n");
		exit(0);
	}
	vulkan->present_modes = (VkPresentModeKHR*)malloc(present_mode_count * sizeof(VkPresentModeKHR));
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan->gpu[0], vulkan->surf, &present_mode_count, vulkan->present_modes) != VK_SUCCESS)
		printf("get physicaldevice surface presenmode failed\n");
	vulkan->present_mode = vulkan->present_modes[0];
	vulkan->swapchain_extent.width = WIDTH; /*TODO weird... capabilities bug? */
	vulkan->swapchain_extent.height = HEIGHT;
	swapchain_create(vulkan);
}
