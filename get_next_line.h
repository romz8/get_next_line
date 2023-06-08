/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:49:01 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/07 12:47:35 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif
# include <unistd.h>
# include <stdlib.h>
#include <stdio.h> //WARNING !!!!!!!!!!!!!!!!!
typedef struct s_list
{
	char	*buff;
	struct s_list	*next;
}	t_list;


char	*get_next_line(int fd);
t_list	*read_to_node(int fd, int *byte_read);
int		ft_search_nl(t_list *node);
void	load_chain_list(t_list **list, int fd, int *read_error);
void	get_all_line(t_list *byte_list, char ** line);
void	measure_n_create(t_list **byte_buff, char **line);
void	clean_chain(t_list **byte_list);
void	ft_passover(t_list *byte_list, t_list **handover_node, int i, int j);
void	free_chain(t_list *list);

#endif
