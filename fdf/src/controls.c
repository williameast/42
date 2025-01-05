/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 12:07:27 by William           #+#    #+#             */
/*   Updated: 2025/01/05 22:09:18 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


// kill stuff


void exit_program(t_ctrl *session)
{
    // Perform any cleanup needed, such as freeing memory or closing files
    if (session->mlx_ptr && session->win_ptr)
    {
        mlx_destroy_window(session->mlx_ptr, session->win_ptr);
    }
	if (session->image.img_ptr)
	{
		mlx_destroy_image(session->mlx_ptr, session->image.img_ptr);
        session->image.img_ptr = NULL;
        session->image.addr = NULL;
	}
	if (session->map)
	{
		free_map(session->map);
	}


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
