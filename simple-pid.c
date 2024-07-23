#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define DEFAULT_Kp (1.1)
#define DEFAULT_Ki (0.1)
#define DEFAULT_Kd (0.01)
#define SETPOINT   (50)

// Define a PID structure
typedef struct {
    double Kp;   // Proportional gain
    double Ki;   // Integral gain
    double Kd;   // Derivative gain
    double previous_error; // Previous error
    double integral;       // Integral of the error
    double setpoint;       // Desired setpoint
} PIDController;

// Initialize the PID controller
void PID_Init(PIDController* pid, double Kp, double Ki, double Kd, double setpoint) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->previous_error = 0;
    pid->integral = 0;
    pid->setpoint = setpoint;
}

// Compute the PID output
double PID_Compute(PIDController* pid, double measured_value) {
    // Calculate error
    double error = pid->setpoint - measured_value;

    // Proportional term
    double Pout = pid->Kp * error;

    // Integral term
    pid->integral += error;
    double Iout = pid->Ki * pid->integral;

    // Derivative term
    double derivative = error - pid->previous_error;
    double Dout = pid->Kd * derivative;

    // Calculate total output
    double output = Pout + Iout + Dout;

    // Save the current error for the next iteration
    pid->previous_error = error;

    return output;
}

// Simulate a process to control
double simulate_process(double input) {
    // Simple simulation of a process
    return input * 0.8 + ((double)rand() / RAND_MAX - 0.5) * 0.1; // Example process model
}

// Auto-tuning function (Ziegler-Nichols method)
void PID_AutoTune(PIDController* pid, double measured_value) {
    double Ku = 1.0;  // Initial guess for critical gain
    double Kp, Ki, Kd;
    double previous_output = 0;
    int oscillation_detected = 0;
    double T = 0.1; // Initial guess for period of oscillation
    double time = 0;

    // Apply a relay feedback to find Ku and Tu
    while (!oscillation_detected && time < 10.0) {
        double control_signal = Ku * (measured_value > 0 ? 1 : -1); // Relay feedback
        measured_value = simulate_process(control_signal);
        time += T;

        // Check for oscillations
        if (fabs(measured_value - previous_output) > 1.0) { // Simple oscillation detection
            oscillation_detected = 1;
        }
        previous_output = measured_value;
    }

    if (oscillation_detected) {
        double Tu = time; // Period of oscillation

        // Apply Ziegler-Nichols tuning rules
        Kp = 0.6 * Ku;
        Ki = 2 * Kp / Tu;
        Kd = Kp * Tu / 8;

        pid->Kp = Kp;
        pid->Ki = Ki;
        pid->Kd = Kd;
    }
    else {
        // If oscillation not detected, use default values
        pid->Kp = DEFAULT_Kp;
        pid->Ki = DEFAULT_Ki;
        pid->Kd = DEFAULT_Kd;
    }
}

int main() {
    srand(time(0));

    PIDController pid;
    PID_Init(&pid, DEFAULT_Kp, DEFAULT_Ki, DEFAULT_Kd, SETPOINT); // Example initial gains and setpoint

    // Auto-tune the PID controller
    double initial_measurement = simulate_process(0);
    PID_AutoTune(&pid, initial_measurement);

    printf("Auto-tuned PID parameters: Kp = %f, Ki = %f, Kd = %f\n", pid.Kp, pid.Ki, pid.Kd);

    double process_value = 0;

    for (int i = 0; i < 1000; i++) 
    {
        double control_signal = PID_Compute(&pid, process_value);
        process_value = simulate_process(control_signal);

        printf("TARGET: %d \tTime: %d \tProcess Value: %.2f \tControl Signal: %.2f\r", (int)pid.setpoint, i, process_value, control_signal);

        if ((int)process_value == pid.setpoint)
        {
            i = 0;
            printf("\n");
            pid.setpoint = rand() % 100;
        }

        Sleep(50);
    }

    return 0;
}
