/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:28:55 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/17 19:09:09 by tlepeche         ###   ########.fr       */
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
		NibblerException(NibblerException const &rhs);

		virtual				 ~NibblerException() throw () {};
		virtual const char	*what(void) const throw();
		NibblerException	&operator=(NibblerException const &rhs);
		std::string			getError() const;

	protected:
		std::string			_error;

	private:
		NibblerException(void);
};

#endif
