/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:28:55 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/03 18:49:25 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXCEPTION_HPP
# define FT_EXCEPTION_HPP

#include <exception>
#include <string>
#include <sstream>

class NibblerException : public std::exception
{
	public:
		NibblerException(const char *msg);
		NibblerException(const std::string &msg);
		virtual const char	*what(void) const throw();
		NibblerException(NibblerException const &rhs);
		virtual ~NibblerException() throw () {};
		std::string			 getError(void) const;
	private:
		std::string			_error;
		NibblerException	&operator=(NibblerException const &rhs);
		NibblerException(void);
};
#endif
