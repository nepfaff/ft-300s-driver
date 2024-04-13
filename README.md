# FT-300S LCM Driver

## Installation

Build:
```bash
bazel build //...
```

Add user to `dialout` group (replace `username` with the actual username). NOTE: Need to
reboot for the changes to take effect.
```bash
sudo usermod -a -G dialout username
```

Make sure that the sensor is visible. A new device named `ttyUSBx` should be present in
`/dev`, which can be verified with the following command.
```bash
ls -l /dev | grep ttyUSB
```

Additional documentation can be downloaded from [here](https://robotiq.com/support) by
selecting `FT 3000-S Force Torque Sensor` -> `Other brands`.

## Running the driver

Sensor readings are published on `FT300S_SENSOR_DATA` and are of type `ft_reading_t`
(see `lcmtypes`).

```bash
./bazel-bin/src/ft_300s_driver
```
NOTE: It is normal for `Input/output error` to be displayed for the first few seconds.
A permission error means that the user has not been added to the `dialout` group or
that the computer has not been rebooted afterwards.
