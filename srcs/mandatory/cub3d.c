/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:47:52 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:47:53 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft_dprintf.h"
#include "libft.h"
#include "main_struct.h"
#include "parsing.h"
#include "structs.h"

int	main(int ac, char **av)
{
	t_main_struct	main_struct;
	t_infos			infos;

	ft_memset(&main_struct, 0, sizeof(t_main_struct));
	ft_memset(&infos, 0, sizeof(t_infos));
	parsing(ac, av, &infos);
	if (!start_display(&main_struct, &infos))
		ft_dprintf(2, "Error\nExternal function fail during initialisation\n");
	free_main_struct(&main_struct);
	cleanup_parsing(&infos);
	return (EXIT_SUCCESS);
}
