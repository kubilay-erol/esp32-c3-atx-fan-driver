
#pragma once
#include <cstdint>

constexpr uint64_t num = 3;

class Time {

public:
    uint64_t reference[num];

    uint64_t get_timer() {
    
        *(reinterpret_cast<volatile uint32_t*>(0x60023004)) = (1 << 30); //write one to bit 30 to prepare low and high

   
        while ((*(reinterpret_cast<volatile uint32_t*>(0x60023004)) & (1 << 29)) == 0) { //check if bit 29 is flipped to 1 so data is ready
        
        }

    
        uint32_t low = *(reinterpret_cast<volatile uint32_t*>(0x60023044)); //low
        uint32_t high = *(reinterpret_cast<volatile uint32_t*>(0x60023040)); //high

    
        uint64_t ticks = (static_cast<uint64_t>(high) << 32) | low;

        return ticks;
    
    }

    uint64_t get_seconds(uint64_t micsec) {
        return micsec/1'000'000;
    }

    void set_ref(uint64_t n) {
        reference[n] = get_timer();
    }      

    uint64_t get_time(uint64_t n) {
        return (get_timer() - reference[n]);
    }

    bool is_delay_complete(uint64_t delay_seconds, uint64_t n) {

        if (get_time(n) >= delay_seconds) {
            return true; 
        }
        return false;
}
};





   
