/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapchain_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:48:02 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/22 10:25:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_imageviews(t_vulkan *vk)
{
	uint32_t	i;

	vkGetSwapchainImagesKHR(vk->logical_device, vk->swapchain, &vk->swapchain_image_count, NULL);
	printf("imagecount :: %u\n", vk->swapchain_image_count);
	vk->swapchain_images = (VkImage*)malloc(vk->swapchain_image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(vk->logical_device, vk->swapchain, &vk->swapchain_image_count, vk->swapchain_images);
	vk->image_views = (VkImageView*)malloc(vk->swapchain_image_count * sizeof(VkImageView));

	i = 0;
	while (i < vk->swapchain_image_count)
	{
		VkImageViewCreateInfo	imageview_info = {};
		imageview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageview_info.image = vk->swapchain_images[i];
		imageview_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageview_info.format = vk->format;
		imageview_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageview_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageview_info.subresourceRange.baseMipLevel = 0;
		imageview_info.subresourceRange.levelCount = 1;
		imageview_info.subresourceRange.baseArrayLayer = 0;
		imageview_info.subresourceRange.layerCount = 1;
		ft_assert((vkCreateImageView(vk->logical_device, &imageview_info, NULL, &vk->image_views[i]) == VK_SUCCESS),
			"creating swapchain_imageview failed.\n", "example.c", 48);
		i++;
	}
}

void	swapchain_create(t_vulkan *vk)
{
	uint32_t					image_count;
	VkSwapchainCreateInfoKHR	swapchain_info = {};

	swapchain_query(vk);
	swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchain_info.surface = vk->surf;
	swapchain_info.minImageCount = 2;
	swapchain_info.imageFormat = vk->format;
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
	ft_assert((vkCreateSwapchainKHR(vk->logical_device, &swapchain_info, NULL, &vk->swapchain) == VK_SUCCESS),
		"failed to create swapchain!!", "swapchain.c", 39);
}
