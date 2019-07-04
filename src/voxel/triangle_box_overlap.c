/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_box_overlap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:16:35 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/30 21:49:14 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlap_test.h"

int		tri_box_overlap(float *box_center, float voxel_size, float *vtx0,
			float *vtx1, float *vtx2, float *normal)
{
	/* translated vtx coordinate of triangle to with box center coordinate as 0,0,0 */
	float	v0[3];
	float	v1[3];
	float	v2[3];
	float half_size[3];

	/* edge of the triangle */
	float	e0[3];
	float	e1[3];
	float	e2[3];

	/* absolute value in each xyz component of a vector */
	float	abs_ex;
	float	abs_ey;
	float	abs_ez;

	/* min and max value for test 2 */
	float	min;
	float	max;

	vec3_sub(v0, vtx0, box_center);
	vec3_sub(v1, vtx1, box_center);
	vec3_sub(v2, vtx2, box_center);

	vec3_sub(e0, v1, v0);
	vec3_sub(e1, v2, v1);
	vec3_sub(e2, v0, v2);

	half_size[0] = voxel_size * 0.5f;
	half_size[1] = voxel_size * 0.5f;
	half_size[2] = voxel_size * 0.5f;
///////////////////////////////////////////////////////////////
// OVERLAP_TEST 3

/*    use separating axis theorem to test overlap between triangle and box */
/*    need to test for overlap in these directions: */
/*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */
/*       we do not even need to test these) */
/*    2) normal of the triangle */
/*    3) crossproduct(edge from tri, {x,y,z}-directin) */
/*       this gives 3x3=9 more tests */

	//xyz-component of e0 abs_ex abs_ey abs_ez
	abs_ex = fabsf(e0[0]);
	abs_ey = fabsf(e0[1]);
	abs_ez = fabsf(e0[2]);

	axis_x_test_e0(e0[2], e0[1], abs_ez, abs_ey, v0, v2, half_size);
	axis_y_test_e0(e0[2], e0[0], abs_ez, abs_ex, v0, v2, half_size);
	axis_z_test_e0(e0[1], e0[0], abs_ey, abs_ex, v1, v2, half_size);

	// p0 = e0[2] * v0[1] - e0[1] * v0[2];
	// p2 = e0[2] * v2[1] - e0[1] * v2[2];
	// rad = abs_ez * half_size[1] + abs_ey * half_size[2];


	// p0 = -e0[2] * v0[0] + e0[0] * v0[2];
	// p2 = -e0[2] * v2[0] + e0[0] * v2[2];
	// rad = abs_ez * half_size[0] + abs_ex * half_size[2];


	// p1 = e0[1] * v1[0] - e0[0] * v1[1];
	// p2 = e0[1] * v2[0] - e0[0] * v2[1];
	// rad = abs_ey * half_size[0] + abs_ex * half_size[1];

///////////////////////////////////////////////////////////////

	abs_ex = fabsf(e1[0]);
	abs_ey = fabsf(e1[1]);
	abs_ez = fabsf(e1[2]);

	axis_x_test_e1(e1[2], e1[1], abs_ez, abs_ey, v0, v2, half_size);
	axis_y_test_e1(e1[2], e1[0], abs_ez, abs_ex, v0, v2, half_size);
	axis_z_test_e1(e1[1], e1[0], abs_ey, abs_ex, v0, v1, half_size);

	// p0 = e1[2] * v0[1] - e1[1] * v0[2];
	// p2 = e1[2] * v2[1] - e1[1] * v2[2];

	// p0 = -e1[2] * v0[0] + e1[0] * v0[2];
	// p2 = -e1[2] * v2[0] + e1[0] * v2[2];

	// p0 = e1[1] * v0[0] - e1[0] * v0[1];
	// p1 = e1[1] * v1[0] - e1[0] * v1[1];
/////////////////////////////////////////////////////////////

	abs_ex = fabsf(e2[0]);
	abs_ey = fabsf(e2[1]);
	abs_ez = fabsf(e2[2]);

	axis_x_test_e2(e2[2], e2[1], abs_ez, abs_ey, v0, v1, half_size);
	axis_y_test_e2(e2[2], e2[0], abs_ez, abs_ex, v0, v1, half_size);
	axis_z_test_e2(e2[1], e2[0], abs_ey, abs_ex, v1, v2, half_size);

	// p0 = e2[2] * v0[1] - e2[1] * v0[2];
	// p1 = e2[2] * v1[1] - e2[1] * v1[2];

	// p0 = -e2[2] * v0[0] + e2[0] * v0[2];
	// p1 = -e2[2] * v1[0] + e1[0] * v1[2];

	// p1 = e2[1] * v1[0] - e2[0] * v1[1];
	// p2 = e2[1] * v2[0] - e2[0] * v2[1];

/////////////////////////////////////////////////////////////

//OVERLAP_TEST 1
	aabb_test(v0[0], v1[0], v2[0], half_size[0]); /* x-axis */
		//min  > half_size[0] || max < -half_size[0] --> doesn't overlap
	aabb_test(v0[1], v1[1], v2[1], half_size[1]); /* y-axis */
		//min  > half_size[1] || max < -half_size[1] --> doesn't overlap
	aabb_test(v0[2], v1[2], v2[2], half_size[2]); /* z-axis */
		//min  > half_size[2] || max < -half_size[2] --> doesn't overlap

//OVERLAP_TEST 2

plane_box_test(normal, v0, half_size);

return (1);
//if all test passes, it overlaps!
}
