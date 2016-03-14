/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 11:05:04 by nchrupal          #+#    #+#             */
/*   Updated: 2016/02/05 11:06:15 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_OPTS_H
# define GET_OPTS_H

typedef unsigned t_flags;

/*
** s = chaine ou recuperer les arguments
** opts = options sous forme d'un tableau "cdui" options -c -d -u -i
** val_opts = valeur des arguments dans le tableau opts. Les valeurs DOIVENT
**   etre des mutilpes de 2 pour faire un OU bit a bit. Doit etre strictement
**   superieur a 0.
** flags = variable qui sera retournee avec les flags presents dans s.
**   La variable flags DOIT etre initialisee avant appel !
** => retourne la premiere occurence de la chaine qui n'est pas presente dans s
*/

char	*get_opts(char *s, char *opts, t_flags *val_opts, t_flags *flags);

#endif
