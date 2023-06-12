/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:52:49 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/09 16:51:00 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	*byte_list;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		free_chain(byte_list);
		byte_list = NULL;
		return (NULL);
	}
	line = NULL;
	load_chain_list(&byte_list, fd);
	if (!byte_list)
		return (NULL);
	get_all_line(byte_list, &line);
	if (line[0] == '\0' || !line)
	{
		free_chain(byte_list);
		byte_list = NULL;
		if (line)
			free(line);
		return (NULL);
	}
	clean_chain(&byte_list);
	return (line);
}

/*we create a node and char *s inside of size BUFFER + 1 -> protect both malloc
read into it -> free node and its content if reading issue
then null terminate the content and return the node */
t_list	*read_to_node(int fd, int *byte_read)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->buff = malloc(BUFFER_SIZE + 1);
	if (!node->buff)
	{
		free(node);
		return (NULL);
	}
	*byte_read = read(fd, node->buff, BUFFER_SIZE);
	if (*byte_read < 0)
	{
		free(node->buff);
		free(node);
		return (NULL);
	}
	node->buff[*byte_read] = '\0';
	node->next = NULL;
	return (node);
}

//we receive a list - if it is null : we add a node to it,
//which will be the first byte to be read
//else we just build on prevous node
//then as long as we have byte to read or that we don't find the \n character : 
//we load nodes full of buffer read to the chain
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
//2 - copy by rolling the nodes into the "line" from the linked list with 
//ft_load_line (using pointer passed as ref to keep array position)
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
			(*line)[i] = byte_list->buff[j];
		byte_list = byte_list->next;
	}
}

// 1 - we will clean the list and the nodes 
// 2 - we go the last node -> clone it and incorporate 
// only the charcetrs after the next line
// 3 - we will leave on the chain only the remaining characters so that 
// read() will build on off 
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
