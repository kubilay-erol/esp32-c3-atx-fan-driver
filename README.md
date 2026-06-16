# esp32-c3-atx-fan-driver

A custom, zero-overhead, bare-metal C++20 driver designed to control and monitor standard 4-pin ATX computer fans using the ESP32-C3 (RISC-V) architecture.

This project bypasses standard OS layers, operating system schedulers, and generic vendor frameworks (like ESP-IDF or Arduino) to manipulate hardware registers directly via low-level pointer dereferencing.

## Features

* **Modern C++20 Compliance:** Utilizes strict type safety, prevents `volatile` deprecation errors common in newer toolchains, and implements explicit resource management.
* **Software PWM Control:** Manages fan speed dynamically by outputting a controlled duty cycle via dedicated GPIO register manipulation.
* **Tachometer RPM Monitoring:** Reads the open-drain tachometer line to measure microsecond deltas between magnetic Hall-effect pulses for precise speed verification.
* **Ultra-Low Footprint:** Runs directly on naked silicon, completely eliminating heap fragmentation risks and overhead.

## Physical Interface & Wiring

To protect the ESP32-C3's 3.3V logic from the fan's 12V operating voltage, the hardware must be isolated with a shared common ground configuration.

### Hardware Connection Logic
* **Fan Pin 1 (Black):** Connected to BOTH ESP32-C3 GND and the 12V DC power supply Negative (-) terminal.
* **Fan Pin 2 (Yellow/Red):** Connected ONLY to the 12V DC power supply Positive (+) terminal. (Do not connect to the MCU).
* **Fan Pin 3 (Green/Yellow):** Connected to GPIO1 (Configured as an Input to read tachometer sensor pulses).
* **Fan Pin 4 (Blue):** Connected to GPIO2 (Configured as an Output to deliver the PWM speed control signal).

## System Architecture

The core driver engine operates entirely inside a lightweight loop structure that continuously evaluates hardware registers:

1. **Initialization:** Registers the memory offsets for the GPIO enable registers, configuration modes, and input/output data lanes using a custom hardware abstraction layer (`DigIOReg`).
2. **Edge Detection:** The control loop tracks bit changes on the GPIO data register (`GPIO_DATA_REG`). When a transition condition is met, it evaluates the system timestamps.
3. **Duty Cycle Updates:** The driver utilizes a custom `SoftwarePWM` instance to step the duty cycle value up or down based on system events, pushing the exact clock state directly into the hardware registers.

## Building and Flashing

This project is configured for execution via PlatformIO using the `espressif32` development platform with a native bare-metal configuration.

To compile and upload the firmware to your development board:
