/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 18:42:49 by ttran             #+#    #+#             */
/*   Updated: 2017/12/16 14:03:57 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int main(int argc, char **argv)
{
	t_tetri *tetri;

	if (argc == 2)
	{
		if (!(tetri = parsefile(argv[1])))
			ft_putstr("Invalid file\n");
		print_pieces(tetri);
		ft_free(tetri);
	}
	else
	{
		ft_putstr("Usage:./fillit file");
		return (1);
	}
	return (0);
}