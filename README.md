# Senior-Design-Project
This is the repository of the code that my team used for our capstone senior design project.

Senior Design Project Overview:

Situation:
The Internal Combustion Enginer Car at the pack Motorsports Formula SAE Team was running in a charge deficit. Since the alternator is built into the engine, that part cannot change and it is not feasible to replace the battery for a bigger one due to packaging constraints. Due to this we looked into the rectifier that was bought off the shelf. The rectifier was roughly about 75-80% efficient. This was the bottlenenck that we were trying to resolve.

Task: 
In order to clear out this bottleneck, we looked into better rectifiers but the more efficent ones available in the market were too expensive for our budget. In order to address this, we decided to design a custom 3 phase active rectifier to replace the existing passive one with a target of 97% efficiency and a power output of 400W.

Action: 
The design of our prodcut was broken down into 2 subsystems each consisting of 2 members. I primarily worked on power management and Power factor correction for the project. As a part of this, I sized components to minimize losses and completed a power budget for the components on the PCB. Besides this, I was assigned to work on the code for implementing power factor correction to maximize efficiency. The code was wrtiten in C and implemented on a Infineon TLE9893 Microcontroller.

The Implementation of the code was broken down into 2 seperate parts, Data Logging via CAN and input frequency detection. The other part which I worked on was interefacing with the input signals and using the input values to implement the power factor correction that would in turn generate a PWM Signal to control the triggering of the MOSFETs.

Background about power factor correction:  
Power factor correction (PFC) refers to the process of improving the efficiency of electrical power usage in a system by aligning the phase of the current with the phase of the voltage, thereby increasing the power factor. In the context of a three-phase active rectifier, PFC is crucial for ensuring that the rectifier draws current in phase with the voltage, minimizing harmonic distortion and improving overall system efficiency.

To achieve this goal, I utilized the clarke tranform algorithm to convert the 3 variable system representing the 3 phases to a 2 variable in an orthogonal stationary frame. This then fed into a park transform which converted it to a 2 variable system in a orthogonal rotating reference frame. This conversion was done to get the direct and quadrature values of the current and detect the phase difference in between the Voltage and current.


![WhatsApp Image 2025-06-24 at 7 47 24 PM](https://github.com/user-attachments/assets/e758d77b-d057-4255-a760-56c023ac2b79)
