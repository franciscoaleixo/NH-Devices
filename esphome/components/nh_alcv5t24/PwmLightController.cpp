#include "PwmLightController.h"
#include <stdio.h>
#include "driver/ledc.h"
#include "hal/ledc_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

/**
 * PWM Light Controller for just one light, so no RGB support.
*/
void PwmLightController::initialize() 
{
    printf("Initializing PWM light controller\n");

    // To check if it suports the duty res / freq combination:
    // div = (BASE_FREQ << 8) / (LED_FREQ * 2^(DUTY_RES)) 
    // div > 255 && div <= 262143
    // Example: 
    //   For RC_FAST_CLK (20MHz), LED_FREQ=30KHz, DUTY_RES=9bits
    //   div = 5120000000 / (30000 * 2^(9)) = 333.33
    //   div = 333.33, which is bigger than 255, so it's supported.
    ledc_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,      // Timer mode
        .duty_resolution = LEDC_TIMER_9_BIT,    // Resolution of PWM duty
        .timer_num = LEDC_TIMER_0,              // Timer index
        .freq_hz = 30000,                       // Frequency of PWM signal
        .clk_cfg = LEDC_USE_RC_FAST_CLK,        // Source clock
    };
    ledc_channel = {
        .gpio_num   = gpio_nr,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_0,
        .intr_type  = LEDC_INTR_DISABLE,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = 0,
        .hpoint     = 0,
        .flags      = { .output_invert = 0}
    };

    ledc_timer_config(&ledc_conf);
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);

    //ledc_cbs_t callbacks = {
    //    .fade_cb = cb_ledc_fade_end_event
    //};
    //QueueHandle_t mutex_sem = xSemaphoreCreateMutex();
    //ledc_cb_register(ledc_channel.speed_mode, ledc_channel.channel, &callbacks, (void *) mutex_sem)

}

void PwmLightController::change_state(bool enable, float turn_on_brightness) 
{
    ledc_fade_stop(ledc_channel.speed_mode, ledc_channel.channel);
    this->currentState = enable;
    if(enable){
        printf("PWM Light Controller - Turning ON lights\n");
        ledc_set_fade_with_time(ledc_channel.speed_mode, ledc_channel.channel, get_adj_duty_cycle(turn_on_brightness), fade_time_ms);
        ledc_fade_start(ledc_channel.speed_mode, ledc_channel.channel, LEDC_FADE_NO_WAIT);
    }
    else {
        printf("PWM Light Controller - Turning OFF lights\n");
        ledc_set_fade_with_time(ledc_channel.speed_mode, ledc_channel.channel, get_adj_duty_cycle(0), fade_time_ms);
        ledc_fade_start(ledc_channel.speed_mode, ledc_channel.channel, LEDC_FADE_NO_WAIT);
    }
}

const char* PwmLightController::get_description() 
{
    return "PWM Light Controller";
}