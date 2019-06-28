/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:05:38 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/17 19:09:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_image(t_vulkan *vk, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
	VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage *image, VkDeviceMemory *image_memory)
{
	VkImageCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	create_info.imageType = VK_IMAGE_TYPE_2D;
	create_info.format = format;
	create_info.extent.width = width;
	create_info.extent.height = height;
	create_info.extent.depth = 1;
	create_info.mipLevels = 1;
	create_info.arrayLayers = 1;
	create_info.tiling = tiling;
	create_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	create_info.usage = usage;
	create_info.samples = VK_SAMPLE_COUNT_1_BIT;
	create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	ft_assert((vkCreateImage(vk->logical_device, &create_info, NULL, image) == VK_SUCCESS),
		"failed to create image!\n", "create_depth_resource.c", 68);

	VkMemoryRequirements	mem_requirements;
	vkGetImageMemoryRequirements(vk->logical_device, *image, &mem_requirements);

	VkMemoryAllocateInfo	alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = mem_requirements.size;
	alloc_info.memoryTypeIndex = find_memory_type(vk, mem_requirements.memoryTypeBits, properties);

	ft_assert(vkAllocateMemory(vk->logical_device, &alloc_info, NULL, image_memory) == VK_SUCCESS,
		"failed to allocate image memory!\n", "create_depth_resource.c", 79);

	vkBindImageMemory(vk->logical_device, *image, *image_memory, 0);
}

VkImageView	create_imageview(t_vulkan *vk, VkImage image, uint32_t levels,
				VkFormat format, VkImageAspectFlagBits flags)
{
	VkImageViewCreateInfo	imageview_info = {};
	VkImageView				image_view;

	imageview_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageview_info.image = image;
	imageview_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageview_info.format = format;
	imageview_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageview_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageview_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageview_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageview_info.subresourceRange.aspectMask = flags;
	imageview_info.subresourceRange.layerCount = 1;
	imageview_info.subresourceRange.baseArrayLayer = 0;
	imageview_info.subresourceRange.levelCount = levels;
	imageview_info.subresourceRange.baseMipLevel = 0;

	ft_assert((vkCreateImageView(vk->logical_device, &imageview_info, NULL,
		&image_view) == VK_SUCCESS), "create imageview failed.\n",
		"create_texture.c", 30);
	return (image_view);
}
