/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_pipline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:39:19 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/14 05:46:53 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

size_t			load_file(char **code const char *path)
{
	FILE	*file;
	long	file_size;
	char	*spv_code;

	file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	spv_code = (char *)malloc(file_size + 1);
	fread(spv_code, file_size, 1, file);
	fclose(file);
	spv_code[file_size] = '\0';
	*code = spv_code;
	return ((size_t)file_size);

}

VkShaderModule	get_shader_module(t_vulkan *vulkan, const char *path)
{
	char	*spv_code;
	size_t	size = load_file(&spv_code, path);
	VkShaderModuleCreateInfo	shader_module_info = {};
	VkShaderModule				module;

	shader_module_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shader_module_info.codeSize = size;
	shader_module_info.pCode = (uint32_t*)spv_code;
	if (vkCreateShaderModule(vulkan->logical_device, &shader_module_info, NULL, &module))
		printf("shader module %s successfully created.\n", path);
	free(spv_code);
	return (module);
}

void	create_pipeline(t_vulkan *vulkan)
{
	VkShaderModule					vertex_shader;
	VkShaderModule					fragment_shader;
	VkPipelineShaderStageCreateInfo	shader_stage[2];

	vertex_shader = get_shader_module(vulkan, "./shaders/vert.spv");
	fragment_shader = get_shader_module(vulkan, "./shaders/frag.spv");

	ft_bzero(shader_stage, 0, sizeof(VkPipelineShaderStageCreateInfo));
	shader_stage[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shader_stage[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shader_stage[0].module = vertex_shader;
    shader_stage[0].pName = "main";

    shader_stage[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shader_stage[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shader_stage[1].module = fragment_shader;
    shader_stage[1].pName = "main";

}
