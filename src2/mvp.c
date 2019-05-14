/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 23:11:24 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 03:19:59 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "matrix.h"
#include "math.h"
float		g_angle1 = 0.0f;
float		g_angle2 = 0.0f;
void	update_model(t_ubo *ubo)
{
	// g_angle1 += 0.01f;
	// g_angle2 += 0.01f;
//	mat4_rotation(ubo->model, g_angle1, g_angle2);
	mat4_identity(ubo->model);
	// for (int i=0;i<4;i++)
	// printf("%f %f %f %f\n", ubo->model[i*4+0], ubo->model[i*4+1], ubo->model[i*4+2], ubo->model[i*4+3]);
	// printf("--------------------------------------------------\n");
}
void	update_view(t_ubo *ubo)
{
	mat4_identity(ubo->view);
}
void	update_proj(t_ubo *ubo)
{
	mat4_identity(ubo->proj);
}
