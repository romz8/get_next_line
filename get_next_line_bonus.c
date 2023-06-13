/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:01:52 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/13 16:43:17 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//as the bonus requires to read multiple fd at the same time,
//while using only one static variable, we use a hash_table
//which index will be the fd (forcing ourself to arbitrary
//limit of 256 values)
char	*get_next_line(int fd)
{
	char			*line;
	t_list			*byte_list;
	static t_list	*hash_table[256];

	byte_list = hash_table[fd];
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0 || fd > 255)
	{
		free_chain(byte_list);
		if (fd <= 255)
			hash_table[fd] = NULL;
		return (NULL);
	}
	line = NULL;
	load_chain_list(&byte_list, fd);
	if (!byte_list)
		return (NULL);
	get_all_line(byte_list, &line);
	if (check_line_over(&line, byte_list) == 1)
	{
		hash_table[fd] = NULL;
		return (NULL);
	}
	clean_chain(&byte_list);
	hash_table[fd] = byte_list;
	return (line);
}

/* to avoid a time ouut, we modified our struct node 
from mandatory partby declaring buff as an array and 
not a char pointer : as we look for speed we leverage 
more static memory while reading bytes into it  */
t_list	*read_to_node(int fd, int *byte_read)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	*byte_read = read(fd, node->buff, BUFFER_SIZE);
	if (*byte_read < 0)
	{
		free(node);
		return (NULL);
	}
	node->buff[*byte_read] = '\0';
	node->next = NULL;
	return (node);
}

//we receive a list - if it is null : we add a node to it,
//which will be the first byte to be read
//else we just build on previous nodes
//then as long as we have byte to read or that we don't find 
//the \n character : we load nodes full of buffer to the chain
void	load_chain_list(t_list **list, int fd)
{	
	t_list	*node;
	t_list	*head;
	int		byte_read;

	byte_read = 1;
	if (!*list)
		*list = read_to_node(fd, &byte_read);
	if (*list == NULL)
		return ;
	head = *list;
	while (byte_read > 0 && !ft_search_nl(*list))
	{
		node = read_to_node(fd, &byte_read);
		if (!node)
		{
			free_chain(head);
			*list = NULL;
			return ;
		}
		(*list)->next = node;
		*list = (*list)->next;
	}
	*list = head;
}

//we will load all of the linked list contennt (until null or \n) into line
//1 - measure and malloc
//2 - copy by rolling the nodes into the "line" from the linked list 
void	get_all_line(t_list *byte_list, char **line)
{
	int	i;
	int	j;

	i = 0;
	if (!byte_list)
		return ;
	measure_n_create(&byte_list, line, 0);
	if (!*line)
		return ;
	while (byte_list && *line)
	{
		j = 0;
		while (byte_list->buff[j] && byte_list->buff[j] != '\n')
		{
			(*line)[i] = byte_list->buff[j];
			i++;
			j++;
		}
		if (byte_list->buff[j] == '\n')
			(*line)[i++] = byte_list->buff[j];
		byte_list = byte_list->next;
	}
}

// 1 - we will clean the list and the nodes 
// 2 - we go the last node -> clone it and incorporate 
// only the charcetrs after the next line
// 3 - we will clean the list and initiate it to our handover node
// then the static variable hash table will keep only this node 
// and build new nodes for next call on top on the cleant chain 
void	clean_chain(t_list **buff_list)
{
	t_list	*handover_node;
	t_list	*byte_list;

	byte_list = *buff_list;
	if (!byte_list)
		return ;
	while (byte_list && byte_list->next)
		byte_list = byte_list->next;
	handover_node = malloc(sizeof(t_list));
	if (!handover_node)
	{
		free_chain(*buff_list);
		return ;
	}
	handover_node->next = NULL;
	ft_passover(byte_list, &handover_node, 0, 0);
	free_chain(*buff_list);
	*buff_list = handover_node;
}
