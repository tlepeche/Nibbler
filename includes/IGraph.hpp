/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGame.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 16:57:55 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/01 17:18:25 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IGRAPH_HPP
# define IGRAPH_HPP

class IGraph
{
	public:
		
		virtual void	Init(void) = 0;		//init graphic library
		virtual void	Display(void) = 0;	//display
		virtual void	EndGame(void) = 0;	//delete all instances of the library
		virtual void	~IGame() {}
};

#endif
