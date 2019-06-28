/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 12:16:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/17 19:09:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PARTICLES_H
# define _PARTICLES_H
# include "visualizer.h"

# define PARTICLES_COUNT 1024


typedef struct	s_particle
{
	float	pos[4]; // 0 1 2 = position, 3 = mass
	float	velocity[4]; // 0 1 2 = velocity 3 = height-dependent color gradient
}				t_particle

typedef struct	s_compute_ubo
{
	float	time_delta;
	float	dest[3]; // point of attraction
	int32_t	particle_count;
}				t_compute_ubo

typedef struct	s_particle_ubo
{
	float	model[16];
	float	view[16];
	float	proj[16];
}

typedef struct	s_particle
{
	VkQueue						graphics_queue;
	VkQueue						compute_queue;
	VkQueue						present_queue;
	uint32_t					graphics_queue_family_index;
	uint32_t					compute_queue_family_index;
	uint32_t					present_queue_family_index;

	VkCommandPool				command_pool;
	VkCommandBuffer				*command_buffers;

	VkDescriptorSetLayout		descriptor_set_layout;
	VkDescriptorPool			descriptor_pool;
	VkDescriptorSet				*descriptor_sets; /*TODO MALLOC */
	VkPipelineLayout			pipeline_layout;
	VkPipeline					graphics_pipeline;
	VkRenderPass				renderpass;

}
particles_graphics_pipeline(t_vulkan *vk);
particles_compute_pipeline(t_vulkan *vk);

#endif
