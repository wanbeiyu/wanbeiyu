# Wanbeiyu

The core library of the Wanbeiyu firmware.

## Overview

This library serves as a hardware abstraction layer for controlling the 3DS. It requires:

- 24 GPIOs, utilizing LOW/Hi-Z states
- 4 channels of IDAC, with more than 256 steps for each axis
- 2 channels of RDAC, with more than 320 steps for the X-axis and more than 240 steps for the Y-axis. The total resistance should be lower than the pull-up resistance (potentially 10kΩ)

These components are defined through interfaces. Clients are responsible for implementing these interfaces according to the actual hardware specifications and must provide them as arguments to the `wanbeiyu_*_init` functions.
