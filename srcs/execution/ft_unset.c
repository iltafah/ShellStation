/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlimouni <hlimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:50:57 by hlimouni          #+#    #+#             */
/*   Updated: 2021/12/16 18:21:28 by hlimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

static int	invalid_option_err(char *arg)
{
	ft_putstr_fd("minishell: unset: ", 2);
	write(2, arg, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("unset: usage: unset [-f] [-v] [name ...]\n", 2);
	g_vars.last_err_num = 2;
	return (0);
}

static int	invalid_identifier_err(char *arg)
{
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_vars.last_err_num = 1;
	return (0);
}

static int	is_argvalid(char *arg)
{
	int	i;
	int	namelen;

	if (*arg == '-')
		return (invalid_option_err(arg));
	if (ft_isdigit(*arg))
		return (invalid_identifier_err(arg));
	namelen = ft_strlen(arg);
	i = 0;
	while (i < namelen && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (i < namelen)
		return (invalid_identifier_err(arg));
	return (namelen);
}

void	ft_unset(t_ast *data)
{
	int	j_args;
	int	j_env;

	j_args = 1;
	while (j_args < data->ARGC)
	{
		if (is_argvalid(data->ARGV[j_args]))
		{
			j_env = 0;
			// printf("used size %d\n", g_vars.env_table.name.used_size);
			while (j_env < g_vars.env_table.name.used_size)
			{
				if (!ft_strcmp(data->ARGV[j_args],
						g_vars.env_table.name.elements[j_env]))
				{
					// printf("found path\n");
					delete_element_at_index(&g_vars.env_table.name, j_env);
					delete_element_at_index(&g_vars.env_table.value, j_env);
					return ;
				}
				j_env++;
			}
			// printf("%d\n", j_env);
			// printf("what about here\n");
		}
		j_args++;
	}
}
