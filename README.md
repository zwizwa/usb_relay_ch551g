hidapi-hidraw code for CH551G based relays

note that these look similar to the ATTiny45-based boards but use a
different protocol.

the 2-channel boards I have are marked:

USB Relay
QYF-UR02

hid packet format was found on some chinese online store:

Channel 1 is open: 0x00 0xf1, off: 0x00 0x01.
Channel 2 is open: 0x00 0xf2, off: 0x00 0x02.


Note on Linux, this works as well:

```
# echo -n -e '\x00\x01' >/dev/hidraw0 
# echo -n -e '\x00\xf1' >/dev/hidraw0 
# echo -n -e '\x00\x02' >/dev/hidraw0 
# echo -n -e '\x00\xf2' >/dev/hidraw0
```

