/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agallon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:06:26 by agallon           #+#    #+#             */
/*   Updated: 2023/11/23 20:06:28 by agallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>	// read close
# include <stdio.h>		// printf malloc free
# include <stdlib.h> 	// malloc free
# include <fcntl.h>		// open

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

///////////////////////////////////////////////////////
// # 	STRUCT
typedef struct s_list
{
	char			buff[BUFFER_SIZE];
	struct s_list	*next;
}					t_list;

t_list	*ini_node(t_list *first_list);
void	clean_buff(char *buff, int sw);
void	free_all(t_list **first_list);
void	f_copy_rest(t_list *last_list);
char	*f_rtrn_2(t_list *first_list, char *rtrn, int size);
char	*get_next_line(int fd);
char	*f_rtrn_1(t_list *first_list, int fd);
int		is_there_n(t_list *node);
int		rtrn_size(t_list *first_list, int fd);

#endif
