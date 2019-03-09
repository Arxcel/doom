/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:32:12 by vkozlov           #+#    #+#             */
/*   Updated: 2019/03/09 14:59:36 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DOOM_NUKEM_H
# define FT_DOOM_NUKEM_H

# define W 800
# define H 600

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "ft_sdl.h"
# include "ft_libftu.h"
# include "structure.h"
# include "player.h"
# include "math_utils.h"

typedef struct		s_main
{
	t_sdl	sdl;
	t_map	map;
}					t_main;

void				sdl_hook(t_main *m);
void				sdl_loop(t_main *m);

t_vertex			get_player_direction(t_main *m);
void				move_player(t_main *m);
void				transform_player(t_map *map);

void				draw_screen(t_img *img, t_map *map);
#endif
