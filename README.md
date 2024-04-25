# VAM C-ITS for Priobike
This package is specifically designed to facilitate V2X (Vehicle-to-Everything) message communication using the Cohda Wireless SDK. The data flow process within this system is structured as follow. The stability of data transmission requires additional validation.

## script preparation
### CohdaSDK
The Latest SDK containing both MK5 (DSRC), MK6C (C-V2X), MK6 (DSRC + C-V2X) and x64 software is found in [Releases_SDK_and_MKx_2023->SDK](https://cohdawireless.account.box.com/login?redirect_url=%2Ffolder%2F236504075293). You could find official tutorials for [Installing and configuring the MKx SDK in VM](https://support.cohdawireless.com/hc/en-us/articles/202668864-Installing-and-configuring-the-MKx-SDK) and [Building MKx Image using SDK and adding Libraries](https://support.cohdawireless.com/hc/en-us/articles/115002590143-Building-MKx-Image-using-SDK-and-adding-Libraries)

### [Workstation player](workstation player)
#### Share Folder

- set the share folder path on workstation player: VM properties-> options-> sharefolder
- make share folder visiable and available, run
```
vmware-hgfsclient
sudo vmhgfs-fuse .host:/ /mnt/hgfs  -o nonempty -o allow_other
```
- get access to share folder
```
cd /mnt/hgfs
```
#### Network configuration
- networkadapter1: connected NAT
- networkcadapter2: connected bridge: host adapter: realtake USB gbE famliy controller

### Cohda Implementation with VAM Message

The original SDK provides a VM with the EclipseIDE as a development environment.

#### File prepatation for RSU
- VAM message structure is defined in <code>/RSU_mk5/RAW.asn1</code>
- Custom payload is generated in <code>/RSU_mk5/rawits.c</code> with header file <code>/RSU_mk5/rawits.h</code>. The custom payload is PER-encoded data generated from the RAW.asn1 file. This is achieved by using the ASN1C compiler to generate C code from ASN.1, which implements the encoders and decoders and provides the structure of the message to populate. Apart from this, this file includes a UDP server to receive externe data from file <code>/vam_client/Windows/VAMinput.py</code>

please overwrite these three files under home/duser/mk5/stack/apps/exampleETSI/src. 

#### File prepatation for RSU
- VAM message structure is defined in <code>/OBU_mk5/RAW.asn1</code>, Both units employ identical VAM structures for both decoding and encoding.
- VAM message can be received in <code>/OBU_mk5/rawits.c</code> with header file <code>/RSU_mk5/rawits.h</code>. This file includes a UDP client to send received data out for further analysis and visualisation.

please overwrite these three files under home/duser/mk6/stack/apps/exampleETSI/src. 

#### Build 
please replace "mk6" with "mk5" when using mk6.
```
cd ~/mk5/stack/apps/exampleETSI`
make mk5` (compiling)
make mk5-tarball
```
you can use [winscp](https://winscp.net/eng/download.php) or command
``` 
 `scp -6 exampleETSI-mk5-Exported.tgz user@\[<ip%interface>\]:/tmp` 
```
to copy <code> /home/duser/mk6/stack/apps/exampleETSI/exampleETSI-mk5-Exported.tgz</code> to cohda model.
user name & PW: user

## Run scripts

### Run UDP client script

<code> VAMinput.py</code> can receive test Priobike data from backend through MQTT and send it to RSU thorugh UDP. Feedback message can be received as well to check the data flow. This file can be compiled using GCC and generate exe file in Windows.

``` 
gcc -o udp_server udp_server.c -lws2_32
```

### start Cohda 

1. SSH or PuTTY 
mk5: fe80::6e5:48ff:fe20:5a88%<interface>` 
mk6: fe80::6e5:48ff:fe50:01A0%<interface>` 
interface can be checked with ipconfig in Windows and ifconfig in Linux

2. unzipping uploaded exampleETSI-mk5-Exported.tgz
```
sudo tar xzfv /tmp/exampleETSI-mk5-Exported.tgz -C /mnt/rw
```

3. check GPS connection. 
```
gpspipe -r
```
4. start GPS connection.
```
/mnt/rw/exampleETSI/rc.exampleETSI start raw
```     

5. shutdown.
```
/mnt/rw/absolutETSI/rc.exampleETSI stop
```

### Run UDP server script (in progress)
- This file involves UDP server to exact data from OBU units. 
- This file involves a Python application using PyQt5 to display and dynamically update a real-time map in a GUI window.


