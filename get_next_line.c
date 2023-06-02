/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:52:49 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/02 13:56:34 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
void	CHECK_PRINT(t_list *byte)
{
	int x = 0;
	while(byte)
	{
		printf("%i : \n%s\n", x, byte->buff);
		x++;
		byte = byte->next;
	}
}

char	*get_next_line(int fd)
{
	int		size;
	t_list	*byte_list;

	if (fd < 0 || BUFFER <= 0)
		return (NULL);
	size = 0;
	byte_list = NULL;
	byte_list = create_chain(byte_list, fd, &size);
	//CHECK_PRINT(byte_list);
	printf("%i\n", size);
	return (all_line(byte_list, size));	
}

t_list	*read_to_node(int fd, int *byte_read, int *size, int *flag)
{
	t_list	*node;
	int	i;
	
	buf = malloc(BUFFER + 1);
	if (!buff)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return(NULL);
	*byte_read = read(fd, buff, BUFFER);
	buff[byte_read] = '\0';
	node->buff = buff;
	node->next = NULL;
	i = 0; //search for nl 
	while (node->buff[i] && node->buff[i] != '\n')
		i++;
	if (i < BUFFER)
		*flag = 0;
	*size += i;
	return (node);
}
	
t_list	*create_chain(t_list *byte_list, int fd, int *size)
{	
	t_list 	*node;
	t_list	*head;
	int		byte_read;
	int		flag;

	byte_read = 0;
	flag = 1;
	byte_list = read_to_node(fd, &byte_read, size, &flag);
	head = byte_list;
	while (byte_read != 0 && flag != 0) 
	{
		node = read_to_node(fd, &byte_read, size, &flag);
		byte_list->next = node;
		byte_list = byte_list->next;
	}
	return (head);
}
	
char	*all_line(t_list *byte_list, int size)
{
	char *line;
	t_list *temp;

	if (!byte_list)
		return (NULL);
	line = malloc(size + 1);
	while(byte_list)
	{
		ft_traverse(line, byte_list, size);
		temp = byte_list->next;
		free(byte_list);
		byte_list = temp;		
	}
	line[size] = '\0';
	return (line);
}

void	ft_traverse(char *s, t_list *node, int size)
{
	static int	x;
	int			j;

	j = 0;
	while (x < size && node->buff[j])
	{
		s[x] = node->buff[j];
		x++;
		j++;
	}
}
