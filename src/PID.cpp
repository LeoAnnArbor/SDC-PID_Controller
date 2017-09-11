#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	PID::Kp = Kp;
    PID::Ki = Ki;
    PID::Kd = Kd;
    p_error = d_error = i_error = 0.0;
    step  = 1;
}

void PID::UpdateError(double cte) {
	if (step == 1) {
        p_error = cte;
    }
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
    step++;

}

double PID::TotalError() {
}

