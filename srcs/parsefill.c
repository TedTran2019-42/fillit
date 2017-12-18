/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 20:08:36 by ttran             #+#    #+#             */
/*   Updated: 2017/12/17 20:04:03 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Creates new nodes to put tetriminos in-- expands the linked list to hold everything. */
int		ft_listcreate(t_tetri **p, char *str, int br)
{
	t_tetri	 *new;

	new = malloc(sizeof(t_tetri));
	new->next = 0;
	new->tetrimino = ft_convertdata(str, br, new);
	if (!(new->tetrimino))
		return (0);
	(*p)->next = new;
	(*p) = new;
	return (1);
}
/*Converts the buffer, which is in str format, into a two-dimensional array */
char	**ft_convertdata(char *str, int br, t_tetri *fuck)
{
	int 	i;
	char	**store;
	int 	n;
	
	if (ft_check_buffer(str, br) == 0)
		return (NULL);
	n = 0;
	store = (char **)malloc(sizeof(char *) * 5);
	while (n < 4)
		store[n++] = (char *)malloc(sizeof(char) * 5);
	store[4] = 0;
	n = 0;
	str[20] = '\0';
	while (*str)
	{
		i = 0;
		while (*str != '\n' && *str != '\0') 
			store[n][i++] = *str++;
		store[n++][i] = '\0';
		str++;
	}
	if (check_valid(fuck, store) == 0)
		return (NULL);
	return (store);
}

/* Goes through the file, putting the buffer into a linked list */
t_tetri	*parsefile(char *file)
{
	int 	fd;
	char	str[21];
	int		br;
	t_tetri	*list;
	t_tetri 	*p;
	
	fd = open(file, O_RDONLY);
	if (open_error(fd) == 0)
		return (NULL);
	list = malloc(sizeof(t_tetri));
	list->tetrimino = NULL;
	list->next = NULL;
	p = list;
	while ((br = read(fd, str, 21)) >= 20)
	{
		if (list->tetrimino == NULL)
		{
			if (!(list->tetrimino = ft_convertdata(str, br, list)))
					return (NULL);
		}
		else
			if (ft_listcreate(&p, str, br) == 0)
				return (NULL);
	}
	if (close_error(close(fd)) == 0)
		return (NULL); 
	if (br != 0)
		return (NULL);
	return (list);
}
/* Simple function to print the board from the linked list. */
void	print_pieces(t_tetri *pieces)
{
	t_tetri *p;
	int n;

	n = 0;
	p = pieces;
	while (p != 0)
	{
		while (p->tetrimino[n] != 0)
		{
			ft_putstr(p->tetrimino[n++]);
			write(1, "\n", 1);
		}
		write(1, "\n", 1);
		n = 0;
		p = p->next;
	}
}

/*Frees data, but I'm not entirely sure if this will get rid of all memory addresses used */
void	ft_free(t_tetri *tetri)
{
	t_tetri	*p;

	while (tetri != NULL)
	{
		p = tetri;
		tetri = tetri->next;
		p->tetrimino = 0;
		p->next = NULL;
		free(p);	
	}
} 