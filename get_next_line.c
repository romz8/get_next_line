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
	char	*line;
	static t_list	*byte_list;

	if (fd < 0 || BUFFER <= 0)
		return (NULL);
	byte_list = load_chain_list(byte_list, fd);
	if (!byte_list)
		return (NULL);
	line = get_all_line(byte_list);
	clean_chain(&byte_list);
	return (line);
}

//we create a node and char *s inside of size BUFFER + 1 -> protect both malloc for mem alloc issues
//read into it -> free node and its content if reading issue, then null terminate the content and return the node
t_list	*read_to_node(int fd, int *byte_read)
{
	t_list	*node;
		
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->buff = malloc(BUFFER + 1);
	if (!node->buff)
	{
		free(node);
		return (NULL);
	}
	*byte_read = read(fd, node->buff, BUFFER);
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
	
int	ft_search_nl(t_list *node)
{
	int i;

	i = 0;
	if (!node)
		return (0);
	while (node->buff[i])
	{
		if (node->buff[i] == '\n')
			return(1);
		i++;
	}
	return (0);
}

//we receive a list - if it is null : we add a node to it which will be the first byte to be read - else we just build on prevous node
//then as long as we have byte to read or that we don't find the \n character : we load nodes full of buffer read to the chain
t_list	*load_chain_list(t_list *byte_list, int fd)
{	
	t_list 	*node;
	t_list	*head;
	int		byte_read;
	int		flag;

	byte_read = 1;
	if (!byte_list)
		byte_list = read_to_node(fd, &byte_read);
	head = byte_list;
	while (byte_read != 0 && !ft_search_nl(byte_list)) 
	{
		node = read_to_node(fd, &byte_read);
		byte_list->next = node;
		byte_list = byte_list->next;
	}
	return (head);
}

//we will load all of the linked list contennt (until null or \n) into line
// 1 - measure and malloc
//2 - copy by rolling the nodes into the "line" from the linked list with ft_load_line (using pointer passed as ref to keep array position)
char	*get_all_line(t_list *byte_list)
{
	char	*line;
	t_list	*temp;
	int		i;

	if (!byte_list)
		return (NULL);
	line = NULL;
	measure_n_create(&byte_list, &line);
	if (!line)
		return (NULL);
	i = 0;
	while(byte_list)
	{
		ft_load_line(line, &i, byte_list);
		byte_list = byte_list->next;
	}
	return (line);
}

//we need to use char ** to ensure the memory we allocate 
void	measure_n_create(t_list **byte_buff, char **line)
{
	int	i;
	int	j;
	t_list	*byte_list;

	byte_list = *byte_buff;
	if (!byte_list)
		return ;
	i = 0;
	while(byte_list)
	{
		j = 0;
		while (byte_list->buff[j])
		{
			if (byte_list->buff[j] == '\n')
			{
				j++;
				break ;
			}
			j++;
		}
		i = j;
		byte_list = byte_list->next;
	}
	*line = malloc(i + 1);
	(*line)[i] = '\0';
}
//from the line that we jsut mallocated, load a node, copy it's buffer into line, and roll to next node until we reach /n or EOF
void	ft_load_line(char *line, int *i, t_list *node)
{
	int	j;

	if (node == NULL)
		return ;
	j = 0;
	while (node->buff[j] && node->buff[j] != '\n')
	{
		line [*i] = node->buff[j];
		*i += 1;
		j++;
	}
	if (node->buff[j] == '\n')
		line [*i] = node->buff[j]; //becasue need the nl as well
}
// 1 - we will clean the list and the nodes 
// 2 - we go the last node -> clone it and incorporate only the charcetrs after the next line
// 3 - we will leave on the chain only the remaining characters so that read() will build on off 
void	clean_chain(t_list **buff_list)
{
	t_list *handover_node;
	t_list  *temp;
	t_list  *byte_list;
	
	byte_list = *buff_list;
	if (!byte_list)
		return ;
	while (byte_list && byte_list->next)
	{
		temp = byte_list->next;
		free_node(byte_list);
		byte_list = temp;
	}
	handover_node = malloc(sizeof(t_list));
	if (handover_node)
		ft_passover(byte_list, &handover_node, 0 , 0);
	free_node(byte_list);
	*buff_list = handover_node;
	printf("PASSOVER : %s\n", (*buff_list)->buff);
}
//first we measure the length of the node in char / bytes -> then we measure when is the \n if there is one
// if there is none (i == j) -> we return - else we create a handover node that will contains the remaining characer
//the purpose is to pass the remaining char in static t_list for the next line 
void	ft_passover(t_list *byte_list, t_list **handover_node, int i, int j)
{
	while (byte_list->buff[j])
		j++;
	while (byte_list->buff[i] && byte_list->buff[i] != '\n')
		i++;
	if (byte_list->buff[i] != '\n')
	i++;
	(*handover_node)->buff = malloc ((j - i) + 1);
	if (!(*handover_node)->buff)
	{
		free(*handover_node);
		return;
	}
	(*handover_node)->next = NULL;
	j = 0;
	while (byte_list->buff[i])
	{
		(*handover_node)->buff[j] = byte_list->buff[i];
		i++;
		j++;
	}
	(*handover_node)->buff[j] = '\0';
}

//freeing a node and its content while respecting null pointer risk
void	free_node(t_list *node)
{
	if (!node)
		return ;
	if (node->buff)
		free(node->buff);
	free(node);
}