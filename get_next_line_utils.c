/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:30:12 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/05 18:30:37 by rjobert          ###   ########.fr       */
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