#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

class LightController {
    public:
        virtual void initialize() {};
        virtual void on_input_switch_change(bool enable) {};
        virtual const char* get_description() { return ""; };
};

#endif