# k24-ps-mio-led-blink
A step-by-step tutorial on blinking the onboard LED of the Avnet K24 Development Kit using MIO GPIO. Covers Vivado hardware setup, Vitis development, and bare-metal C programming on the Zynq UltraScale+ MPSoC.

# Avnet K24 – PS MIO LED Blink

A step-by-step tutorial on controlling the onboard LED of the Avnet K24 Development Kit using Processing System (PS) MIO GPIO. This project covers hardware configuration in Vivado, software platform development in Vitis, and bare-metal C programming on the Zynq UltraScale+ MPSoC.

## 1. Project Overview

This project demonstrates how to configure and control a GPIO pin directly from the Processing System (PS) of the Avnet K24 Development Kit.

The onboard **D13 LED**, connected to **MIO27**, is configured as a GPIO output and controlled by a bare-metal C application running on the ARM Cortex-A53 processor.

Unlike GPIO implementations that use the Programmable Logic (PL), this project uses the PS MIO interface. This means that no custom RTL, AXI GPIO IP, or PL pin constraints are required.

The project is divided into three main stages:

1. **Vivado Hardware Configuration:** Configure the Zynq UltraScale+ MPSoC and enable the appropriate MIO GPIO bank.
2. **Vitis Software Platform:** Export the hardware design, create a Vitis platform, and configure a standalone application.
3. **Bare-Metal GPIO Programming:** Use the Xilinx GPIO driver to configure MIO27 and control the onboard LED.

## 2. Hardware and Software Requirements

### Hardware

- Avnet K24 Development Kit (Kria K24 SOM and carrier card)
- USB cable for board programming and UART communication
- Host computer

### Software

- AMD Vivado 2023.2 or newer
- AMD Vitis 2023.2 or newer
- USB-to-UART/JTAG drivers
- CoolTerm or another serial terminal application

## 3. Hardware Overview

The Avnet K24 Development Kit is built around the AMD Zynq UltraScale+ MPSoC architecture, which combines a Processing System (PS) and Programmable Logic (PL).

- **Processing System (PS):** Contains the ARM processing cores and integrated peripherals, including GPIO, UART, Ethernet, and USB.
- **Programmable Logic (PL):** FPGA fabric used to implement custom digital hardware and accelerators.
- **MIO (Multiplexed I/O):** Provides direct connections between PS peripherals and physical device pins.

For this project, the onboard LED is controlled through the PS GPIO peripheral using MIO27.

### Onboard LED Mapping

| Board LED | MIO Pin | Function |
|---|---:|---|
| D13 | MIO27 | Project LED |
| D14 | MIO28 | Onboard LED |
| D16 | MIO29 | Onboard LED |
| D17 | MIO30 | Onboard LED |

**Target:** D13, connected to MIO27.

## 4. System Architecture

The implementation uses the PS GPIO controller to drive the onboard LED directly.

```text
+-------------------------------------------+
|          Zynq UltraScale+ MPSoC           |
|                                           |
|  +-------------------------------------+  |
|  |        Processing System (PS)       |  |
|  |                                     |  |
|  |  ARM Cortex-A53                     |  |
|  |       |                             |  |
|  |  Bare-Metal C Application           |  |
|  |       |                             |  |
|  |  Xilinx GPIO Driver (XGpioPs)       |  |
|  |       |                             |  |
|  |  PS GPIO Controller                 |  |
|  +-------|-----------------------------+  |
|          |                                |
|        MIO27                              |
+----------|--------------------------------+
           |
           v
       Onboard D13 LED
```

The software application configures MIO27 as an output and repeatedly writes logic levels to the GPIO pin, producing a blinking LED.

## 5. Project Implementation

### Part 1 – Vivado Hardware Configuration

The first stage involves creating a Vivado project and configuring the Zynq UltraScale+ MPSoC.

Key tasks:

- Create a Vivado RTL project for the Avnet K24 Development Kit.
- Add the Zynq UltraScale+ MPSoC IP to the block design.
- Run Block Automation to configure the processing system.
- Enable the GPIO1 MIO bank, which includes MIO27.
- Validate the block design and generate the HDL wrapper.
- Run synthesis and implementation, then generate the bitstream.
- Export the hardware design as an XSA file, including the bitstream.

