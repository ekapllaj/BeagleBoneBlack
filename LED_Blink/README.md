Beagle Bone Black board, blinking leds

In this very small project, we show the led blinking on the device.

go to this directory and type: make

after this, copy the file main.bin to the tftp/ folder

turn on the board, and wait for the u-boot prompt (need to connect the uart0 to see the boot process on a serial terminal)

hit a button to disable the normal Linux boot and acquire the u-boot command terminal.

There are some settings to be done here, we need to setup the environment variables to use the ethernet port so:



=> setenv ethdev eth0

=> setenv ipaddr 192.168.2.15

=> setenv serverip 192.168.2.15

=> setenv gateway 192.168.2.1

=> ping 192.168.2.14

link up on port 0, speed 100, full duplex

Using cpsw device

host 192.168.2.14 is alive

=> tftp 80200000 main.bin
link up on port 0, speed 100, full duplex
Using cpsw device
TFTP from server 192.168.2.14; our IP address is 192.168.2.15
Filename 'main.bin'.
Load address: 0x80200000
Loading: #
	 53.7 KiB/s
done
Bytes transferred = 220 (dc hex)
=> go 80200000
## Starting application at 0x80200000 ...

After this we should see the leds blinking!

if there are problems with the bin image transfer, control if the connection is estabilished, or if the tftp server is running,
it happened sometimes to have problems with the connecition so i had to reboot the computer.



