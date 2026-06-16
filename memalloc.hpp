

#pragma once 

#include <cstdint>

constexpr uint32_t buffer_size = 20000; //preallocate 20000 bytes compile time

constexpr uint32_t align = 4;



namespace MemoryAllocator {

    alignas(16) uint8_t buffer[buffer_size];
    uint32_t offset = 0; //start from fresh


    void* alloc(uint32_t bytes) { 

        if (offset + bytes > buffer_size) {
            return nullptr;
        }
        
        uint32_t block = 0;

        while(true) {
        
            block = block + align;

            if (block >= bytes) {
                break;
            }
        }


        void* ptr = buffer + offset;

        offset = offset + block;

        return ptr;

    }


    void reset() { 
        offset = 0; } //will reset the pointer


    uint32_t remaining() { 
        return buffer_size - offset; 
    }

};

