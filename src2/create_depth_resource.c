/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_depth_resource.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 23:42:28 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/29 13:05:27 by jaelee           ###   ########.fr       */
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
