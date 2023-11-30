/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:13:21 by agallon           #+#    #+#             */
/*   Updated: 2023/11/23 20:13:22 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	// read close
#include <stdio.h>	// printf malloc free
#include <stdlib.h> // malloc free
#include <fcntl.h>	// open
#include "get_next_line.h"

///////////////////////////////////////////////////////
// #	RESET TEMP || CLEAN BUFFER
void	clean_buff(char *buff, int sw)
{	
	int	i;

	i = 0;
	if (sw == 0)
	{
		while (i < BUFFER_SIZE)
			buff[i++] = '\0';
	}
	else
	{
		while (i < BUFFER_SIZE && buff[i] != '\0')
			buff[i++] = '\0';
	}	
}

///////////////////////////////////////////////////////
// #	FREE ALL NODES FROM FIRST
void	free_all(t_list **first_list)
{	
	t_list	*current_list;
	t_list	*temp_list;

	current_list = *first_list;
	while (current_list != NULL)
	{
		temp_list = current_list->next;
		free(current_list);
		current_list = temp_list;
	}
	*first_list = NULL;
}

///////////////////////////////////////////////////////
// #	RETURN SIZE OF NEXT \N		+1 if \n found
int	is_there_n(t_list *node)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (node->buff[i] == '\0')
			return (-i);
		if (node->buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-i);
}

///////////////////////////////////////////////////////
// #	RETURN FULL SIZE + CREATE ALL LIST
int	rtrn_size(t_list *first_list, int fd)
{
	t_list	*current_list;
	int		size;

	current_list = first_list;
	size = 0;
	while (is_there_n(current_list) <= 0)
	{
		size += -is_there_n(current_list);
		current_list = ini_node(current_list);
		if (!current_list)
			return (-1);
		if (read(fd, current_list->buff, BUFFER_SIZE) <= 0)
			break ;
	}
	if (size == 0 && is_there_n(current_list) == 0)
		return (-1);
	if (is_there_n(current_list) > 0)
		size += is_there_n(current_list);
	return (size);
}
