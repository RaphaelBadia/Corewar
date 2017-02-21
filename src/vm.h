/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:09:05 by jye               #+#    #+#             */
/*   Updated: 2017/02/21 18:49:12 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "op.h"
# define ERROR "Error"
/*
** r1 == given out as player_id at launch
** MEM_SIZE / player == offset between each player
** if process has not live in CYCLE_TO_DIE, process will be killed
** if process has live == NBR_LIVE -> CYCLE_TO_DIE will decrease by CYCLE_DELTA
** game over when all process are dead
** Player X (champion_name) won where X is the player’s number and champion_name is its name.
** A process shows that player X (champion_name) is alive
*/
typedef struct	s_statu
{
	int		nb_player;
	int
}				t_statu

typedef struct	s_process
{
	int		r[16];
	int		pc;
	int		carry;
}				t_process;

#endif
