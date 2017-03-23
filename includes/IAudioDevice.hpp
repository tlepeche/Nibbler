/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IAudioDevice.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:49:13 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 18:31:40 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IAUDIO_DEVICE_HPP
# define FT_IAUDIO_DEVICE_HPP

class IAudioDevice
{
	public:
		virtual			~IAudioDevice() {};
		virtual bool	init() = 0;
		virtual bool	playSound() = 0;
		virtual void	close(void) = 0;
};

#endif
