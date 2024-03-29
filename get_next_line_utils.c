/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:30:12 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/13 21:52:29 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_chain(t_list *list)
{
	t_list	*temp;

	if (!list)
		return ;
	while (list)
	{
		temp = list->next;
		free(list->buff);
		free(list);
		list = temp;
	}
	list = NULL;
}

int	ft_search_nl(t_list *node)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	while (node->buff[i])
	{
		if (node->buff[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

//1 - we run through the entire linked list : as long as there are nodes, 
//we read each node content char by char and count how many chars need 
//to be read until we find \n (included) 
//2 - we malloc this bytes quantity (1 char = 1 byte) 
void	measure_n_create(t_list **byte_buff, char **line, int i)
{
	int		j;
	t_list	*byte_list;

	byte_list = *byte_buff;
	if (!byte_list)
		return ;
	while (byte_list)
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
	*line = malloc((i + 1) * sizeof(char));
	if (*line == NULL)
		return ;
	(*line)[i] = '\0';
}

//1 - we measure the length of the node in char / bytes
//2 - we measure when is the \n if there is one
//3 - allocate corresponding memory for the buffer in 
//handover node that will contain the remaining characer : 
//the purpose is to pass the remaining char 
//in static t_list for the next line 
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
		return ;
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
