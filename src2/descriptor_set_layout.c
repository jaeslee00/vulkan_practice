/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descriptor_set_layout.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:17:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/22 10:20:53 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_descriptor_set_layout(t_vulkan *vk)
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
	ft_assert((vkCreateDescriptorSetLayout(vk->logical_device, &create_info, NULL,
			&vk->descriptor_set_layout) == VK_SUCCESS),
		"failed to create descriptor set layout", "descriptor_set_layout.c", 24);
}

void create_descriptor_sets(t_vulkan *vk)
{
	VkDescriptorSetLayout *layouts;
	uint32_t	i;

	layouts =
		(VkDescriptorSetLayout*)malloc(vk->swapchain_image_count * sizeof(VkDescriptorSetLayout));
	layouts[0] = vk->descriptor_set_layout;
	layouts[1] = vk->descriptor_set_layout;

	vk->descriptor_sets =
		(VkDescriptorSet*)malloc(vk->swapchain_image_count * sizeof (VkDescriptorSet));

	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = vk->descriptor_pool;
	allocInfo.descriptorSetCount = vk->swapchain_image_count;
	allocInfo.pSetLayouts = layouts;

	if (vkAllocateDescriptorSets(vk->logical_device, &allocInfo, vk->descriptor_sets) != VK_SUCCESS)
		printf("failed to allocate descriptor sets!\n");

	i = 0;
	while (i < vk->swapchain_image_count)
	{
		VkDescriptorBufferInfo buffer_info = {};
		buffer_info.buffer = vk->uniform_buffers[i];
		buffer_info.offset = 0;
		buffer_info.range = sizeof(t_ubo);

		VkWriteDescriptorSet descriptor_write = {};
		descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptor_write.dstSet = vk->descriptor_sets[i];
		descriptor_write.dstBinding = 0;
		descriptor_write.dstArrayElement = 0;
		descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptor_write.descriptorCount = 1;
		descriptor_write.pBufferInfo = &buffer_info;

		vkUpdateDescriptorSets(vk->logical_device, 1, &descriptor_write, 0, NULL);
		i++;
	}
}

void	create_descriptor_pool(t_vulkan *vk)
{
	VkDescriptorPoolSize		pool_size = {};
	pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	pool_size.descriptorCount = vk->swapchain_image_count;

	VkDescriptorPoolCreateInfo	pool_info = {};
	pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	pool_info.poolSizeCount = 1;
	pool_info.pPoolSizes = &pool_size;
	pool_info.maxSets = vk->swapchain_image_count;

	if (vkCreateDescriptorPool(vk->logical_device, &pool_info, NULL, &vk->descriptor_pool) != VK_SUCCESS)
		printf("failed to create descriptor pool!\n");
}

