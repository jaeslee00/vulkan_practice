/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:01:36 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/10 16:23:39 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	matrix_perspective()
{

}

void	model_rotation()
{

}

void	model_transformation()
{

}

void	view_lookat(float *view, float *cam_pos, float *cam_target, float *up_u_vector)
{
	float	lookat[16];
	float	h_vector[3];
	float	u_vector[3];
	float	f_vector[3];

	vec3_sub(f_vector, cam_pos, cam_target);
	vec3_cross(h_vector, f_vector, up_u_vector);
	vec3_normalize(h_vector);
	vec3_cross(u_vector, h_vector, f_vector);

	/* Gram-Schmidt matrix */
	view[0] = h_vector[0];
	view[1] = h_vector[1];
	view[2] = h_vector[2];
	view[3] = (h_vector[0] * -cam_pos[0]) +
					(h_vector[1] * -cam_pos[1]) * (h_vector[2] * -cam_pos[2]);

	view[4] = u_vector[0];
	view[5] = u_vector[0];
	view[6] = u_vector[0];
	view[7] = (u_vector[0] * -cam_pos[0]) +
					(u_vector[1] * -cam_pos[1]) * (u_vector[2] * -cam_pos[2]);

	view[8] = f_vector[0];
	view[9] = f_vector[0];
	view[10] = f_vector[0];
	view[11] = (f_vector[0] * -cam_pos[0]) +
					(f_vector[1] * -cam_pos[1]) * (f_vector[2] * -cam_pos[2]);

	view[12] = 0.0f;
	view[13] = 0.0f;
	view[14] = 0.0f;
	view[15] = 1.0f;
}

void	view_updates(float *view)
{

}

void	input_loop()
{
	t_ubo		ubo;
	ft_bzero(&ubo, sizeof(t_ubo));
	view_updates(&ubo.view);
	model_rotation(&ubo.model);
	model_transformation(&ubo.model);
	projection_updates(&ubo.proj);
}
