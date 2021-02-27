// Main program to test UART communication from BBB to VESC
// Last modified on 3/7/2017 by: Ryan Owens
#include <stdio.h>
#include <string.h>
#include "bldc_interface.h"
#include "comm_uart.h"
#include <unistd.h> // for usleep
#include <time.h>

void bldc_val_received(mc_values *val) {
    FILE *logfile;
    time_t now;

    now = time(0);
    logfile = fopen("bldc_log.csv", "a");

    printf("\e[1;1H\e[2J");
    printf("Timestamp:     %ld\r\n", now);
    printf("Input voltage: %.2f V\r\n", val->v_in);
    printf("Temp:          %.2f degC\r\n", val->temp_mos);
    printf("Current motor: %.2f A\r\n", val->current_motor);
    printf("Current in:    %.2f A\r\n", val->current_in);
    printf("RPM:           %.1f RPM\r\n", val->rpm);
    printf("Duty cycle:    %.1f %%\r\n", val->duty_now * 100.0);
    printf("Ah Drawn:      %.4f Ah\r\n", val->amp_hours);
    printf("Ah Regen:      %.4f Ah\r\n", val->amp_hours_charged);
    printf("Wh Drawn:      %.4f Wh\r\n", val->watt_hours);
    printf("Wh Regen:      %.4f Wh\r\n", val->watt_hours_charged);
    printf("Tacho:         %i counts\r\n", val->tachometer);
    printf("Tacho ABS:     %i counts\r\n", val->tachometer_abs);
    printf("Fault Code:    %s\r\n", bldc_interface_fault_to_string(val->fault_code));

    fprintf(logfile, "%ld,%.2f,%.2f,%.2f,%.2f,%.1f,%.1f,%.4f,%.4f,%.4f,%.4f,%i,%i\r\n",
        now,
        val->v_in,
        val->temp_mos,
        val->current_motor,
        val->current_in,
        val->rpm,
        val->duty_now * 100.0,
        val->amp_hours,
        val->amp_hours_charged,
        val->watt_hours,
        val->watt_hours_charged,
        val->tachometer,
        val->tachometer_abs);

    fclose(logfile);
}

int main(void) {

    // For the serial interface
    comm_uart_init("/dev/ttyACM0");
    // Give bldc interface a callback function to handle received values
    bldc_interface_set_rx_value_func(bldc_val_received);

    while(1) {
        bldc_interface_get_values();
        usleep(10000);
        receive_packet();
        usleep(1000000);
    }
}
