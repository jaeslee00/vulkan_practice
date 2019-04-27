/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 09:50:23 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 10:23:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static VkVertexInputBindingDescription get_binding_description()
{
	VkVertexInputBindingDescription binding_descriptions = {};

	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(t_vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return (binding_description);
}

static VkVertexInputAttributeDescription *get_attr_description()
{
	VkVertexInputAttributeDescription	*attr_descriptions;

	attr_descriptions =
		(VkVertexInputAttributeDescription*)malloc(2 * sizeof(VkVertexInputAttributeDescription));

	attr_descriptions[0].binding = 0;
	attr_descriptions[0].location = 0;
	attr_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attr_descriptions[0].offset = offsetof(t_vertex, pos);

	attr_descriptions[1].binding = 0;
	attr_descriptions[1].location = 1;
	attr_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attr_descriptions[1].offset = offsetof(t_vertex, color);

	return (attr_descriptions);
}

