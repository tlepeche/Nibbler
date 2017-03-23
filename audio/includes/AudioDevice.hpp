/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioDevice.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:44:40 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 18:32:06 by tiboitel         ###   ########.fr       */
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
		bool init();
		bool playSound();
		void close();
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
