/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_callbacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:27:59 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/02 19:31:07 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vector.h"

void	reset_cam(uint32_t width, uint32_t height)
{
	g_cam.cam_pos[0] = 0.0f;
	g_cam.cam_pos[1] = 0.0f;
	g_cam.cam_pos[2] = 2.0f;
	g_cam.cam_front[0] = 0.0f;
	g_cam.cam_front[1] = 0.0f;
	g_cam.cam_front[2] = -1.0f;
	g_cam.last_x = width / 2;
	g_cam.last_y = height / 2;
	g_cam.yaw = -90.0f;
	g_cam.pitch = 0.0f;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	float	camera_speed;
	float	up_vec[3];
	float	tmp[3];

	camera_speed = 0.1f;
	up_vec[0] = 0.0f;
	up_vec[1] = 1.0f;
	up_vec[2] = 0.0f;
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		vec3_cross(tmp, g_cam.cam_front, up_vec);
		vec3_normalize(tmp);
		g_cam.cam_pos[0] += camera_speed * tmp[0];
		g_cam.cam_pos[1] += camera_speed * tmp[1];
		g_cam.cam_pos[2] += camera_speed * tmp[2];
		//g_cam.cam_pos[0] += camera_speed;
	}
	// else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	// 	g_cam.velocity[0] = 0.0f;
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		vec3_cross(tmp, g_cam.cam_front, up_vec);
		vec3_normalize(tmp);
		g_cam.cam_pos[0] -= camera_speed * tmp[0];
		g_cam.cam_pos[1] -= camera_speed * tmp[1];
		g_cam.cam_pos[2] -= camera_speed * tmp[2];
		//g_cam.cam_pos[0] -= camera_speed;
	}
	// else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	// 	g_cam.velocity[0] = 0.0f;
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		g_cam.cam_pos[0] += camera_speed * g_cam.cam_front[0];
		g_cam.cam_pos[1] += camera_speed * g_cam.cam_front[1];
		g_cam.cam_pos[2] += camera_speed * g_cam.cam_front[2];
	}
	// else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	// 	g_cam.velocity[2] = 0.0f;
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		g_cam.cam_pos[0] -= camera_speed * g_cam.cam_front[0];
		g_cam.cam_pos[1] -= camera_speed * g_cam.cam_front[1];
		g_cam.cam_pos[2] -= camera_speed * g_cam.cam_front[2];
	}
	// else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	// 	g_cam.velocity[2] = 0.0f;
	if (key == GLFW_KEY_R)
	{
		reset_cam(WIDTH, HEIGHT);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float	x_offset;
	float	y_offset;
	float	sensitivity;

	sensitivity = 0.03f;
	x_offset = xpos - g_cam.last_x;
	y_offset = g_cam.last_y - ypos;
	g_cam.last_x = xpos;
	g_cam.last_y = ypos;
	g_cam.yaw += x_offset * sensitivity;
	g_cam.pitch += y_offset * sensitivity;
	if (g_cam.pitch > 89.0f)
		g_cam.pitch = 89.0f;
	if (g_cam.pitch < -89.0f)
		g_cam.pitch = -89.0f;

	g_cam.rad_yaw = (g_cam.yaw * PI) / 180.f;
	g_cam.rad_pitch = (g_cam.pitch * PI) / 180.f;

	g_cam.cam_front[0] = cosf(g_cam.rad_pitch) * cosf(g_cam.rad_yaw);
	g_cam.cam_front[1] = sinf(g_cam.rad_pitch);
	g_cam.cam_front[2] = cosf(g_cam.rad_pitch) * sinf(g_cam.rad_yaw);
	vec3_normalize(g_cam.cam_front);
}
