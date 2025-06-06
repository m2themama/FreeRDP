/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * SDL Client Channels
 *
 * Copyright 2022 Armin Novak <armin.novak@thincast.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <freerdp/config.h>

#include <winpr/assert.h>

#include <freerdp/client/rail.h>
#include <freerdp/client/cliprdr.h>
#include <freerdp/client/disp.h>

#include "sdl_channels.hpp"
#include "sdl_freerdp.hpp"
#include "sdl_disp.hpp"

void sdl_OnChannelConnectedEventHandler(void* context, const ChannelConnectedEventArgs* e)
{
	auto sdl = get_context(context);

	WINPR_ASSERT(sdl);
	WINPR_ASSERT(e);

	if (strcmp(e->name, RAIL_SVC_CHANNEL_NAME) == 0)
	{
	}
	else if (strcmp(e->name, CLIPRDR_SVC_CHANNEL_NAME) == 0)
	{
		auto clip = reinterpret_cast<CliprdrClientContext*>(e->pInterface);
		WINPR_ASSERT(clip);
		sdl->clip.init(clip);
	}
	else if (strcmp(e->name, DISP_DVC_CHANNEL_NAME) == 0)
	{
		auto disp = reinterpret_cast<DispClientContext*>(e->pInterface);
		WINPR_ASSERT(disp);
		(void)sdl->disp.init(disp);
	}
	else
		freerdp_client_OnChannelConnectedEventHandler(context, e);
}

void sdl_OnChannelDisconnectedEventHandler(void* context, const ChannelDisconnectedEventArgs* e)
{
	auto sdl = get_context(context);

	WINPR_ASSERT(sdl);
	WINPR_ASSERT(e);

	// TODO: Set resizeable depending on disp channel and /dynamic-resolution
	if (strcmp(e->name, RAIL_SVC_CHANNEL_NAME) == 0)
	{
	}
	else if (strcmp(e->name, CLIPRDR_SVC_CHANNEL_NAME) == 0)
	{
		auto clip = reinterpret_cast<CliprdrClientContext*>(e->pInterface);
		WINPR_ASSERT(clip);
		(void)sdl->clip.uninit(clip);
		clip->custom = nullptr;
	}
	else if (strcmp(e->name, DISP_DVC_CHANNEL_NAME) == 0)
	{
		auto disp = reinterpret_cast<DispClientContext*>(e->pInterface);
		WINPR_ASSERT(disp);
		(void)sdl->disp.uninit(disp);
	}
	else
		freerdp_client_OnChannelDisconnectedEventHandler(context, e);
}
