/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapchain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:48:02 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/14 22:33:49 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	imageview_create(t_vulkan *vulkan)
{
	VkImage					*swapchain_image;
	uint32_t				i;

	vkGetSwapchainImagesKHR(vulkan->logical_device, vulkan->swapchain, &vulkan->swapchain_image_count, NULL);
	swapchain_image = (VkImage*)malloc(vulkan->swapchain_image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(vulkan->logical_device, vulkan->swapchain, &vulkan->swapchain_image_count, swapchain_image);
	vulkan->buffer = (t_swapchain_buffer*)malloc(vulkan->swapchain_image_count * sizeof(t_swapchain_buffer));

	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		VkImageViewCreateInfo	imageview_info = {};
		imageview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageview_info.image = swapchain_image[i];
		vulkan->buffer[i].swapchain_image = swapchain_image[i];
		imageview_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageview_info.format = vulkan->format;
		imageview_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageview_info.subresourceRange.baseMipLevel = 0;
		imageview_info.subresourceRange.levelCount = 1;
		imageview_info.subresourceRange.baseArrayLayer = 0;
		imageview_info.subresourceRange.layerCount = 1;
		if (vkCreateImageView(vulkan->logical_device, &imageview_info, NULL, &vulkan->buffer[i].view) != VK_SUCCESS)
			printf("creating swapchain_imageview failed.\n");
		else
			printf("swapchain_imageview %u successfully created.\n", i);
		i++;
	}
	free(swapchain_image);
}

void	swapchain_create(t_vulkan *vulkan)
{
	uint32_t					image_count;
	VkSwapchainCreateInfoKHR	swapchain_info = {};

	printf("max imagecount : %u\n", vulkan->surf_capabilities.maxImageCount);
	printf("min imagecount : %u\n", vulkan->surf_capabilities.minImageCount);
	image_count = vulkan->surf_capabilities.minImageCount + 1;
	if (image_count > vulkan->surf_capabilities.maxImageCount &&
			vulkan->surf_capabilities.maxImageCount > 0)
		image_count = vulkan->surf_capabilities.maxImageCount;

	swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_info.surface = vulkan->surf;
	swapchain_info.minImageCount = image_count;
	swapchain_info.imageFormat = vulkan->format;
	swapchain_info.imageColorSpace = vulkan->color_space;
	swapchain_info.imageExtent = vulkan->swapchain_extent;
	swapchain_info.imageArrayLayers = 1; /* always 1 unless creating stereoscopic 3D app */
	swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchain_info.queueFamilyIndexCount = 0;
	swapchain_info.pQueueFamilyIndices = NULL;
	swapchain_info.preTransform = vulkan->surf_capabilities.currentTransform; /* it can differ*/
	swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_info.presentMode = vulkan->present_mode;
	swapchain_info.clipped = VK_TRUE;
	swapchain_info.oldSwapchain = VK_NULL_HANDLE;
	if (vkCreateSwapchainKHR(vulkan->logical_device, &swapchain_info, NULL, &vulkan->swapchain) != VK_SUCCESS)
		printf("failed to create swapchain!!\n");
	else
		printf("successfully created swapchain!!\n");

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
	vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan->gpu[0], vulkan->surf, &present_mode_count, vulkan->present_modes);
	vulkan->present_mode = vulkan->present_modes[0];
	vulkan->swapchain_extent.width = WIDTH;
	vulkan->swapchain_extent.height = HEIGHT;
	swapchain_create(vulkan);
	imageview_create(vulkan);
}