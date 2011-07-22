#include "response.h"
#include "../sys/tasks.h"
#include "state.h"
#include "../systick/systick.h"
#include "movement.h"

static struct response_controller_t _rc;
static struct task_t _response_task;

static int _response_is_on;

static float state_error_last[AXIS_CNT] = {0, 0, 0, 0, 0, 0};

#define PID_T_P 0 // Torque (roll, pitch) P gain
#define PID_Z_P 0 // Torque (yaw) P gain
#define PID_T_D 0 // Torque (roll, pitch) D gain
#define PID_Z_D 0 // Torque (yaw) D gain
#define PID_Y_P .2 // Vertical P gain
#define PID_Y_D 0 // Vertical D gain

static float pid_gains_p[4][4] = {
		{ 0,        -PID_T_P, PID_Z_P,  PID_Y_P },
		{ -PID_T_P, 0,        -PID_Z_P, PID_Y_P },
		{ 0,        PID_T_P,  PID_Z_P,  PID_Y_P },
		{ PID_T_P,  0,        -PID_Z_P, PID_Y_P }
};

static float pid_gains_d[4][4] = {
		{ 0,        -PID_T_D, PID_Z_D,  PID_Y_D },
		{ -PID_T_D, 0,        -PID_Z_D, PID_Y_D },
		{ 0,        PID_T_D,  PID_Z_D,  PID_Y_D },
		{ PID_T_D,  0,        -PID_Z_D, PID_Y_D }
};

/* This gets called every CFG_RESPONSE_UPDATE_MSECS */
void response_update(struct task_t *task)
{
	// Ability to turn off response system
	// Safety feature, DO NOT DISABLE!
	if(!_response_is_on)
		return;

	int i;
	struct state_controller_t *sc;
	sc = stateControllerGet();

	// Figure out error
	float state_error[AXIS_CNT];
	stateSubtract(_rc.state_setpoint, sc->inertial_state, state_error);

	float output[4];
	// Multiply P gains
	for(i = 0;i<4;i++)
		output[i] = state_error[AxisRoll]*pid_gains_p[i][0] + state_error[AxisPitch]*pid_gains_p[i][1] + state_error[AxisPitch]*pid_gains_p[i][2] + state_error[AxisY]*pid_gains_p[i][3];

	// Multiply D gains
	for(i = 0;i<4;i++)
		output[i] += state_error[AxisRoll]*pid_gains_d[i][0] + state_error[AxisPitch]*pid_gains_d[i][1] + state_error[AxisPitch]*pid_gains_d[i][2] + state_error[AxisY]*pid_gains_d[i][3];

	// Square outputs to account for motor input -> thrust conversion
	for(i = 0;i<4;i++)
		output[i] *= output[i];

	// output to motors
	motors_set(output);

	// Set current error as last
	stateCopy(state_error, state_error_last);
}

void response_start(void)
{
	int i = 0;

	// Init _rc
	for(i = 0;i < AXIS_CNT;++i) {
		_rc.state_setpoint[i] = 0;
		_rc.state_dt_setpoint[i] = 0;
	}

	// Setup response update task
	_response_task.handler = response_update;
	_response_task.msecs = CFG_RESPONSE_UPDATE_MSECS;
	tasks_add_task(&_response_task);

	response_on();
}

struct response_controller_t *response_controller_get(void)
{
	return &_rc;
}

void response_on(void)
{
	_response_is_on = 1;
}

void response_off(void)
{
	_response_is_on = 0;
}
