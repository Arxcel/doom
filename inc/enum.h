/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlov <vkozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:30:14 by vkozlov           #+#    #+#             */
/*   Updated: 2019/03/09 11:30:14 by vkozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum
{
	MaxQueue = 32
};

enum	e_bool {false, true} __attribute__((packed));

# define _BOOL  typedef enum e_bool bool

_BOOL;

#endif