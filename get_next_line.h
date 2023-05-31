/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:49:01 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/31 21:30:02 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER 40
# include <unistd.h>
# include <stdlib.h>
typedef struct s_list
{
	char	buff[BUFFER];
	struct s_list	*next;
}	t_list;


char	*get_next_line(int fd);
t_list  *read_to_node(int fd, int *byte_read);
t_list  *create_chain(t_list *byte_list, int fd, int *size);
char    *all_line(t_list *byte_list, int size);
void    ft_traverse(char *s, t_list *node);
int ft_is_next_char(t_list *node);

#endif
