# keen-cc3200

This library allows you to push events from the [CC3200](http://www.ti.com/product/cc3200) to [https://api.keen.io](https://api.keen.io)

### Community-Supported SDK
This is an _unofficial_ community supported SDK. If you find any issues or have a request please post an [issue](https://github.com/keen/keen-cc3200/issues).

## Examples

An example application that links with the `keen-cc3200` library is available at [example/keen-cc3200](example/keen-cc3200).

```c
#include "http_client.h"
#include "keen_client.h"

char *api_version = "3.0";
char *project_id = "000000000000000000000000";
char *write_key = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

error_code = WlanConnect();
if(error_code < 0)
{
	return error_code;
}

error_code = set_time();
if(error_code < 0)
{
	return error_code;
}

error_code = add_event("motion_detections", "{\"cat\": 1}");

if (error_code < 0) {
	return error_code;
}
```

The above code listing is illustrative and will not compile.

## Library Reference

The `keen-cc3200` library declares five external variables that can be defined in your application. The first three, `api_version`, `project_id`, and `write_key` must be defined in your application.

```c
extern char *api_version;
extern char *project_id;
extern char *write_key;
extern char *read_key;
extern char *master_key;
```

The `keen-cc3200` library also exposes two functions, `add_event`, and `add_events`.

```c
int add_event(const char *event_collection, const char *event_body);
int add_events(const char *events);

```

## Installation

### Installing CCS

For detailed instructions on installing Code Composer Studio, building a sample application, and configuring for your WiFi endpoint, see the [CC3200 SimpleLink Wi-Fi and IoT Solution With MCU LaunchPad Getting Started Guide](http://www.ti.com/lit/pdf/swru376).

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

### Configuring WiFi Endpoint

1. Navigate to `\path\to\CC3200SDK_1.1.0\cc3200-sdk\example\common`
2. Edit `common.h`
    - Set the `SSID_NAME` of your WiFi endpoint
    - Set the `SECURITY_TYPE` (likely `SL_SEC_TYPE_WPA`) endpoint
    - Set the `SECURITY_KEY` of your WiFi endpoint

### Compiling the Library

Once the project has been cloned, we can compile the `keen-cc3200` library.

```sh
git clone git@github.com:keen/keen-cc3200.git
```

1. Start Code Composer Studio
2. When prompted to select a workspace, enter `\path\to\keen-cc3200`
    - Make sure the option to mark as default is left unchecked and select 'OK'
3. Select 'Project > Import CCS Projects...'
    - Browse to `\path\to\keen-cc3200\keen-cc3200` and select 'OK'
    - Make sure that 'Automatically import...' and 'Copy projects into workspace' are left unchecked and select 'Finish'
4. Click the hammer icon to build.
    - From the hammer drop down select 'Release' to build a Release version  

### Compiling the Example Application

Once the `keen-cc3200` library has been compiled we can compile the example application.

1. Start Code Composer Studio
2. When prompted to select a workspace, enter `\path\to\keen-cc3200\exammple`
    - Make sure the option to mark as default is left unchecked and select 'OK'
3. Select 'Project > Import CCS Projects...'
    - Browse to `\path\to\CC3200SDK_1.1.0` and select 'OK'
    - Select the following projects:
        - driverlib
        - oslib
        - simplelink
    - Make sure that 'Automatically import...' and 'Copy projects into workspace' are left unchecked and select 'Finish'
4. Select 'Project > Import CCS Projects...'
    - Browse to `\path\to\keen-cc3200\example\keen-cc3200` and select 'OK'
    - Select the project keen-cc3200
    - Make sure that 'Automatically import...' and 'Copy projects into workspace' are left unchecked and select 'Finish'
5. In the Project Explorer, build the projects in the following order:
    1. driverlib
    2. oslib
    3. simplelink
    4. keen-cc3200
        - A Release version of the library must have been built

### Flashing the Example Application

Once the example application has been compiled we can flash it to the device and debug.

1. Select 'View > Target Configurations'
2. Right click on 'User Defined' and select 'Import Target Configuration'
    - Browse to `\path\to\CC3200SDK_1.1.0\cc3200-sdk\tools\ccs\_patch\CC3200.ccxml`
    - When prompted, select 'Copy files'
3. In the Target Configurations panel right click on 'CC3200.ccxml' and select 'Set as default'
4. The application can now be flashed to the device and debugged by clicking on the debug icon next to the hammer

## Supported Hardware

The `keen-cc3200` library supports the [CC3200](http://www.ti.com/product/cc3200) as it has on board WiFi and TLS, which is required to use [https://keen.io](https://keen.io)'s API.

The library is intended to serve as a reference, and porting it to other wireless MCUs should be simple.

## Notes
