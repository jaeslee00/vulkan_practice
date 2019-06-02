/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shader_module.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 11:23:16 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/29 17:51:30 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static size_t	load_file(char **code, const char *path)
{
	FILE	*file;
	long	file_size;
	char	*spv_code;

	file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	spv_code = (char *)malloc(file_size + 1);
	fread(spv_code, file_size, 1, file);
	fclose(file);
	spv_code[file_size] = 0;
	*code = spv_code;
	return ((size_t)file_size);
}

VkShaderModule	get_shader_module(t_vulkan *vk, const char *path)
{
	char						*spv_code;
	size_t						size;
	VkShaderModuleCreateInfo	shader_module_info = {};
	VkShaderModule				module;

	size = load_file(&spv_code, path);
	shader_module_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shader_module_info.codeSize = size;
	ft_assert(size % 4 == 0,
	"something wrong with the spir-v code!", "get_shader_module.c", 45);
	shader_module_info.pCode = (uint32_t*)spv_code;
	ft_assert((vkCreateShaderModule(vk->logical_device, &shader_module_info, NULL, &module) == VK_SUCCESS),
				"failed to create shadermodule", "get_shader_module.c", 47);
	free(spv_code);
	return (module);
}
