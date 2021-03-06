/*
 * Author: Gregory Haynes 	<greg@greghaynes.net>
 *
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2010, Gregory Haynes, Spencer Krum
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef RESPONSE_H
#define RESPONSE_H

#include "state.h"

struct response_controller_t {
	float state_setpoint[AXIS_CNT]; // Desired state
	float state_dt_setpoint[AXIS_CNT]; // Desired state dt
};

void response_start(void);
struct response_controller_t *response_controller_get(void);

void response_off(void);
void response_on(void);
void response_reset(void);

void response_set_p_gain(int axis, float value);
void response_set_d_gain(int axis, float value);
void response_set_i_gain(int axis, float value);
float response_get_p_gain(int axis);
float response_get_d_gain(int axis);
float response_get_i_gain(int axis);

#endif
