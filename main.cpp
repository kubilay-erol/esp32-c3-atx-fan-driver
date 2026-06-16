#include <time.hpp>
#include <digioreg.hpp>
#include <memalloc.hpp>
#include <cstdint>
#include <pwm.hpp>



extern "C" void app_main(void) {

    SoftwarePWM* ptr = SoftwarePWM::create_PWM(GPIO2_MODE_REG, 40, 50000, 0);

    ptr->on();
        


    
    
}
