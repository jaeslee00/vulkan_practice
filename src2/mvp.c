/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 23:11:24 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/14 00:40:43 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "matrix.h"
#include "math.h"

void	update_model(t_ubo *ubo)
{
	mat4_scaling(ubo->model, 1.5f);
}
void	update_view(t_ubo *ubo)
{
	mat4_identity(ubo->view);
}
void	update_proj(t_ubo *ubo)
{
	mat4_identity(ubo->proj);
}
