/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:52:49 by rjobert           #+#    #+#             */
/*   Updated: 2023/05/31 22:10:43 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
void	CHECK_PRINT(t_list *byte)
{
	int i = 0;
	while(byte)
	{
		printf("%i : %s\n", i, byte->buff);
		i++;
		byte = byte->next;
	}
}

char	*get_next_line(int fd)
{
	int		size;
	t_list	*byte_list;

	if (fd < 0 || BUFFER < 0)
		return (NULL);
	size = 0;
	byte_list = create_chain(fd, &size);
	CHECK_PRINT(byte_list);
	//printf("%i\n", size);
	return (all_line(byte_list, size));	
}

t_list	*read_to_node(int fd, int *byte_read)
{
	t_list	*node;
	t_list	*byte_list;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return(NULL);
	*byte_read = read(fd, node->buff, BUFFER);
	node->next = NULL;
	return (node);
}
	
t_list	*create_chain(int fd, int *size)
{	
	t_list 	*node;
	t_list	*byte_list;
	t_list	*head;
	int		byte_read;

	byte_read = 0;
	head = byte_read;read_to_node(fd, &byte_read);
	while (byte_read != 0) 
	{
		node = read_to_node(fd, &byte_read);
		byte_list->next = node;
		byte_list = byte_list->next;
		printf("%i : %s\n", byte_read, byte_list->buff);
		if (ft_is_next_char(byte_list) == 0)
			break ;
	}
	CHECK_PRINT(head);
	return (head);
}
	
int ft_is_next_char(t_list *node)
{
	int i;
	i = 0;
	while (node->buff[i])
	{
		if (node->buff[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*all_line(t_list *byte_list, int size)
{
	char *line;
	t_list *head;
	t_list *temp;

	if (!byte_list)
		return (NULL);
	head = byte_list;
	line = malloc(size + 1);
	while(byte_list)
	{
		ft_traverse(line, byte_list);
		temp = byte_list->next;
		free(byte_list);
		byte_list = temp;		
	}
	line[size] = '\0';
	return (line);
}

void	ft_traverse(char *s, t_list *node)
{
	static int	x;
	int			j;

	j = 0;
	while(s[x] && node->buff[j])
	{

		s[x] = node->buff[j];
		x++;
		j++;
	}
}