See: [`docs/part1-vivado-setup.md`](docs/part1-vivado-setup.md)

### Part 2 – Vitis Software Platform

The second stage involves importing the exported hardware design into Vitis and creating a standalone software platform.

Key tasks:

- Create a Vitis platform component.
- Import the XSA hardware specification.
- Select the `psu_cortexa53_0` processor.
- Configure the platform to use the Standalone operating system.
- Build the platform and generate the Board Support Package (BSP).
- Create a bare-metal application using the Hello World example.
- Verify UART communication through a serial terminal.

See: [`docs/part2-vitis-setup.md`](docs/part2-vitis-setup.md)

### Part 3 – MIO GPIO Programming

The final stage involves writing a bare-metal C application to control the onboard LED.

The application uses the Xilinx `XGpioPs` driver to access the PS GPIO controller.

The main implementation steps are:

1. Retrieve the GPIO configuration using `XGpioPs_LookupConfig()`.
2. Initialize the GPIO driver using `XGpioPs_CfgInitialize()`.
3. Configure MIO27 as an output using `XGpioPs_SetDirectionPin()`.
4. Enable the output driver using `XGpioPs_SetOutputEnablePin()`.
5. Control the LED using `XGpioPs_WritePin()`.
6. Introduce a delay between output transitions to produce the blinking effect.

See: [`docs/part3-mio-gpio-programming.md`](docs/part3-mio-gpio-programming.md)

## 6. GPIO Driver Functions

The following Xilinx GPIO driver functions are used in the application.

| Function | Purpose |
|---|---|
| `XGpioPs_LookupConfig()` | Retrieves the GPIO peripheral configuration. |
| `XGpioPs_CfgInitialize()` | Initializes the GPIO driver instance. |
| `XGpioPs_SetDirectionPin()` | Configures a GPIO pin as an input or output. |
| `XGpioPs_SetOutputEnablePin()` | Enables or disables the GPIO output driver. |
| `XGpioPs_WritePin()` | Writes a logic level to a GPIO pin. |

## 7. Repository Structure

```text
k24-ps-mio-led-blink/
│
├── README.md
│
├── docs/
│   ├── part1-vivado-setup.md
│   ├── part2-vitis-setup.md
│   └── part3-mio-gpio-programming.md
│
├── src/
│   └── main.c
│
├── images/
│   ├── block_design.png
│   ├── gpio_mio_configuration.png
│   └── led_blinking.jpg
│
├── .gitignore
└── LICENSE
```

## 8. Expected Result

After successfully building and running the application, the onboard D13 LED should blink continuously.

The application runs on the ARM Cortex-A53 processor and controls the LED directly through the PS GPIO peripheral.

## 9. Key Learning Outcomes

By completing this project, you will learn how to:

- Configure the Zynq UltraScale+ MPSoC Processing System in Vivado.
- Understand the distinction between PS MIO and PL-based GPIO.
- Enable and configure MIO GPIO pins.
- Create a hardware platform in Vitis using an exported XSA.
- Develop and debug a bare-metal application on the Cortex-A53 processor.
- Use the Xilinx `XGpioPs` driver to control physical GPIO pins.

## 10. Future Extensions

This implementation can be extended to explore additional PS GPIO functionality:

- Control multiple onboard LEDs using MIO.
- Implement LED patterns and timing sequences.
- Read button inputs through PS GPIO.
- Compare direct MIO GPIO control with EMIO-based GPIO control through the PL.

## 11. References

- [AMD Vivado Design Suite Documentation](https://docs.amd.com/)
- [AMD Vitis Unified Software Platform Documentation](https://docs.amd.com/r/en-US/ug1400-vitis-embedded)
- [AMD Zynq UltraScale+ MPSoC Documentation](https://docs.amd.com/v/u/en-US/ug1085-zynq-ultrascale-trm)
- [Avnet K24 Development Kit Documentation](https://www.avnet.com/)

---

**Project:** Avnet K24 PS MIO LED Blink  
**Platform:** AMD Zynq UltraScale+ MPSoC  
**Processor:** ARM Cortex-A53  
**GPIO Interface:** PS MIO  
**Target Pin:** MIO27  
**Target LED:** D13  
**Development Tools:** Vivado and Vitis
