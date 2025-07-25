/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_facing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:46:28 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:46:28 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	is_facing_up(double ray_angle)
{
	return (ray_angle > PI);
}

int	is_facing_left(double ray_angle)
{
	return (ray_angle < PIXX15 && ray_angle > PIX2);
}

int	is_facing_right(double ray_angle)
{
	return (!is_facing_left(ray_angle));
}

int	is_facing_down(double ray_angle)
{
	return (!is_facing_up(ray_angle));
}
