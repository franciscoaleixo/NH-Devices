#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/portmacro.h"

#include "simpleswitch.h"
#include "lightcontroller.h"


const static int DEBOUNCE_TIME_MS = 200;
static QueueHandle_t interruptQueue;
static unsigned int current_queue_process = 0;

/**
 * Listens to given gpio_nr and on input change, applies a simple debounce algorithm before executing program_block.
*/
void SimpleSwitchInputMode::initialize()
{
    if(interruptQueue != NULL) {
        printf("SimpleSwitch Input Mode has already been initialized, returning...");
        return;
    }
    gpio_num_t gpio_nr = args->gpio_nr;
    // Setup GPIO for input with pulldown
    gpio_set_direction(gpio_nr, GPIO_MODE_INPUT);
    gpio_set_pull_mode(gpio_nr, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(gpio_nr, GPIO_INTR_ANYEDGE);

    // Setup our debounce task
    interruptQueue = xQueueCreate(1, sizeof(int));
    xTaskCreate(simple_switch_control_task, "Simple_Switch_Control_Task", 2048, args, tskIDLE_PRIORITY, NULL);

    // Finally link GPIO interrupt service to our debounce task 
    gpio_install_isr_service(0);
    gpio_isr_handler_add(gpio_nr, simple_switch_interrupt_handler, NULL);
}

const char* SimpleSwitchInputMode::get_description() {
    return "Simple switch";
};

static inline void IRAM_ATTR simple_switch_interrupt_handler(void *args)
{
    int process = ++current_queue_process;
    xQueueOverwriteFromISR(interruptQueue, &process, NULL);
}

static inline void simple_switch_control_task(void *params)
{
    simple_switch_args args = *static_cast<simple_switch_args *>(params);
    gpio_num_t gpio = (gpio_num_t) args.gpio_nr;
    
    int process = 0;
    while (true)
    {
        if (xQueueReceive(interruptQueue, &process, NULL))
        {
            int initial_state = gpio_get_level(gpio);
            vTaskDelay(DEBOUNCE_TIME_MS / portTICK_PERIOD_MS);
            int current_state = gpio_get_level(gpio);
            //printf("Simple switch - Initial state: %d, Current state: %d \n", initial_state, current_state);

            if(process == current_queue_process && initial_state == current_state) {
                args.on_input_switch_change(current_state == 1);
            }
        }
    }
}