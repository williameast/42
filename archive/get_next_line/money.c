/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   money.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:19:39 by William           #+#    #+#             */
/*   Updated: 2024/08/15 12:33:17 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>

int main()
{
	int x = 4;
	int *px = &x;

	int y = *px;

	printf("%i\n", x);
	printf("%i\n", *px);
	printf("%i\n", y);





}