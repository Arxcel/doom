/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:30:55 by vkozlov           #+#    #+#             */
/*   Updated: 2019/03/09 11:30:55 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "structure.h"

float		minf(float a, float b);
float		maxf(float a, float b);
float		clampf(float a, float min, float max);
float		crossf(float x0, float y0, float x1, float y1);
int			overlapf(float begin0, float end0, float begin1, float end1);
int			intersect_box(t_vertex v1, t_vertex v2, t_vertex v3, t_vertex v4);
t_vertex	intersect_line(t_vertex v1, t_vertex v2, t_vertex v3, t_vertex v4);
float		point_side(t_vertex p, t_vertex v1, t_vertex v2);
int			intersects(t_player const *p, t_sector const *cur_s,
														int v1, int v2);

#endif
