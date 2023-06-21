# ChipControl (LTC2943 driver)
This package contains a C implementation for an LTC2943 chip driver. This module can be used to access, monitor, and configure the multicell battery gas gauge LTC2943. 

# Dependencies
The module is tested and configured on:

* cppStandard: gnu++14
* cStandard: c17
* Ubuntu 20.04

# Build Dependencies
Install Linux dependencies:
```
sudo apt install build-essential libssl-dev g++         // C build requirements
```
Install `Ceedling` and dependencies:

`Ceedling` requires both `Ruby` and `GCC` to run
```
sudo apt install python3-pip                           
sudo apt-get install ruby
gem install ceedling                           
pip install gcovr
```

# Build Test Suite
First, go into the project directory where `project.yml` file resides. Then enter the commands below.

```
ceedling test:all                       //build and test the test cases
ceedling gcov:all		                //generate coverage result
```

# Build
To build the project, navigate to the project's root directory in the terminal and run the command `make`. It will compile the source files, link them with the application file, and generate the executable named "app". If you want to clean the project run `make clean`. 


# Device APIs
The device provides a number of C APIs that can be used to access measurements:
```
bool LTC2943_Initialise();                                              // Initialise the driver
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize);    // Read data from the chip @address to dest
bool LTC2973_Write(uint8_t address, uint8_t *src, uint8_t dataSize);    // Write data from src to the chip @address
```

# ChipControl Module
The package contains a number of critical functions:

## Mode Setting
The driver can be configured for a number of modes: Automatic, Scan, Manual, and Sleep. The driver allows monitorng and setting of the current mode to change the driver's operating mode. The modes have the following behaviours:
 
* Automatic
* Scan 
* Manual 
* Sleep 

## Threshold Setting
The driver maintains a number of operational and survival thresholds that can be used for monitoring and alerting mechanisms. The module allows configuration of thresholds for battery charge state.

## Alerting
The module allows for automated checking of measurements against configured thresholds in Automatic and Scan modes. In manual mode, the measurement alerts can be polled.

# RTOS Configuration
When handling the IO interface of the LTC2943 chip in a Real-Time Operating System (RTOS) environment, there are a few considerations to keep in mind. Here's a detailed and specific approach for handling the IO interface of the LTC2943 chip within the Chip Control module in an RTOS environment:

1. Task Design: 
    * Create a dedicated task for the Chip Control module to handle communication with the LTC2943 chip.
    * Assign an appropriate priority to the task to ensure timely execution based on the real-time requirements.
    * Define the task's execution frequency based on the desired sampling rate or event-driven communication with the chip.

2. Synchronization and Mutual Exclusion:
    * Implement a mutex or binary semaphore to provide exclusive access to the IO interface of the LTC2943 chip.
    * Acquire the mutex before accessing the chip's registers or initiating any communication.
    * Release the mutex after the communication is complete to allow other tasks to access the IO interface.
    
3. Interrupt Handling:
    * Configure the interrupt mechanism of the RTOS to handle chip-related interrupts, such as temperature alerts or status changes.
    * Define an interrupt service routine (ISR) to handle the chip interrupts promptly.
    * Within the ISR, signal a semaphore or set a flag to notify the Chip Control task about the occurrence of the interrupt.

4. Time Management:
    * Utilize timers or periodic tasks provided by the RTOS to schedule regular communication with the LTC2943 chip.
    * Configure a timer to trigger at the desired sampling rate or interval for data collection or status monitoring.
    * When the timer expires, the Chip Control task is activated to perform the necessary IO operations on the chip.

5. Error Handling and Recovery:
    * Implement appropriate error handling mechanisms within the Chip Control module.
    * Check for communication errors, such as I2C bus errors or device-specific error codes, and handle them gracefully.
    * Use error detection techniques, such as CRC checks or data integrity verification, to ensure the reliability of data exchanged with the chip.

6. Resource Management:
    * Optimize memory usage by allocating memory efficiently and releasing it when no longer needed.
    * Minimize CPU utilization by employing efficient algorithms and data processing techniques.
    * Consider power management strategies to minimize power consumption, such as reducing the frequency of chip interactions during idle periods.

7. Testing and Validation:
    * Thoroughly test the Chip Control module within the RTOS environment to ensure proper functionality and real-time behavior.
    * Use unit testing techniques to validate the individual functions and integration testing to verify the interaction between the module and the LTC2943 chip.
    * Conduct performance testing to measure the response time and resource utilization of the Chip Control module under different scenarios and workloads.

Refer to the documentation and guidelines provided by the RTOS and the LTC2943 chip datasheet for specific details, interrupt handling requirements, and any recommended practices or limitations.