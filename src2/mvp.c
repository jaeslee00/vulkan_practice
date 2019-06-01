/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 23:11:24 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/29 15:55:39 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "matrix.h"
#include "vector.h"
#include <math.h>

void	update_model(t_ubo *ubo)
{
//	mat4_rotation(ubo->model, g_cam.rad_yaw, g_cam.rad_pitch);
//	mat4_translation(ubo->model, g_cam.cam_pos[0], g_cam.cam_pos[1], 0.0f);
	mat4_identity(ubo->model);
	// for (int i=0;i<4;i++)
	// printf("%f %f %f %f\n", ubo->model[i*4+0], ubo->model[i*4+1], ubo->model[i*4+2], ubo->model[i*4+3]);
	// printf("--------------------------------------------------\n");
}

void	update_proj(t_ubo *ubo)
{
	float	near_width;
	float	aspect_ratio;
	float	f;
	float	*proj;

	proj = ubo->proj;
//	near_width = NEAR_Z * tan(FOV / 2.f);
	f = 1.0f / tanf(FOV * 0.5f);
	aspect_ratio = WIDTH / HEIGHT;
	// proj[0 * 4 + 0] = NEAR_Z / near_width; //x 정사각형 모양 클리핑
	// proj[1 * 4 + 1] = -(NEAR_Z / near_width); //y 정사각형 모양 클리핑
	// proj[2 * 4 + 2] = (FAR_Z + NEAR_Z) / (FAR_Z - NEAR_Z);
	// proj[2 * 4 + 3] = 2.f * (FAR_Z * NEAR_Z) / (FAR_Z - NEAR_Z);
	// proj[3 * 4 + 2] = 1.f;

	// proj[0 * 4 + 0] = 1.0f / (WIDTH / HEIGHT); //x 정사각형 모양 클리핑
	// proj[1 * 4 + 1] = f; //y 정사각형 모양 클리핑
	// proj[2 * 4 + 2] = 0.0f;
	// proj[2 * 4 + 3] = -1.0f;
	// proj[3 * 4 + 2] = NEAR_Z;
	// proj[3 * 4 + 3] = 0.0f;

	proj[0 * 4 + 0] = f / aspect_ratio;
	proj[0 * 4 + 1] = 0.0f;
	proj[0 * 4 + 2] = 0.0f;
	proj[0 * 4 + 3] = 0.0f;

	proj[1 * 4 + 0] = 0.0f;
	proj[1 * 4 + 1] = -f;
	proj[1 * 4 + 2] = 0.0f;
	proj[1 * 4 + 3] = 0.0f;

	proj[2 * 4 + 0] = 0.0f;
	proj[2 * 4 + 1] = 0.0f;
	proj[2 * 4 + 2] = -(FAR_Z) / (FAR_Z - NEAR_Z);
	proj[2 * 4 + 3] = -1.0f;

	proj[3 * 4 + 0] = 0.0f;
	proj[3 * 4 + 1] = 0.0f;
	proj[3 * 4 + 2] = -(2.f * FAR_Z * NEAR_Z) / (FAR_Z - NEAR_Z);
	proj[3 * 4 + 3] = 0.0f;
}

void	view_lookat(t_ubo *ubo, float *cam_target)
{
	float	*view;
	float	h_vec[3];
	float	u_vec[3];
	float	f_vec[3];
	float	up_u_vec[3];

	view = ubo->view;
	up_u_vec[0] = 0.0f;
	up_u_vec[1] = 1.0f;
	up_u_vec[2] = 0.0f;
	vec3_sub(f_vec, g_cam.cam_pos, cam_target);
	vec3_normalize(f_vec);
	vec3_cross(h_vec, up_u_vec, f_vec);
	vec3_normalize(h_vec);
	vec3_cross(u_vec, f_vec, h_vec);
//	vec3_normalize(f_vec);
//	vec3_normalize(h_vec);
//	printf("f_vec : %f %f %f\n", f_vec[0], f_vec[1], f_vec[2]);
	//  printf("h_vec : %f %f %f\n", h_vec[0], h_vec[1], h_vec[2]);
	//  printf("u_vec : %f %f %f\n", u_vec[0], u_vec[1], u_vec[2]);
//	printf("%f %f %f\n", g_cam.cam_pos[0] - cam_target[0], g_cam.cam_pos[1] - cam_target[1], g_cam.cam_pos[2] - cam_target[2]);
//	printf("%f %f %f\n", g_cam.cam_pos[0], g_cam.cam_pos[1], g_cam.cam_pos[2]);
//	printf("%f %f %f\n", cam_target[0], cam_target[1], cam_target[2]);
	/* Gram-Schmidt matrix */
	view[0] = h_vec[0];
	view[4] = h_vec[1];
	view[8] = h_vec[2];
	view[12] = -((h_vec[0] * g_cam.cam_pos[0]) +
					(h_vec[1] * g_cam.cam_pos[1]) +
						(h_vec[2] * g_cam.cam_pos[2]));

	view[1] = u_vec[0];
	view[5] = u_vec[1];
	view[9] = u_vec[2];
	view[13] = -((u_vec[0] * g_cam.cam_pos[0]) +
					(u_vec[1] * g_cam.cam_pos[1]) +
						(u_vec[2] * g_cam.cam_pos[2]));

	view[2] = f_vec[0];
	view[6] = f_vec[1];
	view[10] = f_vec[2];
	view[14] = -((f_vec[0] * g_cam.cam_pos[0]) +
					(f_vec[1] * g_cam.cam_pos[1]) +
						(f_vec[2] * g_cam.cam_pos[2]));

	view[3] = 0.0f;
	view[7] = 0.0f;
	view[11] = 0.0f;
	view[15] = 1.0f;
}

void	update_view(t_ubo *ubo)
{
	// float	tmp[3];
	float	target[3];

	target[0] = g_cam.cam_pos[0] + g_cam.cam_front[0];
	target[1] = g_cam.cam_pos[1] + g_cam.cam_front[1];
	target[2] = g_cam.cam_pos[2] + g_cam.cam_front[2];
//	target[0] = 0.0f;
//	target[1] = 0.0f;
//	target[2] = 0.0f;

	// float x = 3.f;
	// g_cam.cam_pos[0] = cos(glfwGetTime()*x);
	// g_cam.cam_pos[2] = sin(glfwGetTime()*x);
//	printf("%f %f %f\n", g_cam.cam_pos[0], g_cam.cam_pos[1], g_cam.cam_pos[2]);
	view_lookat(ubo, target);
//	mat4_identity(ubo->view);
}
