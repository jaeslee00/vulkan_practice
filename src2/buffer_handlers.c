/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 10:19:30 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/17 18:18:42 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	copy_buffer(t_vulkan *vulkan, VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size)
{
	VkCommandBufferAllocateInfo	alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	alloc_info.commandPool = vulkan->command_pool_transfer;
	alloc_info.commandBufferCount = 1;

	VkCommandBuffer				command_buffer;
	vkAllocateCommandBuffers(vulkan->logical_device, &alloc_info, &command_buffer);

	VkCommandBufferBeginInfo	begin_info = {};
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(command_buffer, &begin_info);

		VkBufferCopy copy_region = {};
		copy_region.size = size;
		vkCmdCopyBuffer(command_buffer, src_buffer, dst_buffer, 1, &copy_region);

	vkEndCommandBuffer(command_buffer);

	VkSubmitInfo	submit_info = {};
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &command_buffer;

	vkQueueSubmit(vulkan->transfer_queue, 1, &submit_info, VK_NULL_HANDLE);
	vkQueueWaitIdle(vulkan->transfer_queue);

	vkFreeCommandBuffers(vulkan->logical_device, vulkan->command_pool_transfer, 1, &command_buffer);
}

static uint32_t	find_memory_type(t_vulkan *vulkan, uint32_t type_filter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties	mem_properties;
	uint32_t							i;

	vkGetPhysicalDeviceMemoryProperties(vulkan->gpu[0], &mem_properties);
	i = 0;
	while (i < mem_properties.memoryTypeCount)
	{
		if ((type_filter & (1 - i)) &&
			(mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
			return (i);
		i++;
	}
	printf("couldn't find proper memory type!\n");
	exit(0);
}

void	create_buffer(t_vulkan *vulkan, VkDeviceSize size,
					VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
								VkBuffer *buffer, VkDeviceMemory *buffer_memory)
{
	VkBufferCreateInfo		create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	create_info.size = size;
	create_info.usage = usage;
	create_info.queueFamilyIndexCount = 2;
	create_info.pQueueFamilyIndices = vulkan->queue_family_indices;
	create_info.sharingMode = VK_SHARING_MODE_CONCURRENT; // diff queues;.. please change it back if not work out!!

	ft_assert((vkCreateBuffer(vulkan->logical_device, &create_info, NULL,
				buffer) == VK_SUCCESS),
					"failed to create vertex buffer", "create_vertex_buffer.c", 23);

	VkMemoryRequirements	mem_requirements;
	vkGetBufferMemoryRequirements(vulkan->logical_device, *buffer, &mem_requirements);

	VkMemoryAllocateInfo 	alloc_info = {};
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.allocationSize = mem_requirements.size;
	alloc_info.memoryTypeIndex = find_memory_type(vulkan, mem_requirements.memoryTypeBits,
													properties);
	ft_assert((vkAllocateMemory(vulkan->logical_device, &alloc_info,
					NULL, buffer_memory) == VK_SUCCESS),
			"failed to allocate memory for vertex buffer", "create_vertex_buffer.c", 55);

	vkBindBufferMemory(vulkan->logical_device, *buffer, *buffer_memory, 0);
}

void	create_vertex_buffer(t_vulkan *vulkan)
{
	VkDeviceSize	buffer_size;
	VkBuffer		stage_buffer;
	VkDeviceMemory	stage_buffer_memory;

	printf("vertex ::: %zu\n", vulkan->triangle.length);
	buffer_size = vulkan->triangle.elem_size * vulkan->triangle.length;

	create_buffer(vulkan, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					&stage_buffer, &stage_buffer_memory);

	void	*data;
	vkMapMemory(vulkan->logical_device, stage_buffer_memory, 0, buffer_size, 0, &data);
		memcpy(data, (t_vertex*)vulkan->triangle.ptr, (size_t)buffer_size);
	vkUnmapMemory(vulkan->logical_device, stage_buffer_memory);

	create_buffer(vulkan, buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
					&vulkan->vertex_buffer, &vulkan->vertex_buffer_memory);

	copy_buffer(vulkan, stage_buffer, vulkan->vertex_buffer, buffer_size);

	vkDestroyBuffer(vulkan->logical_device, stage_buffer, NULL);
	vkFreeMemory(vulkan->logical_device, stage_buffer_memory, NULL);
}

void	create_index_buffer(t_vulkan *vulkan)
{
	VkDeviceSize	buffer_size;
	VkBuffer		stage_buffer;
	VkDeviceMemory	stage_buffer_memory;

	buffer_size = 12 * sizeof(uint32_t); /*TODO the number cannot be hard-coded!!*/

	create_buffer(vulkan, buffer_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					&stage_buffer, &stage_buffer_memory);

	void	*data;
	vkMapMemory(vulkan->logical_device, stage_buffer_memory, 0, buffer_size, 0, &data);
		memcpy(data, vulkan->vertices_index, (size_t)buffer_size);
	vkUnmapMemory(vulkan->logical_device, stage_buffer_memory);

	create_buffer(vulkan, buffer_size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
					&vulkan->index_buffer, &vulkan->index_buffer_memory);

	copy_buffer(vulkan, stage_buffer, vulkan->index_buffer, buffer_size);

	vkDestroyBuffer(vulkan->logical_device, stage_buffer, NULL);
	vkFreeMemory(vulkan->logical_device, stage_buffer_memory, NULL);
}
