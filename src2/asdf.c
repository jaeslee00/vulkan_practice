/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asdf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 01:01:35 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 01:01:43 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_descriptor_set(t_vulkan *vulkan)
{
	VkDescriptorSetAllocateInfo alloc_info = {};
	uint32_t i;
	VkDescriptorSetLayout		*layouts;

	vulkan->descriptor_set =
		(VkDescriptorSet*)malloc(vulkan->swapchain_image_count * sizeof(VkDescriptorSet));
	layouts =
		(VkDescriptorSetLayout*)malloc(vulkan->swapchain_image_count * sizeof(VkDescriptorSetLayout));
	layouts[0] = vulkan->descriptor_set_layout;
	layouts[1] = vulkan->descriptor_set_layout;
	layouts[2] = vulkan->descriptor_set_layout;
	alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	alloc_info.descriptorPool = vulkan->descriptor_pool;
	alloc_info.descriptorSetCount = vulkan->swapchain_image_count;
	alloc_info.pSetLayouts = layouts;

	ft_assert ((vkAllocateDescriptorSets(vulkan->logical_device, &alloc_info, vulkan->descriptor_set) == VK_SUCCESS),
					"failed to allcate descriptor sets", "descriptor_pool.c", 26);
	i = 0;
	while (i < vulkan->swapchain_image_count)
	{
		VkDescriptorBufferInfo	buffer_info = {};
		buffer_info.buffer = vulkan->uniform_buffers[i];
		buffer_info.offset = 0;
		buffer_info.range = sizeof(vulkan->ubo);

		VkWriteDescriptorSet	descriptor_write = {};
		descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptor_write.dstSet = vulkan->descriptor_set[i];
		descriptor_write.dstBinding = 0;
		descriptor_write.dstArrayElement = 0;
		descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptor_write.descriptorCount = 1;
		descriptor_write.pBufferInfo = &buffer_info;

		vkUpdateDescriptorSets(vulkan->logical_device, 1, &descriptor_write, 0, NULL);
		i++;
	}
}

void	create_descriptor_pool(t_vulkan *vulkan)
{
	VkDescriptorPoolSize	poolsize = {};
	VkDescriptorPoolCreateInfo create_info = {};

	poolsize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolsize.descriptorCount = vulkan->swapchain_image_count;
	create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	create_info.poolSizeCount = 1;
	create_info.pPoolSizes = &poolsize;
	create_info.maxSets = vulkan->swapchain_image_count;

	ft_assert((vkCreateDescriptorPool(vulkan->logical_device, &create_info, NULL, &vulkan->descriptor_pool) == VK_SUCCESS),
		"failed to create descriptor pool", "descriptor_pool.c", 62);
}
