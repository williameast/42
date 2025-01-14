/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/14 16:16:52 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	attach_mlx(t_ctrl *session)
{
	mlx_loop_hook(session->mlx_ptr, render_loop, session);
	mlx_key_hook(session->win_ptr, key_hook, session);
	mlx_hook(session->win_ptr, 17, 0, close_window, session);
	mlx_loop(session->mlx_ptr);
}

int main(int argc, char *argv[])
{
    t_ctrl session;
	t_map	*map;

    if (argc != 2)
		return(ft_printf("Usage: %s <filename>\n", argv[0]));
	map = parse_map(argv[1]);
    if (!map)
        return(ft_printf("ERROR: Error loading map.\n"));
    session = init_session(map);
	center_image(&session);
	if (DEBUG)
		print_map_struct(map);
	if (RENDER)
		attach_mlx(&session);
	free_map(map);
    return 0;
}
