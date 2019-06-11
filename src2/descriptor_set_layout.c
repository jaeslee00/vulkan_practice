/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descriptor_set_layout.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:17:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/11 14:57:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	create_descriptor_set_layout(t_vulkan *vk)
{
	VkDescriptorSetLayoutBinding	ubo_binding = {};
	ubo_binding.binding = 0;
	ubo_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	ubo_binding.descriptorCount = 1;
	ubo_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	ubo_binding.pImmutableSamplers = NULL;

	VkDescriptorSetLayoutBinding	sampler_binding = {};
	sampler_binding.binding = 1;
	sampler_binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	sampler_binding.descriptorCount = 1;
	sampler_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
	sampler_binding.pImmutableSamplers = NULL;

	VkDescriptorSetLayoutCreateInfo	create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	create_info.bindingCount = 2;
	create_info.pBindings = (VkDescriptorSetLayoutBinding[]){ubo_binding, sampler_binding};
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
	free(layouts);
	i = 0;
	while (i < vk->swapchain_image_count)
	{
		VkDescriptorBufferInfo buffer_info = {};
		buffer_info.buffer = vk->uniform_buffers[i];
		buffer_info.offset = 0;
		buffer_info.range = sizeof(t_ubo);

		VkDescriptorImageInfo image_info = {};
		image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		image_info.imageView = vk->texture_image_view;
		image_info.sampler = vk->texture_sampler;

		VkWriteDescriptorSet	buffer_descriptor_write = {};

		buffer_descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		buffer_descriptor_write.pNext = NULL;
		buffer_descriptor_write.dstSet = vk->descriptor_sets[i];
		buffer_descriptor_write.dstBinding = 0;
		buffer_descriptor_write.dstArrayElement = 0;
		buffer_descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		buffer_descriptor_write.descriptorCount = 1;
		buffer_descriptor_write.pBufferInfo = &buffer_info;

		VkWriteDescriptorSet	sampler_descriptor_write = {};

		sampler_descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		sampler_descriptor_write.pNext = NULL;
		sampler_descriptor_write.dstSet = vk->descriptor_sets[i];
		sampler_descriptor_write.dstBinding = 1;
		sampler_descriptor_write.dstArrayElement = 0;
		sampler_descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		sampler_descriptor_write.descriptorCount = 1;
		sampler_descriptor_write.pImageInfo = &image_info;

		vkUpdateDescriptorSets(vk->logical_device, 2, (VkWriteDescriptorSet[])
			{buffer_descriptor_write, sampler_descriptor_write}, 0, NULL);
		i++;
	}
}

void	create_descriptor_pool(t_vulkan *vk)
{
	VkDescriptorPoolSize		ubo_size = {};
	ubo_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	ubo_size.descriptorCount = vk->swapchain_image_count;

	VkDescriptorPoolSize		sampler_size = {};
	sampler_size.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	sampler_size.descriptorCount = vk->swapchain_image_count;

	VkDescriptorPoolCreateInfo	pool_info = {};
	pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	pool_info.poolSizeCount = 2;
	pool_info.pPoolSizes = (VkDescriptorPoolSize[]){ubo_size, sampler_size};
	pool_info.maxSets = vk->swapchain_image_count;

	if (vkCreateDescriptorPool(vk->logical_device, &pool_info, NULL, &vk->descriptor_pool) != VK_SUCCESS)
		printf("failed to create descriptor pool!\n");
}

