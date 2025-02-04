/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:07:27 by William           #+#    #+#             */
/*   Updated: 2025/01/18 11:32:35 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	exit_program(t_ctrl *session)
{
	ft_printf("INFO: exiting program and removing resources....\n");
	if (session->mlx_ptr && session->win_ptr)
	{
		mlx_destroy_window(session->mlx_ptr, session->win_ptr);
		ft_printf("INFO: mlx window destroyed.\n");
	}
	if (session->image.img_ptr)
	{
		mlx_destroy_image(session->mlx_ptr, session->image.img_ptr);
		ft_printf("INFO: session image destroyed.\n");
		mlx_destroy_display(session->mlx_ptr);
		ft_printf("INFO: session display destroyed.\n");
		session->image.img_ptr = NULL;
		ft_printf("INFO: image pointer destroyed.\n");
		session->image.addr = NULL;
		ft_printf("INFO: image address destroyed.\n");
		free(session->mlx_ptr);
		ft_printf("INFO: session pointer destroyed.\n");
	}
	if (session->map)
		free_map(session->map);
	exit(0);
}

// Window close event handler
int	close_window(t_ctrl *ctrl)
{
	exit_program(ctrl);
	return (0);
}

int	key_hook(int keycode, t_ctrl *ctrl)
{
	if (keycode == KEY_ESC)
		exit_program(ctrl);
	if (keycode == KEY_D)
		translate(ctrl, (ctrl->offset.scale), 0);
	if (keycode == KEY_A)
		translate(ctrl, -(ctrl->offset.scale), 0);
	if (keycode == KEY_S)
		translate(ctrl, 0, ctrl->offset.scale);
	if (keycode == KEY_W)
		translate(ctrl, 0, -(ctrl->offset.scale));
	if (keycode == KEY_I)
		scale(ctrl, 1);
	if (keycode == KEY_O)
		scale(ctrl, -1);
	if (keycode == KEY_R)
		reset_session(ctrl);
	if (keycode == KEY_SPC)
		ctrl->is_isometric = ternary(ctrl->is_isometric == 1, -1, 1);
	if (keycode)
		ctrl->draw_complete = 0;
	return (0);
}
