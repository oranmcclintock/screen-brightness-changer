# screen-brightness-changer

A lightweight, modular C++ utility for fine-grained backlight control on Linux systems. 

This utility interacts directly with the Linux kernel's virtual filesystem (`/sys/class/backlight/`) to provide precise brightness adjustments. It is designed to be mapped to window manager keybindings (like Hyprland) for system-wide brightness control.

## Features

- **Precise Control:** Allows for granular adjustments via terminal arguments.
- **Dynamic Step Sizes:** Supports default step sizes or custom values passed via command line.
- **Hardware Safety:** Includes built-in guard clauses to prevent setting brightness outside of valid hardware ranges.
- **Lightweight:** Compiled directly into a small, fast binary with no external dependencies.

## Prerequisites

This utility modifies system hardware files directly. You need permission to write to your backlight device.

### Temporary Fix
For immediate use, you can grant write permissions to your backlight file:
```bash
sudo chmod 666 /sys/class/backlight/intel_backlight/brightness
