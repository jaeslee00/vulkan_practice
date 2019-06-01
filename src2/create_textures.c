/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:19:44 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/01 22:35:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void	copy_buffer_to_image(t_vulkan *vk, VkBuffer buffer, VkImage image,
			uint32_t width, uint32_t height)
{
	VkCommandBuffer	command_buffer;

	command_buffer = begin_singletime_commands(vk);

	VkBufferImageCopy	region = {};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = (VkOffset3D){0, 0, 0};
	region.imageExtent = (VkExtent3D){width, height, 1};

	vkCmdCopyBufferToImage(command_buffer, buffer, image,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	end_singletime_commands(vk, command_buffer);
}

void	create_texture_image(t_vulkan *vk)
{
	int				tex_width;
	int				tex_height;
	int				tex_channel;
	stbi_uc 		*pixels;
	VkDeviceSize	size;
	VkBuffer		stage_buffer;
	VkDeviceMemory	stage_buffer_memory;

	pixels = stbi_load("./textures/stone.jpg",
				&tex_width, &tex_height, &tex_channel, STBI_rgb_alpha);
	size = tex_width * tex_height * 4;

	create_buffer(vk, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
					&stage_buffer, &stage_buffer_memory);

	void	*data;
	vkMapMemory(vk->logical_device, stage_buffer_memory, 0, size, 0, &data);
		memcpy(data, pixels, (size_t)size);
	vkUnmapMemory(vk->logical_device, stage_buffer_memory);

	stbi_image_free(pixels);
	create_image(vk, tex_width, tex_height, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&vk->texture_image, &vk->texture_image_memory);

	transition_image_layout(vk, vk->texture_image, VK_FORMAT_R8G8B8A8_UNORM,
		VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	copy_buffer_to_image(vk, stage_buffer, vk->texture_image, (uint32_t)tex_width, (uint32_t)tex_height);
	transition_image_layout(vk, vk->texture_image,VK_FORMAT_R8G8B8A8_UNORM,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}
