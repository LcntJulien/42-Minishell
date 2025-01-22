/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/22 12:27:54 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	alloc_htab(t_shell *mini, int nb)
{
	int	i;

	i = -1;
	mini->htab = malloc(sizeof(int *) * nb);
	if (!mini->htab)
		err_manager(mini, NULL, 3);
	while (++i < nb)
	{
		mini->htab[i] = malloc(sizeof(int) * 2);
		if (!mini->htab[i])
			err_manager(mini, NULL, 3);
	}
	i = -1;
	while (++i < nb)
		if (pipe(mini->htab[i]) < 0)
			err_manager(mini, NULL, 1);
}

char	*hrdc_convert(t_shell *mini, char *s)
{
	char	*cur;
	char	*tmp;
	char	*iter;
	int		i;

	cur = NULL;
	tmp = NULL;
	iter = NULL;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$')
		{
			cur = get_vname(s, i);
			iter = get_nvar(mini, cur);
			tmp = rewrite(mini, s, cur, i);
			free(s);
			s = tmp;
			i += (ft_strlen(iter) - 1);
			free2(cur, iter);
		}
	}
	return (s);
}

void	hrdc_filler(t_shell *mini, t_token *cur, int i)
{
	char	*tmp;

	tmp = NULL;
	signals_hrdc();
	if (cur && cur->type == HEREDOC && cur->next)
		cur = cur->next;
	while (1)
	{
		tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		if (!tmp || (tmp && tmp[0] && ft_strncmp(tmp, cur->s,
					ft_strlen(cur->s)) == 0))
			break ;
		if (contain_var(tmp))
			tmp = hrdc_convert(mini, tmp);
		ft_putendl_fd(tmp, mini->htab[i][1]);
		free(tmp);
		tmp = NULL;
	}
	if (tmp)
		free(tmp);
	exit(0);
}

void	hrdc_manager(t_shell *mini)
{
	t_token	*cp;
	pid_t	pid;
	int		i;

	cp = mini->token;
	i = -1;
	replace_sig();
	if (nb_hrdc(mini))
		alloc_htab(mini, nb_hrdc(mini));
	while (nb_hrdc(mini) && ++i < nb_hrdc(mini))
	{
		cp = next_hrdc(cp, i);
		pid = fork();
		if (pid == -1)
			err_manager(mini, NULL, 2);
		else if (pid == 0)
			hrdc_filler(mini, cp, i);
		waitpid(pid, &mini->rtn, 0);
		mini->rtn = WEXITSTATUS(mini->rtn);
		if (mini->rtn == 1)
			mini_free(mini);
	}
	if (mini->ncmd == 1)
		define_signals();
}

void	close_hrdc(t_shell *mini, int cur, int sw)
{
	int	i;

	i = -1;
	if (!nb_hrdc(mini))
		return ;
	if (sw)
	{
		while (++i < nb_hrdc(mini))
		{
			if (i != get_htab(mini, cur))
				close(mini->htab[i][0]);
			close(mini->htab[i][1]);
		}
	}
	else
	{
		while (++i < nb_hrdc(mini))
		{
			close(mini->htab[i][0]);
			close(mini->htab[i][1]);
		}
	}
}
