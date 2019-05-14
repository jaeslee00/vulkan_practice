/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 23:11:24 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 02:19:14 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "matrix.h"
#include "math.h"
float		g_angle = 0.0f;
void	update_model(t_ubo *ubo)
{
	g_angle += 0.001f;
	mat4_rotation(ubo->model, 30.f, g_angle);
}
void	update_view(t_ubo *ubo)
{
	mat4_identity(ubo->view);
}
void	update_proj(t_ubo *ubo)
{
	mat4_identity(ubo->proj);
}
