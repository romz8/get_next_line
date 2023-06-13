/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:02:25 by rjobert           #+#    #+#             */
/*   Updated: 2023/06/13 16:44:36 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_chain(t_list *list)
{
	t_list	*temp;

	if (!list)
		return ;
	while (list)
	{
		temp = list->next;
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
	if (*line)
		(*line)[i] = '\0';
}

//as we use an array and not a char poinnter in the bonus,
//we make a modification in the handover_process here
void	ft_passover(t_list *byte_list, t_list **handover_node, int i, int j)
{
	while (byte_list->buff[j])
		j++;
	while (byte_list->buff[i] && byte_list->buff[i] != '\n')
		i++;
	if (byte_list->buff[i] == '\n')
		i++;
	j = 0;
	while (byte_list->buff[i])
	{
		(*handover_node)->buff[j] = byte_list->buff[i];
		i++;
		j++;
	}
	while ((*handover_node)->buff[j])
		(*handover_node)->buff[j] = '\0';
}

int	check_line_over(char **line, t_list *list)
{
	if ((*line)[0] == '\0')
	{
		free_chain(list);
		free(*line);
		return (1);
	}
	return (0);
}
