/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 14:38:16 by vkozlov           #+#    #+#             */
/*   Updated: 2019/04/21 19:06:46 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		load_sound_mav(char *path, t_music *m, int i)
{
	char				*file_contents;
	zip_file_t			*f;
	zip_t				*z;
	struct zip_stat		st;
	SDL_RWops			*rwops;

	z = zip_open(RESOURCES, ZIP_CREATE, 0);
	if (!z)
		MSG(zip_strerror(z));
	zip_stat_init(&st);
	zip_stat(z, path, 0, &st);
	if (st.size < 1)
		MSG("No such sound");
	file_contents = malloc(st.size);
	f = zip_fopen_encrypted(z, path, 0, RESOURCES_PASS);
	if (!f)
		MSG(zip_strerror(z));
	if (zip_fread(f, file_contents, st.size) < 1 || zip_fclose(f))
		MSG(zip_strerror(z));
	rwops = SDL_RWFromMem(file_contents, st.size);
	if (!(m->snd[i] =
			Mix_LoadWAV_RW(rwops, SDL_TRUE)))
		MSG(SDL_GetError());
	zip_close(z);
	free(file_contents);
}

void			init_sounds(t_main *m)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
													2, 1500) == -1)
		MSG(Mix_GetError());
	load_sounds(m);
}

void			load_sounds(t_main *m)
{
	int i;

	i = -1;
	load_sound_mav("assets/sounds/Knife.wav", &m->music, ++i);
	load_sound_mav("assets/sounds/Pistol.wav", &m->music, ++i);
	load_sound_mav("assets/sounds/Machine Gun.wav", &m->music, ++i);
	load_sound_mav("assets/sounds/Gatling Gun.wav", &m->music, ++i);
	load_sound_mav("assets/sounds/Pickup.wav", &m->music, ++i);
	load_sound_mav("assets/sounds/Ammo.wav", &m->music, ++i);
	load_sound_mav("assets/sounds/Key.wav", &m->music, ++i);
	load_sound_mav("assets/sounds/Boss Gun.wav", &m->music, ++i);
}
