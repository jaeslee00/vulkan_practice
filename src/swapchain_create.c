/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapchain_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:48:02 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/17 19:09:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_swapchain(t_vulkan *vk)
{
	uint32_t					swapchain_imageview_index;
	VkSwapchainCreateInfoKHR	swapchain_info = {};

	swapchain_query(vk);
	swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_info.surface = vk->surf;
	swapchain_info.minImageCount = 2;
	swapchain_info.imageFormat = vk->swapchain_image_format;
	swapchain_info.imageColorSpace = vk->color_space;
	swapchain_info.imageArrayLayers = 1; /* always 1 unless creating stereoscopic 3D app */
	swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchain_info.imageExtent = vk->swapchain_extent;
	swapchain_info.queueFamilyIndexCount = 0;
	swapchain_info.pQueueFamilyIndices = NULL;
	swapchain_info.preTransform = vk->surf_capabilities.currentTransform; /* it can differ*/
	swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchain_info.presentMode = vk->present_mode;
	swapchain_info.clipped = VK_TRUE;
	swapchain_info.oldSwapchain = VK_NULL_HANDLE;

	if (vk->graphics_queue_family_index != vk->present_queue_family_index)
	{
		swapchain_info.queueFamilyIndexCount = 2;
		swapchain_info.pQueueFamilyIndices =
			(uint32_t[]){vk->graphics_queue_family_index, vk->present_queue_family_index};
		swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	}
	ft_assert((vkCreateSwapchainKHR(vk->logical_device, &swapchain_info, NULL, &vk->swapchain) == VK_SUCCESS),
		"failed to create swapchain!!", "swapchain.c", 39);

	vkGetSwapchainImagesKHR(vk->logical_device, vk->swapchain, &vk->swapchain_image_count, NULL);
	printf("swapchain image count : %u\n", vk->swapchain_image_count);
	vk->swapchain_images = (VkImage*)malloc(vk->swapchain_image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(vk->logical_device, vk->swapchain, &vk->swapchain_image_count, vk->swapchain_images);

	vk->swapchain_imageviews = (VkImageView*)malloc(vk->swapchain_image_count * sizeof(VkImageView));
	swapchain_imageview_index = 0;
	while (swapchain_imageview_index < vk->swapchain_image_count)
	{
		vk->swapchain_imageviews[swapchain_imageview_index] =
			create_imageview(vk, vk->swapchain_images[swapchain_imageview_index],
			1, vk->swapchain_image_format, VK_IMAGE_ASPECT_COLOR_BIT);
		swapchain_imageview_index++;
	}
}
