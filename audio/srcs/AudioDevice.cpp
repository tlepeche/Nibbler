/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioDevice.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:44:10 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/30 14:34:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AudioDevice.hpp"
#include <iostream>

AudioDevice::AudioDevice()
{
}

AudioDevice::~AudioDevice()
{
}

AudioDevice::AudioDevice(AudioDevice const & src)
{
	*this = src;
}

AudioDevice	&AudioDevice::operator=(AudioDevice const & src)
{
	if (this != &src)
		_food_sound = src.getFoodSound();
	return *this;
}

Mix_Chunk	*AudioDevice::getFoodSound() const { return _food_sound; }

bool AudioDevice::init()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 8089) == -1)
		return (false);
	this->_food_sound = Mix_LoadWAV("audio/blop.wav");
	if (this->_food_sound == NULL)
		return (false);
	return (true);
}

bool AudioDevice::playSound()
{
	if (Mix_PlayChannel(-1, this->_food_sound, 0) == -1)
		return (false);
	return (true);
}

void AudioDevice::close()
{
	Mix_FreeChunk(this->_food_sound);
	this->_food_sound = NULL;
	Mix_CloseAudio();
}
