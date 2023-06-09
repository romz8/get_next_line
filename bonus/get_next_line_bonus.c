/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:52:49 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/02 20:44:59 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	CHECK_PRINT(t_list *byte, int fd)
{
	int x = 0;
	while(byte)
	{
		if (!byte)
			printf("THE CHAIN IS NULL\n");
		printf("NODE %i fd %i: %p : %s\n", x, fd, byte->buff, byte->buff);
		x++;
		byte = byte->next;
	}
}

char	*get_next_line(int fd)
{
	char	*line;
	static t_list	*byte_list;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		free_chain(&byte_list, fd);
		return (NULL);
	}
	line = NULL;
	load_chain_list(&byte_list, fd);
	if (!byte_list)
		return (NULL);
	CHECK_PRINT(byte_list, fd);
	get_all_line(byte_list, &line, fd);
	if (line[0] == '\0' || !line) // case for empty line
	{
		free_chain(&byte_list, fd);
		if (line)
			free(line);
		return (NULL);
	}
	clean_chain(&byte_list, fd);
	return (line); 
}

/*we create a node and char *s inside of size BUFFER + 1 -> protect both malloc for mem alloc issues
read into it -> free node and its content if reading issue, then null terminate the content and return the node */
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
	node->fd = fd;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

//we receive a list - if it is null : we add a node to it which will be the first byte to be read - else we just build on prevous node
//then as long as we have byte to read or that we don't find the \n character : we load nodes full of buffer read to the chain
void	load_chain_list(t_list **list, int fd)
{	
	t_list 	*node;
	t_list	*head;
	int		byte_read;

	byte_read = 1;
	if (!*list)
        *list = read_to_node(fd, &byte_read);
		if (*list == NULL)
			return  ;
    head = *list;
	while (byte_read > 0 && !ft_search_nl(*list, fd))
    {
        node = read_to_node(fd, &byte_read);
		if (!node)
		{
			free_chain(list, fd);
			*list = NULL;
			return ;
		} 
		node->prev = *list;
		(*list)->next = node;
        *list = (*list)->next;
    }
	*list = head;
}

//we will load all of the linked list contennt (until null or \n) into line
// 1 - measure and malloc
//2 - copy by rolling the nodes into the "line" from the linked list with ft_load_line (using pointer passed as ref to keep array position)
void	get_all_line(t_list *byte_list, char ** line, int fd)
{
	int	i;
	int	j;

	i = 0;
	if (!byte_list)
		return ;
	measure_n_create(&byte_list, line, fd);
	if (!*line)
		return;
	while(byte_list && *line)
	{
		j = 0;
		while(byte_list->buff[j] && byte_list->buff[j] != '\n')
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
// 2 - we go the last node -> clone it and incorporate only the charcetrs after the next line
// 3 - we will leave on the chain only the remaining characters so that read() will build on off 
void	clean_chain(t_list **buff_list, int fd)
{
	t_list *handover_node;
	t_list  *byte_list;
	
	byte_list = *buff_list;
	if (!byte_list)
		return ;
	while (byte_list && byte_list->next)
		byte_list = byte_list->next;
	while (byte_list->fd != fd)
		byte_list = byte_list->prev;
	handover_node = malloc(sizeof(t_list));
	if (!handover_node)
    {
        free_chain(buff_list, fd);
        return;
    }
	handover_node->fd = fd;
	handover_node->next = NULL;
	handover_node->prev = NULL; //risk to break the list here ??
	ft_passover(byte_list, &handover_node, 0 , 0);
	ft_lstadd_back(buff_list, handover_node);
	free_chain(buff_list, fd);
	*buff_list = handover_node;
}