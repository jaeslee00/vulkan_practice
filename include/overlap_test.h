/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlap_test.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:05:30 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/30 21:49:32 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OVERLAP_TEST_H
# define OVERLAP_TEST_H
# include "vector.h"
# include "libft.h"
# include <math.h>
# define OVERLAP 1
# define NOT_OVERLAP 0

int		tri_box_overlap(float *box_center, float voxel_size, float *vtx0,
			float *vtx1, float *vtx2, float *normal);

/* test 1 */

int		aabb_test(float v0, float v1, float v2, float half_size);

/* test 2 */

int		plane_box_test(float *normal, float *vtx, float *half_size);


/* test 3 */

int		axis_x_test_e0(float z_comp, float y_comp, float z_size, float y_size,
			float *vtx0, float *vtx2, float *half_size);

int		axis_y_test_e0(float z_comp, float x_comp, float z_size, float x_size,
			float *vtx0, float *vtx2, float *half_size);

int		axis_z_test_e0(float y_comp, float x_comp, float y_size, float x_size,
			float *vtx1, float *vtx2, float *half_size);

int		axis_x_test_e1(float z_comp, float y_comp, float z_size, float y_size,
			float *vtx0, float *vtx2, float *half_size);

int		axis_y_test_e1(float z_comp, float x_comp, float z_size, float x_size,
			float *vtx0, float *vtx2, float *half_size);

int		axis_z_test_e1(float y_comp, float x_comp, float y_size, float x_size,
			float *vtx0, float *vtx1, float *half_size);

int		axis_x_test_e2(float z_comp, float y_comp, float z_size, float y_size,
			float *vtx0, float *vtx1, float *half_size);

int		axis_y_test_e2(float z_comp, float x_comp, float z_size, float x_size,
			float *vtx0, float *vtx1, float *half_size);

int		axis_z_test_e2(float y_comp, float x_comp, float y_size, float x_size,
			float *vtx1, float *vtx2, float *half_size);

#endif
