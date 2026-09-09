# Keil µVision & Proteus VSM Setup Guide

This guide walks undergraduate students through setting up the complete 8051 toolchain: from writing and compiling C code in Keil µVision to simulating and debugging circuits in Proteus VSM.

---

## Part 1: Keil µVision C51 Setup

### Step 1: Create a New Project
1. Launch **Keil µVision**.
2. Go to **Project > New µVision Project...**.
3. Choose a folder for your experiment and name the project (e.g., `Exp01_LED`).
4. In the device selection dialog:
   - Select **Microchip (or Atmel) > AT89S52** (or `AT89C51`).
   - Click **OK**.
5. When prompted: *"Copy Standard 8051 Startup Code to Project Folder and Add File to Project?"*
   - Click **Yes** (this adds `STARTUP.A51`).

### Step 2: Configure Project for HEX File Generation
1. In the Project Workspace window, right-click **Target 1** and select **Options for Target 'Target 1'...** (Shortcut: `Alt + F7`).
2. Go to the **Target** tab:
   - Set **Xtal (MHz):** `11.0592`.
   - Set Memory Model: `Small: variables in DATA`.
   - Set Code Rom Size: `Large: 64K program`.
3. Go to the **Output** tab:
   - Check the box **Create HEX File**. (This is critical: without this, Keil only produces an `.OBJ` file).
4. Click **OK**.

### Step 3: Add Source Code
1. Expand **Target 1**, right-click **Source Group 1**, and select **Add New Item to Group 'Source Group 1'...**
2. Choose **C File (.c)**, name it `main.c`, and click **Add**.
3. Paste or write the experiment C code.
4. Press **F7** (or **Project > Build Target**).
5. Verify the Build Output window shows:
   ```
   "Exp01_LED" - 0 Error(s), 0 Warning(s).
   creating hex file from "Exp01_LED"...
   ```

---

## Part 2: Proteus VSM Simulation Setup

### Step 1: Create Schematic
1. Open **Proteus ISIS**.
2. Press **P** (Pick from Libraries) to find components:
   - `AT89C51` or `AT89S52`
   - `CRYSTAL` (Quartz Crystal)
   - `CAP` / `CAP-ELEC` (Capacitors)
   - `RES` (Resistors) / `RESPACK-8` (Port 0 pull-ups)
   - LEDs, 7SEG-COM-CATHODE, LM016L (16x2 LCD), ADC0808/0809, DAC0808, L293D, MOTOR.

### Step 2: Attach the Compiled HEX File
1. Double-click the 8051 microcontroller in Proteus.
2. In the **Edit Component** dialog:
   - Set **Clock Frequency:** `11.0592MHz` (or `12MHz` depending on your code).
   - Click the folder icon next to **Program File**.
   - Browse and select your compiled `.hex` file.
   - Click **OK**.

### Step 3: Run the Simulation
1. Click the **Play** (Execute) icon in the bottom-left corner of the Proteus window.
2. Watch pin voltage states:
   - 🔴 **Red square:** Logic High (+5V)
   - 🔵 **Blue square:** Logic Low (GND)
   - 🔘 **Gray square:** High-impedance / Floating
3. Use interactive buttons, switches, and virtual instruments (Virtual Terminal, Oscilloscope) to observe behavior in real time.

---

## Part 3: Flashing Real Hardware (USBASP Programmer)

If testing on physical hardware:
1. Connect your 8051 board to your PC using a **USBASP ISP Programmer** (6-pin / 10-pin ribbon cable).
2. Open **ProgISP** or **avrdude**:
   - Select Chip: `AT89S52`
   - Load Flash: Select your generated `.hex` file
   - Click **Auto** / **Write**
3. Once verification passes, disconnect the programmer and power the board via +5V DC.
