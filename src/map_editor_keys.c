/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:48:45 by sahafono          #+#    #+#             */
/*   Updated: 2019/04/29 15:09:54 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int				left_arrow_key(SDL_Keycode sym, t_map_editor *e)
{
	if (sym != SDLK_LEFT  || (e->n && e->sectors[e->n].num_walls < 2))
		return (1);
	if (!e->n && e->sectors[e->n].num_walls < 0)
		return (1);
	e->sectors[e->n].wall_vertice[e->sectors[e->n].num_walls - 1].texture = 0;
	e->sectors[e->n].num_walls--;
	if ((e->n == 0 && e->sectors[e->n].num_walls >= 0) || (e->n && e->sectors[e->n].num_walls > 1))
    	e->global_index--;
	if (e->mode == CLOSE)
		(e->mode)--;
	return (0);
}

int				up_arrow_key(SDL_Keycode sym, t_map_editor *e)
{
	if ((e->mode == TEXTURE || e->mode == CLOSE) && e->sectors[e->n].num_walls > 0
		&& e->sectors[e->n].wall_vertice[e->sectors[e->n].num_walls - 1].texture < TEXTURE_MAX)
		e->sectors[e->n].wall_vertice[e->sectors[e->n].num_walls - 1].texture++;
	else if (e->mode == FLOOR_HEIGHT &&
		e->sectors[e->n].floor_height + 10 < e->sectors[e->n].ceiling_height)
		e->sectors[e->n].floor_height += 10;
	else if (e->mode == CEILING_HEIGHT && e->sectors[e->n].ceiling_height + 10 <= MAX_CEILING_HEIGHT)
		e->sectors[e->n].ceiling_height += 10;
	else if (e->mode == TO && e->sectors[e->n].is_lift &&
		e->sectors[e->n].to + 30 <=e->sectors[e->n].ceiling_height)
		e->sectors[e->n].to += 10;
	else
		return (1);
	return (0);
}

int				down_arrow_key(SDL_Keycode sym, t_map_editor *e)
{
	if ((e->mode == TEXTURE || e->mode == CLOSE) && e->sectors[e->n].num_walls > 0 &&
		e->sectors[e->n].wall_vertice[e->sectors[e->n].num_walls - 1].texture > 0)
		e->sectors[e->n].wall_vertice[e->sectors[e->n].num_walls - 1].texture--;
	else if (e->mode == FLOOR_HEIGHT && e->sectors[e->n].floor_height - 10 >= MIN_FLOOR_HEIGHT)
		e->sectors[e->n].floor_height -= 10;
	else if (e->mode == CEILING_HEIGHT && e->sectors[e->n].ceiling_height - 10 > e->sectors[e->n].floor_height)
		e->sectors[e->n].ceiling_height -= 10;
	else if (e->mode == TO && e->sectors[e->n].is_lift)
		e->sectors[e->n].to -= 10;
	else
		return (1);
	return (0);
}

int				arrow_keys(SDL_Keycode sym, t_map_editor *e)
{
	if (sym != SDLK_UP && sym != SDLK_DOWN && sym != SDLK_LEFT)
		return (1);
	if ((e->mode == TEXTURE || e->mode == CLOSE) && !left_arrow_key(sym, e))
		return (1);
	if ((sym == SDLK_UP && !up_arrow_key(sym, e)) ||
		(sym == SDLK_DOWN && !down_arrow_key(sym, e)))
		return (0);
	else if (e->mode == IS_LIFTED)
	{
		e->sectors[e->n].is_lift = e->sectors[e->n].is_lift ? false : true;
		e->sectors[e->n].from = e->sectors[e->n].is_lift ? e->sectors[e->n].floor_height : 0;
	}
	else
		return (1);
	return (0);
}

int					player_save_keys(t_main *m, t_map_editor *e)
{
	int		i;
	t_dot	d;

	if (m->sdl.e.key.keysym.sym != SDLK_s && m->sdl.e.type != SDL_MOUSEBUTTONDOWN)
		return (1);
	if (m->sdl.e.key.keysym.sym == SDLK_s && e->mode >= PORTAL)
	{
		if (e->mode == PORTAL)
		{
			e->mode = CREATED;
			shift_left(e);
		}
		else if (e->mode == SAVE)
			serialize_map(m, e);
		return (0);
	}
	SDL_GetMouseState(&d.x, &d.y);
	i = -1;
	while (e->mode >= CREATED && e->mode < SPRITE_Z && ++i <= e->n)
		if (pnpoly(e->sectors[i].num_walls, e->sectors[i].wall_vertice, d))
		{
			m->map.player.sector_number = i;
			m->map.player.position.x = d.x;
			m->map.player.position.y = d.y;
			e->mode = PLAYER;
			return (0);
		}
	if (e->mode == SPRITE_Z && e->sprite_cnt < SPRITE_CNT)
	{
		e->sprites[e->sprite_cnt].position.x = d.x;
		e->sprites[e->sprite_cnt].position.y = d.y;
		return (0);
	}
	return (1);
}
