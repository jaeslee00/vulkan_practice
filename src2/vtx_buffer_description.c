/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtx_buffer_description.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 09:50:23 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 21:51:35 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

VkVertexInputBindingDescription		get_binding_description(void)
{
	VkVertexInputBindingDescription binding_descriptions = {};

	binding_descriptions.binding = 0;
	binding_descriptions.stride = sizeof(t_vertex);
	binding_descriptions.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return (binding_descriptions);
}

VkVertexInputAttributeDescription	get_position_attirbutes(void)
{
	VkVertexInputAttributeDescription	attr_descriptions;

	attr_descriptions.binding = 0;
	attr_descriptions.location = 0;
	attr_descriptions.format = VK_FORMAT_R32G32B32_SFLOAT; /* t_vertex->pos input of vec3 info */
	attr_descriptions.offset = offsetof(t_vertex, pos);

	return (attr_descriptions);
}
VkVertexInputAttributeDescription	get_color_attributes(void)
{
	VkVertexInputAttributeDescription	attr_descriptions;

	attr_descriptions.binding = 0;
	attr_descriptions.location = 1;
	attr_descriptions.format = VK_FORMAT_R32G32B32_SFLOAT; /* t_vertex->color input of vec3 info */
	attr_descriptions.offset = offsetof(t_vertex, color);

	return (attr_descriptions);
}
VkVertexInputAttributeDescription	get_tex_coord_attirbutes(void)
{
	VkVertexInputAttributeDescription	attr_descriptions;

	attr_descriptions.binding = 0;
	attr_descriptions.location = 2;
	attr_descriptions.format = VK_FORMAT_R32G32_SFLOAT; /* t_vertex->tex_coord input of vec2 info */
	attr_descriptions.offset = offsetof(t_vertex, tex_coord);

	return (attr_descriptions);
}
