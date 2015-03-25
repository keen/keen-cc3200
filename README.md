# keen-cc3200

This library allows you to push events from the [CC3200](http://www.ti.com/product/cc3200) to [https://api.keen.io](https://api.keen.io)

## Examples

```c

```

## Library Reference

## Installation

### Installing CCS

### Installing Certificate Authority 

The [CC3200](http://www.ti.com/product/cc3200) includes serial flash that stores files as well as the current program. It exposes a filesystem so that  files can be referenced by a path in the program. To transfer files to the device, UniFlash is used.

In order to verify the identity of the host during TLS communications, a Root Certificate Authority is required. The following instructions will install the  Root Certificate Authority for [https://api.keen.io](https://api.keen.io).

1. Start UniFlash.
2. Select 'New Target Configuration'
3. Select 'Add File'
    - A new file will appear on the left menu under 'User Files'. Select it.
4. Change the 'Name' field to `/cert/DigiCertHighAssuranceEVRootCA.cer`
    - This is where the program will look for the file.
5. Change the 'Url' field to `/path/to/repo/cert/DigiCertHighAssuranceEVRootCA.cer`
6. Check 'Update' and 'Verify'. Uncheck 'Erase'
7. Select 'CC31xx/CC32xx Flash Setup and Control' from the left menu.
8. Select 'Program'
9. Make sure to Reset the CC3200 if and when prompted.

### Starting a Project

## Supported Hardware

The `keen-cc3200` library supports the [CC3200](http://www.ti.com/product/cc3200) as it has on board WiFi and TLS, which is required to use [https://keen.io](https://keen.io)'s API.

The library is intended to serve as a reference, and porting it to other wireless MCUs should be simple.

## Notes
