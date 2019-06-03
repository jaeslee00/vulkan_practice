/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_depth_resource.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 23:42:28 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 22:54:29 by jaelee           ###   ########.fr       */
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
		vkGetPhysicalDeviceFormatProperties(vk->gpu[0], candidates[index], &props);
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

	candidates[0] = VK_FORMAT_D32_SFLOAT_S8_UINT;
	candidates[1] = VK_FORMAT_D32_SFLOAT;
	candidates[2] = VK_FORMAT_D24_UNORM_S8_UINT;

	chosen_format = find_supported_depth_format(vk, candidates, 3, VK_IMAGE_TILING_OPTIMAL,
						VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	return (chosen_format);
}

void		create_depth_resource(t_vulkan *vk)
{
	VkFormat	depth_format;

	depth_format = choose_depth_format(vk);
	create_image(vk, vk->swapchain_extent.width, vk->swapchain_extent.height,
		depth_format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vk->depth_image, &vk->depth_image_memory);
	vk->depth_image_view =
		create_imageview(vk, vk->depth_image, 1, depth_format, VK_IMAGE_ASPECT_DEPTH_BIT);
	transition_image_layout(vk, vk->depth_image, depth_format,
		VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}
