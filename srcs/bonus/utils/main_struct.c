/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:46:03 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:46:04 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"
#include "structs_b.h"

int	init_r_h_tab(t_main_struct *main_struct)
{
	int	i;

	main_struct->cos_r_h_tab = malloc(sizeof(double) * WINDOW_WIDTH);
	main_struct->r_h_tab = malloc(sizeof(double) * WINDOW_WIDTH);
	if (main_struct->cos_r_h_tab == NULL || main_struct->r_h_tab == NULL)
		return (false);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		main_struct->r_h_tab[i] = atan(2 * tan(FOVHALF)
				/ WINDOW_WIDTH * (i - WINDOW_WIDTH * 0.5));
		main_struct->cos_r_h_tab[i] = cos(main_struct->r_h_tab[i]);
		if (main_struct->cos_r_h_tab[i] == 0)
			main_struct->cos_r_h_tab[i] = 0.00001;
		i++;
	}
	return (true);
}

int	is_moving(t_main_struct *main_struct)
{
	if (main_struct->inputs[UP] + main_struct->inputs[DOWN] == 1
		|| main_struct->inputs[RIGHT] + main_struct->inputs[LEFT] == 1
		|| main_struct->inputs[TRIGHT] + main_struct->inputs[TLEFT] == 1)
		return (true);
	return (false);
}
