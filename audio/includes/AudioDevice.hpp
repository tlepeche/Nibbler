/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioDevice.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:44:40 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/30 14:34:05 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AUDIO_DEVICE_HPP
# define FT_AUDIO_DEVICE_HPP

#include "IAudioDevice.hpp"
#include <SDL2/SDL_mixer.h>

class AudioDevice : public IAudioDevice
{
	public:
		AudioDevice();
		~AudioDevice();
		AudioDevice(AudioDevice const & src);
		AudioDevice	&operator=(const AudioDevice & src);
		bool		init();
		bool		playSound();
		void		close();
		Mix_Chunk	*getFoodSound() const;

	private:
		Mix_Chunk	*_food_sound;
};


extern "C"
{
	IAudioDevice	*create_audiodevice()
	{
		return (new AudioDevice());
	}
}

#endif
