/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:55:50 by weast             #+#    #+#             */
/*   Updated: 2024/12/04 13:30:50 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* void	ft_put_pixel(t_graphics *gfx, t_crd crd, int colour) */
/* { */
/*     char *pxl; */
/*     int buffer_index = gfx->active_buffer; */

/*     if (crd.x >= 0 && crd.x < WIN_WIDTH && crd.y >= 0 && crd.y < WIN_HEIGHT) */
/*     { */
/*         pxl = gfx->addr[buffer_index] + (crd.y * gfx->line_length + crd.x * (gfx->bits_per_pixel) / 8); */
/*         *(unsigned int *)pxl = colour; */
/*     } */
/* } */

/* t_crd	init_crd(int x, int y) */
/* { */
/*     return ((t_crd){x, y}); */
/* } */

/* // Function to draw a rectangle */
/* void draw_rectangle1(t_graphics *gfx, t_crd start, int width, int height, int color) */
/* { */
/*     t_crd crd; // Coordinate for the current pixel */
/*     int i, j; */

/*     for (i = 0; i < height; i++) */
/*     { */
/*         for (j = 0; j < width; j++) */
/*         { */
/*             crd.x = start.x + j; // Set current x coordinate */
/*             crd.y = start.y + i; // Set current y coordinate */
/*             ft_put_pixel(gfx, crd, color); */
/*         } */
/*     } */
/* } */

/* void draw_rectangle(char *buffer_addr, int line_length, int bits_per_pixel, */
/*                     t_crd start, int width, int height, int color) */
/* { */
/*     t_crd crd; // Coordinate for the current pixel */
/*     int i, j; */

/*     for (i = 0; i < height; i++) */
/*     { */
/*         for (j = 0; j < width; j++) */
/*         { */
/*             crd.x = start.x + j; // Set current x coordinate */
/*             crd.y = start.y + i; // Set current y coordinate */

/*             // Ensure the pixel is within bounds */
/*             if (crd.x >= 0 && crd.x < WIN_WIDTH && crd.y >= 0 && crd.y < WIN_HEIGHT) */
/*             { */
/*                 char *pixel = buffer_addr + (crd.y * line_length + crd.x * (bits_per_pixel / 8)); */
/*                 *(unsigned int *)pixel = color; */
/*             } */
/*         } */
/*     } */
/* } */


/* void	swap_buffers(t_graphics *gfx) */
/* { */
/*     gfx->active_buffer = 1 - gfx->active_buffer; */
/* } */

/* int render(void *param) */
/* { */
/*     t_graphics *gfx = (t_graphics *)param; */

/*     // Determine inactive buffer */
/*     int inactive_buffer = 1 - gfx->active_buffer; */

/*     // Clear the inactive buffer */
/*     for (int y = 0; y < WIN_HEIGHT; y++) */
/*         for (int x = 0; x < WIN_WIDTH; x++) */
/*             *(unsigned int *)(gfx->addr[inactive_buffer] + (y * gfx->line_length + x * (gfx->bits_per_pixel / 8))) = 0x000000; */

/*     // Draw to the inactive buffer */
/*     if (gfx->active_buffer == 0) */
/*         draw_rectangle(gfx->addr[inactive_buffer], gfx->line_length, gfx->bits_per_pixel, */
/*                        (t_crd){0, 0}, 100, 100, GREEN); */
/*     else */
/*         draw_rectangle(gfx->addr[inactive_buffer], gfx->line_length, gfx->bits_per_pixel, */
/*                        (t_crd){150, 150}, 100, 100, RED); */

/*     // Swap buffers */
/*     swap_buffers(gfx); */

/*     // Display the active buffer */
/*     mlx_put_image_to_window(gfx->mlx_ptr, gfx->win_ptr, gfx->buffer[gfx->active_buffer], 0, 0); */

/*     usleep(500000); // Pause for 500ms to visualize swapping */
/*     return 0; */
/* } */

/* /\* int main() *\/ */
/* /\* { *\/ */
/* /\*     /\\* t_graphics gfx; *\\/ *\/ */

/* /\*     /\\* // Initialize MiniLibX and create window *\\/ *\/ */
/* /\*     /\\* gfx.mlx_ptr = mlx_init(); *\\/ *\/ */
/* /\*     /\\* gfx.win_ptr = mlx_new_window(gfx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Double Buffering"); *\\/ *\/ */

/* /\*     /\\* // Create image buffers *\\/ *\/ */
/* /\*     /\\* for (int i = 0; i < 2; i++) *\\/ *\/ */
/* /\*     /\\* { *\\/ *\/ */
/* /\*     /\\*     gfx.buffer[i] = mlx_new_image(gfx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT); *\\/ *\/ */
/* /\*     /\\*     gfx.addr[i] = mlx_get_data_addr(gfx.buffer[i], &gfx.bits_per_pixel, &gfx.line_length, &gfx.endian); *\\/ *\/ */
/* /\*     /\\* } *\\/ *\/ */
/* /\*     /\\* gfx.active_buffer = 0; *\\/ *\/ */

/* /\*     /\\* // Set render loop *\\/ *\/ */
/* /\*     /\\* mlx_loop_hook(gfx.mlx_ptr, render, &gfx); *\\/ *\/ */

/* /\*     /\\* // Start MiniLibX event loop *\\/ *\/ */
/* /\*     /\\* mlx_loop(gfx.mlx_ptr); *\\/ *\/ */

/* /\*     /\\* return 0; *\\/ *\/ */

/* /\* } *\/ */

/* /\* int main(void) *\/ */
/* /\* { *\/ */
/* /\*     char line[] = "1 2 3 4 5"; *\/ */
/* /\*     int length; *\/ */
/* /\*     t_crd *crds = convert_line_into_crds(line, 0, &length); *\/ */
/* /\*     if (!crds) *\/ */
/* /\*     { *\/ */
/* /\*         printf("Error converting line into crds.\n"); *\/ */
/* /\*         return (1); *\/ */
/* /\*     } *\/ */
/* /\*     for (int i = 0; i < length; i++) *\/ */
/* /\*     { *\/ */
/* /\*         printf("x: %d, y: %d, z: %d\n", crds[i].x, crds[i].y, crds[i].z); *\/ */
/* /\*     } *\/ */
/* /\*     free(crds); *\/ */
/* /\*     return (0); *\/ */
/* /\* } *\/ */
