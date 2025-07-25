/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:58 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:59 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "mlx.h"
#include "multithreading.h"
#include "ray_b.h"

static void	wait_for_threads_rendering(t_main_struct *main_struct)
{
	pthread_barrier_wait(&main_struct->thread_manager->render);
}

static void	start_next_frame(t_main_struct *main_struct)
{
	pthread_barrier_wait(&main_struct->thread_manager->frame);
}

int	frame_display(t_main_struct *main_struct)
{
	start_next_frame(main_struct);
	wait_for_threads_rendering(main_struct);
	mlx_put_image_to_window(main_struct->mlx_ptr, main_struct->win_ptr,
		main_struct->frame->sprite, 0, 0);
	if (!overlay(main_struct))
		return (1);
	return (0);
}
