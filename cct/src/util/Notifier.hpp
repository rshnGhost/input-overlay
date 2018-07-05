/**
 * Created by univrsal on 30.05.2018.
 * This file is part of input-overlay which is licensed
 * under the MOZILLA PUBLIC LICENSE 2.0 - mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#pragma once

#include "../util/SDL_helper.hpp"
#include <vector>
#include <memory.h>
#include <algorithm>

#define MESSAGE_INFO  0
#define MESSAGE_ERROR 1

#define MESSAGE_TIMEOUT 4000

class SDL_helper;


struct Message
{
public:
	Message(uint8_t type, std::string msg)
	{
		m_message = msg;
		m_type = type;
		m_time_stamp = SDL_GetTicks();
	}

	~Message()
	{
		m_message.clear();
		m_type = 0;
		m_time_stamp = 0;
	}

	std::string m_message;
	uint8_t m_type;
	uint32_t m_time_stamp;
};

class Notifier
{
public:
	Notifier(SDL_helper * h)
	{
		m_messages = std::vector<std::unique_ptr<Message>>();
		m_helper = h;
		m_dim = { 0, 0};
	}

	~Notifier()
	{
		m_messages.clear();
		m_helper = nullptr;
		m_dim = { 0, 0 };
	}

	void add_msg(uint8_t type, std::string msg);

	void draw(void);
private:
	std::string m_last_message = "";
	std::vector<std::unique_ptr<Message>> m_messages;
	SDL_helper * m_helper;
	SDL_Point m_dim;
};