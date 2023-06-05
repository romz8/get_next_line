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
		if (!byte)
			printf("THE CHAIN IS NULL\n");
		printf("NODE %i : %p : %s\n", x, byte->buff, byte->buff);
		x++;
		byte = byte->next;
	}
}

char	*get_next_line(int fd)
{
	char	*load;
	char	*line;
	static t_list	*byte_list;

	if (fd < 0 || BUFFER <= 0)
		return (NULL);
	load = NULL;
	load_chain_list(&byte_list, fd);
	if (!byte_list)
		return (NULL);
	get_all_line(byte_list, &load);
	line = ft_strdup(load);
	free(load);
	clean_chain(&byte_list);
	
	if (line[0] == '\0')
	{
		free_chain(byte_list);
		byte_list = NULL;
		free(line);
		return (NULL);
	}
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
	// printf("NODE CONTENT: %s \n", node->buff);
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
void	load_chain_list(t_list **list, int fd)
{	
	t_list 	*node;
	t_list	*head;
	int		byte_read;

 	byte_read = 1;
	if (!*list)
        *list = read_to_node(fd, &byte_read);
    head = *list;
	while (byte_read && !ft_search_nl(*list))
    {
        node = read_to_node(fd, &byte_read);
        (*list)->next = node;
        *list = (*list)->next;
    } 
	*list = head;
}

//we will load all of the linked list contennt (until null or \n) into line
// 1 - measure and malloc
//2 - copy by rolling the nodes into the "line" from the linked list with ft_load_line (using pointer passed as ref to keep array position)
void	get_all_line(t_list *byte_list, char ** line)
{
	int		i;

	if (!byte_list)
		return ;
	measure_n_create(&byte_list, line);
	if (!line)
		return ;
	i = 0;
	while(byte_list)
	{
		ft_load_line(line, &i, byte_list);
		byte_list = byte_list->next;
	}
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
				i++;
				break ;
			}
			i++;
			j++;
		}
		byte_list = byte_list->next;
	}
	*line = malloc(i + 1);
	(*line)[i] = '\0';
}
//from the line that we jsut mallocated, load a node, copy it's buffer into line, and roll to next node until we reach /n or EOF
void	ft_load_line(char **line, int *i, t_list *node)
{
	int	j;

	if (node == NULL)
		return ;
	j = 0;
	while (node->buff[j] && node->buff[j] != '\n')
	{
		(*line)[*i] = node->buff[j];
		*i += 1;
		j++;
	}
	if (node->buff[j] == '\n')
		(*line)[*i] = node->buff[j]; //becasue need the nl as well
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
		byte_list = byte_list->next;
	handover_node = malloc(sizeof(t_list));
	if (handover_node)
	{
		handover_node->next = NULL;
		ft_passover(byte_list, &handover_node, 0 , 0);
	}
	free_chain(*buff_list);
	*buff_list = handover_node;
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
	if (byte_list->buff[i] == '\n')
		i++;
	(*handover_node)->buff = malloc ((j - i) + 1);
	if (!(*handover_node)->buff)
	{
		free(*handover_node);
		return;
	}
	j = 0;
	while (byte_list->buff[i])
	{
		(*handover_node)->buff[j] = byte_list->buff[i];
		i++;
		j++;
	}
	(*handover_node)->buff[j] = '\0';
}

void	free_chain(t_list *list)
{
	t_list	*temp;

	if (!list)
		return ;
	while (list)
	{
		temp = list->next;
		if (list->buff)
			free(list->buff);
		free(list);
		list = temp;
	}
}

char	*ft_strdup(const char *s1)
{
	int	len;
	char	*cpy;
	int		i;
	
	len = 0;
	while (s1[len])
		len++;
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	return (cpy);
}