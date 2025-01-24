/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2025/01/24 16:30:12 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Initialise la structure principale `t_shell` et prépare l'environnement.
 * 
 * Cette fonction configure les valeurs initiales des attributs de la structure
 * `t_shell`, alloue l'environnement, initialise l'historique et configure le terminal.
 * En cas d'erreur, elle quitte le programme avec un message approprié.
 * 
 * @param mini : Structure principale contenant les données de l'exécution.
 * @param env : Tableau contenant les variables d'environnement.
 * @param histo : Pointeur vers l'identifiant de l'historique.
 * @param term : Structure pour la configuration du terminal.
 */
static void	startshell(t_shell *mini, char **env, int *histo,
		struct termios *term)
{
	mini->rtn = 0;
	mini->exit = 0;
	mini->pid = 0;
	mini->ncmd = 0;
	mini->in = -1;
	mini->out = -1;
	mini->cmd = NULL;
	mini->tab = NULL;
	mini->args = NULL;
	mini->paths = NULL;
	mini->line = NULL;
	mini->htab = NULL;
	mini->token = NULL;
	mini->o_in = dup(STDIN_FILENO);
	mini->o_out = dup(STDOUT_FILENO);

	// Allocation des variables d'environnement
	alloc_env(mini, env);
	mini->home = ft_strdup(getenv("HOME"));

	// Création ou initialisation de l'historique
	if (!create_history(histo))
		ft_exit_plus(mini, "Fail to create/initiate history\n", 1);

	// Configuration des attributs du terminal
	if (tcgetattr(STDIN_FILENO, term) == -1)
		ft_exit_plus(mini, "Fail to get terminal attributes\n", 1);

	// Désactivation des signaux readline par défaut
	rl_catch_signals = 0;
}

/**
 * @brief Vérifie les arguments du programme et configure les signaux.
 * 
 * Cette fonction vérifie que le programme est lancé sans arguments et initialise
 * la gestion des signaux. Si des arguments sont fournis, elle affiche un message
 * d'erreur et quitte le programme.
 * 
 * @param ac : Nombre d'arguments passés au programme.
 * @param av : Tableau des arguments passés au programme.
 */
static void	args(int ac, char **av)
{
	(void)av;
	g_sig = 0; // Initialisation des signaux globaux
	define_signals(); // Configuration des gestionnaires de signaux

	// Vérifie que le programme est lancé sans arguments
	if (ac > 1)
	{
		ft_putstr_fd("Launch without any arguments\n", STDERR_FILENO);
		exit(1);
	}
}

/**
 * @brief Fonction principale du programme Minishell.
 * 
 * Cette fonction gère l'initialisation, la boucle principale du shell et la
 * libération des ressources avant la sortie.
 * 
 * @param ac : Nombre d'arguments passés au programme.
 * @param av : Tableau des arguments passés au programme.
 * @param env : Tableau contenant les variables d'environnement.
 * @return Retourne 0 en cas de succès.
 */
int	main(int ac, char **av, char **env)
{
	t_shell			mini;
	struct termios	term;
	int				histo;

	// Vérification des arguments et initialisation des signaux
	args(ac, av);

	// Initialisation du shell et des ressources nécessaires
	startshell(&mini, env, &histo, &term);

	// Boucle principale du shell
	while (1)
	{
		// Recharge les attributs du terminal avant chaque itération
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
			ft_exit_plus(&mini, "Fail to reload minishell attributes\n", 1);

		// Affiche le prompt et récupère la ligne de commande de l'utilisateur
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		if (!mini.line) // Gestion du cas où readline retourne NULL (Ctrl+D)
			break;

		if (mini.line[0]) // Si l'utilisateur a entré une commande
		{
			add_histo(mini.line, histo);
			parse_input(&mini);
			minishell(&mini);	// Exécution de la commande
		}

		mini_free(&mini); // Libération des ressources allouées pour cette itération
	}

	// Libération des ressources globales et sortie propre
	ft_exit_all(&mini, histo, mini.rtn);
	return (0);
}
