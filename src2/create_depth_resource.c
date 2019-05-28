/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_depth_resource.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 23:42:28 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/28 22:05:20 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static VkFormat	find_supported_depth_format(t_vulkan *vk, VkFormat *candidates, uint32_t nbr_candidates,
				VkImageTiling tiling, VkFormatFeatureFlags features)
{
	uint32_t	index;

	index = 0;
	while (index < nbr_candidates)
	{
		VkFormatProperties	props;
		vkGetPhysicalDeviceFormatProperties(vk->logical_device, candidates[index], &props);
		if ((tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features))
			|| (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features)))
			return (candidates[index]);
		index++;
	}
	return (-1);
}

VkFormat	choose_depth_format(t_vulkan *vk)
{
	VkFormat	candidates[3];
	VkFormat	chosen_format;

	candidates[0] = VK_FORMAT_D32_SFLOAT;
	candidates[1] = VK_FORMAT_D32_SFLOAT_S8_UINT;
	candidates[2] = VK_FORMAT_D24_UNORM_S8_UINT;

	chosen_format = find_supported_depth_format(vk, candidates, 3, VK_IMAGE_TILING_OPTIMAL,
						VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

void		create_depth_resource(t_vulkan *vk)
{

}

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
	create_info.samples = VK_SAMPLE_COUNT_32_BIT;
	create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	ft_assert(vkCreateImage(vk->logical_device, &create_info, NULL, image),
	"failed to create image!\n", "create_depth_resource.c", 68);

	VkMemoryRequirements	mem_requirements;
	vkGetImageMemoryRequirements(vk->logical_device, image, &mem_requirements);

	VkMemoryAllocateInfo	alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = mem_requirements.size;
	alloc_info.memoryTypeIndex = find_memory_type(vk, mem_requirements.memoryTypeBits, properties);

	ft_assert(vkAllocateMemory(vk->logical_device, &alloc_info, NULL, image_memory),
	"failed to allocate image memory!\n", "create_depth_resource.c", 79);

	vkBindImageMemory(vk->logical_device, image, image_memory, 0);
}

void	create_image_view
