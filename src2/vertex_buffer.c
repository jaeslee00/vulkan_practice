/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 09:50:23 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 02:50:14 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

VkVertexInputBindingDescription get_binding_description(void)
{
	VkVertexInputBindingDescription binding_descriptions = {};

	binding_descriptions.binding = 0;
	binding_descriptions.stride = sizeof(t_vertex);
	binding_descriptions.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return (binding_descriptions);
}

VkVertexInputAttributeDescription *get_attr_description(void)
{
	VkVertexInputAttributeDescription	*attr_descriptions;

	attr_descriptions =
		(VkVertexInputAttributeDescription*)malloc(2 * sizeof(VkVertexInputAttributeDescription)); /*TODO erase hard-coded numbers */

	attr_descriptions[0].binding = 0;
	attr_descriptions[0].location = 0;
	attr_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; /* vertex_buffer input of vec2 info */
	attr_descriptions[0].offset = offsetof(t_vertex, pos);

	attr_descriptions[1].binding = 0;
	attr_descriptions[1].location = 1;
	attr_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT; /* vertex_buffer input of vec3 info */
	attr_descriptions[1].offset = offsetof(t_vertex, color);
	return (attr_descriptions);
}
