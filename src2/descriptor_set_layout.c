/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descriptor_set_layout.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:17:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/11 22:22:27 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_descriptor_set_layout(t_vulkan *vulkan)
{
	VkDescriptorSetLayoutBinding	ubo_layout = {};
	ubo_layout.binding = 0;
	ubo_layout.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	ubo_layout.descriptorCount = 1;
	ubo_layout.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	ubo_layout.pImmutableSamplers = NULL;

	VkDescriptorSetLayoutCreateInfo	create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	create_info.bindingCount = 1;
	create_info.pBindings = &ubo_layout;
	ft_assert((vkCreateDescriptorSetLayout(vulkan->logical_device, &create_info, NULL,
			&vulkan->descriptor_set_layout) == VK_SUCCESS),
		"failed to create descriptor set layout", "descriptor_set_layout.c", 24);
}
