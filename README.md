# Custom USB Device Driver in C (Linux Kernel Module)

A small, production-quality example of a Linux USB driver module that probes a target device, logs interface/endpoint details, and exposes simple runtime diagnostics via debugfs. Structured for senior engineering review.

## Features
- Probe/disconnect of a specific VID:PID
- Enumerates and logs interface class, endpoints, and packet sizes
- Debugfs diagnostics directory `/sys/kernel/debug/usb_skel/`
  - `stats`: total number of tracked transfer events
- Separation of concerns:
  - `usb_driver.c`: driver registration, probe/disconnect, logging
  - `usb_transfer.c/.h`: debugfs and counters
- Clean build via out-of-tree kernel module Makefile
- SPDX headers and module metadata

## Build
Prerequisites: kernel headers for the running kernel present at `/lib/modules/$(uname -r)/build`.
```bash
make
```

## Load and Verify
```bash
sudo insmod usb_driver.ko
# verify logs
dmesg | tail -n 100 | cat

# ensure debugfs is mounted
sudo mount -t debugfs none /sys/kernel/debug || true

# view stats
sudo cat /sys/kernel/debug/usb_skel/stats | cat

# unload
sudo rmmod usb_driver
```

## Target Device
The example matches:
- Vendor ID: `0x0781`
- Product ID: `0x5567`

Change the entries in `skel_table` in `usb_driver.c` to target your device.

## Code Overview
- `usb_skel_init`/`usb_skel_exit`: module lifecycle; registers/deregisters the driver and initializes debugfs
- `skel_probe`: logs interface/endpoint descriptors and increments a debug counter
- `skel_disconnect`: releases references and logs device removal
- `usb_transfer.c`: provides `usb_dbg_init`, `usb_dbg_exit`, and `usb_dbg_transfer_inc`, exporting them for the driver

## Design Notes
- Uses `dev_info`/`pr_*` for structured logging
- Minimal shared state guarded by a `mutex` (placeholder for future concurrency)
- Debugfs avoids sysfs ABI commitments for developer diagnostics
- Small footprint and readable flow for interview/review settings

## Project Layout
- `usb_driver.c`: USB driver
- `usb_transfer.c/.h`: diagnostics helpers
- `Makefile`: kernel module build

## License
GPL-2.0. See `LICENSE`.
