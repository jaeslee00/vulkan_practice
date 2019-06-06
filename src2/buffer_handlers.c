/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 10:19:30 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/06 23:05:06 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	copy_buffer(t_vulkan *vk, VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size)
{
	VkCommandBuffer		command_buffer;

	command_buffer = begin_singletime_commands(vk);

	VkBufferCopy copy_region = {};
	copy_region.size = size;
	vkCmdCopyBuffer(command_buffer, src_buffer, dst_buffer, 1, &copy_region);

	end_singletime_commands(vk, command_buffer);
}

uint32_t	find_memory_type(t_vulkan *vk, uint32_t type_filter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties	mem_properties;
	uint32_t							i;

	vkGetPhysicalDeviceMemoryProperties(vk->gpu[0], &mem_properties);
	i = 0;
	while (i < mem_properties.memoryTypeCount)
	{
		if ((type_filter & (1 << i)) &&
			(mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
			return (i);
		i++;
	}
	printf("couldn't find proper memory type!\n");
	exit(0);
}

void	create_buffer(t_vulkan *vk, VkDeviceSize size,
					VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
								VkBuffer *buffer, VkDeviceMemory *buffer_memory)
{
	VkBufferCreateInfo		create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	create_info.size = size;
	create_info.usage = usage;
	create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	ft_assert((vkCreateBuffer(vk->logical_device, &create_info, NULL,
				buffer) == VK_SUCCESS),
					"failed to create vertex buffer", "create_vertex_buffer.c", 23);

	VkMemoryRequirements	mem_requirements;
	vkGetBufferMemoryRequirements(vk->logical_device, *buffer, &mem_requirements);

	VkMemoryAllocateInfo 	alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = mem_requirements.size;
	alloc_info.memoryTypeIndex = find_memory_type(vk, mem_requirements.memoryTypeBits,
													properties);
	ft_assert((vkAllocateMemory(vk->logical_device, &alloc_info,
					NULL, buffer_memory) == VK_SUCCESS),
			"failed to allocate memory for vertex buffer", "create_vertex_buffer.c", 55);

	vkBindBufferMemory(vk->logical_device, *buffer, *buffer_memory, 0);
}

void	create_vertex_buffer(t_vulkan *vk)
{
	VkDeviceSize	buffer_size;
	VkBuffer		stage_buffer;
	VkDeviceMemory	stage_buffer_memory;

	buffer_size = vk->ico.elem_size * vk->ico.length;
	create_buffer(vk, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					&stage_buffer, &stage_buffer_memory);

	void	*data;
	vkMapMemory(vk->logical_device, stage_buffer_memory, 0, buffer_size, 0, &data);
		memcpy(data, (t_vertex*)vk->ico.ptr, (size_t)buffer_size);
	vkUnmapMemory(vk->logical_device, stage_buffer_memory);

	create_buffer(vk, buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
					&vk->vertex_buffer, &vk->vertex_buffer_memory);

	copy_buffer(vk, stage_buffer, vk->vertex_buffer, buffer_size);

	vkDestroyBuffer(vk->logical_device, stage_buffer, NULL);
	vkFreeMemory(vk->logical_device, stage_buffer_memory, NULL);
}

void	create_index_buffer(t_vulkan *vk)
{
	VkDeviceSize	buffer_size;
	VkBuffer		stage_buffer;
	VkDeviceMemory	stage_buffer_memory;

	//buffer_size = (uint64_t)QUADS * (uint64_t)QUADS * 6 * 6 * sizeof(uint32_t); /*TODO the number cannot be hard-coded!!*/
	buffer_size = 3840 * sizeof(uint32_t);
	printf("buffersize : %llu", buffer_size);
	create_buffer(vk, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					&stage_buffer, &stage_buffer_memory);

	void	*data;
	vkMapMemory(vk->logical_device, stage_buffer_memory, 0, buffer_size, 0, &data);
		memcpy(data, vk->final_vi, (size_t)buffer_size);
	vkUnmapMemory(vk->logical_device, stage_buffer_memory);

	create_buffer(vk, buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
					&vk->index_buffer, &vk->index_buffer_memory);

	copy_buffer(vk, stage_buffer, vk->index_buffer, buffer_size);

	vkDestroyBuffer(vk->logical_device, stage_buffer, NULL);
	vkFreeMemory(vk->logical_device, stage_buffer_memory, NULL);
}
