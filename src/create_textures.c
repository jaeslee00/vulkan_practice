/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:19:44 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/17 19:09:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void	create_texture_imageview(t_vulkan *vk)
{
	vk->texture_image_view =
		create_imageview(vk, vk->texture_image,
			1, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
}

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

	pixels = stbi_load("./textures/moss.jpg", &tex_width, &tex_height,
				&tex_channel, STBI_rgb_alpha);
	size = tex_width * tex_height * 4;
	printf("texture size : %d by %d\n", tex_width, tex_height);
	create_buffer(vk, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
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

	vkDestroyBuffer(vk->logical_device, stage_buffer, NULL);
	vkFreeMemory(vk->logical_device, stage_buffer_memory, NULL);
}

void	create_texture_sampler(t_vulkan *vk)
{
	VkSamplerCreateInfo		sampler_info = {};

	sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;

	sampler_info.magFilter = VK_FILTER_LINEAR;
	sampler_info.minFilter = VK_FILTER_LINEAR;

	sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT; /*attr for texture-space left-over*/
	sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT; /*attr for texture-space left-over*/
	sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT; /*attr for texture-space left-over*/

	if (vk->dv_feats.samplerAnisotropy)
	{
		sampler_info.anisotropyEnable  = VK_TRUE;
		sampler_info.maxAnisotropy = 16;
	}
	else
	{
		sampler_info.anisotropyEnable  = VK_FALSE;
		sampler_info.maxAnisotropy = 1;
	}

	sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK; /* attr for image_clamp option in addressmode*/
	sampler_info.unnormalizedCoordinates = VK_FALSE;

	sampler_info.compareEnable = VK_FALSE; /* percentage-closer filtering on shadow maps */
	sampler_info.compareOp = VK_COMPARE_OP_ALWAYS; /* percentage-closer filtering on shadow maps */

	sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	sampler_info.mipLodBias = 0.0f;
	sampler_info.minLod = 0.0f;
	sampler_info.maxLod = 0.0f;

	ft_assert((vkCreateSampler(vk->logical_device, &sampler_info,
		NULL, &vk->texture_sampler) == VK_SUCCESS),
		"failed to create image sampler", "create_texture.c", 123);
}
