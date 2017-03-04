/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 18:31:27 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/04 18:59:58 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

NibblerException::NibblerException(const char *msg)
{
	std::stringstream	ss;

	ss << msg;
	this->_error = ss.str();
}

NibblerException::NibblerException(const std::string &msg) : _error(msg)
{
}

NibblerException::NibblerException(NibblerException const &rhs)
{
	_error = rhs._error;
}

const char *NibblerException::what(void) const throw()
{
	return (this->_error.c_str());
}

NibblerException	&NibblerException::operator=(NibblerException const &rhs)
{
	_error = rhs._error;
	return (*this);
}
