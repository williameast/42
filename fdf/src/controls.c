/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:07:27 by William           #+#    #+#             */
/*   Updated: 2025/01/07 15:20:52 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


/* // kill stuff */
/* mlx_destroy_window(data->mlx_ptr, data->win_ptr); */
/* 	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img); */
/* 	mlx_destroy_display(data->mlx_ptr); */
/* 	free(data->mlx_ptr); */

void exit_program(t_ctrl *session)
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
// Key event handler
int key_hook(int keycode, t_ctrl *ctrl)
{
    if (keycode == 65307) // 65307 is the keycode for ESC
    {
        exit_program(ctrl);
    }
    return (0);
}
// Window close event handler
int close_window(t_ctrl *ctrl)
{
    exit_program(ctrl);
    return (0);
}
