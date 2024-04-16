/* Software License Agreement (BSD License)
*
* Copyright (c) 2014, Robotiq, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
* disclaimer in the documentation and/or other materials provided
* with the distribution.
* * Neither the name of Robotiq, Inc. nor the names of its
* contributors may be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* Copyright (c) 2014, Robotiq, Inc
*/

/*
 *  \file main.c
 *  \date June 18, 2014
 *  \author Jonathan Savoie <jonathan.savoie@robotic.com>
 *  \maintener Nicolas Lauzier <nicolas@robotiq.com>
 */

#include "rq_sensor_com.h"
#include "rq_sensor_state.h"
#include "rq_int.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "Thread/rq_thread.h"

#include <lcm/lcm-cpp.hpp>
#include "ft_300s/ft_reading_t.hpp"

using ft_300s::ft_reading_t;

const char* kLcmSensorDataChannel = "FT300S_SENSOR_DATA";

/**
 * \fn static void decode_message_and_do(char *buff)
 * \brief Decode the message received and execute the operation.
 * Accepted string 	: GET PYE
 * 					: GET FMW
 * 					: GET SNU
 * 					: SET ZRO
 * No other message will be accepted
 * \param *buff, String to decode and execute
 */
/*static void decode_message_and_do(UINT_8 *buff){
	if(buff == NULL || strlen(buff) < 7){
		return;
	}
	UINT_8 get_or_set[3];
	strncpy(get_or_set, &buff[0], 3);
	if(strstr(get_or_set, "GET")){
		UINT_8 nom_get_var[4];
		strncpy(nom_get_var, &buff[4], strlen(buff) -3);
		UINT_8 buffer[512];
		rq_state_get_command(nom_get_var, buffer);
		//
		//  Here comes the code to resend the high level data.
		//
	}
	else if (strstr(buff, "SET ZRO")){
		rq_set_zero();
	}
	//
	// Here comes the code to empty the string(buff).
	//
}*/

/**
 * \fn static void wait_for_other_connection()
 * \brief Function who wait for another connection
 */
static void wait_for_other_connection(){
	INT_8 ret;
	struct timespec tim;
	tim.tv_sec = 1;
	tim.tv_nsec = 0L;

	while(1){
		nanosleep(&tim, (struct timespec *)NULL);
		ret = rq_sensor_state();
		if(ret == 0){
			break;
		}
	}
}

 int main(){
	 //IF can't connect with the sensor wait for another connection
	INT_8 ret = rq_sensor_state();
	if(ret == -1){
		wait_for_other_connection();
	}

	//Read high-level informations
	ret = rq_sensor_state();
	if(ret == -1){
		wait_for_other_connection();
	}

	//Initialize connection with the client
	ret = rq_sensor_state();
	if(ret == -1){
		wait_for_other_connection();
	}

	lcm::LCM lcm_;
	assert(lcm_.good());
	ft_reading_t ft_reading_;

	// Zero the sensor
	rq_set_zero();
 	while(1){
 	 		ret = rq_sensor_state();
 		if(ret == -1){
 			wait_for_other_connection();
 		}
 		if(rq_sensor_get_current_state() == RQ_STATE_RUN){
			ft_reading_.fx = rq_state_get_received_data(0);
			ft_reading_.fy = rq_state_get_received_data(1);
			ft_reading_.fz = rq_state_get_received_data(2);
			ft_reading_.tx = rq_state_get_received_data(3);
			ft_reading_.ty = rq_state_get_received_data(4);
			ft_reading_.tz = rq_state_get_received_data(5);
			ft_reading_.timestamp = (int64_t)time(NULL);
			lcm_.publish(kLcmSensorDataChannel, &ft_reading_);
 		}
 	}
 	return 0;
 }
