#include <hidapi/hidapi.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG(...) fprintf(stderr, __VA_ARGS__)
#define ERROR(...) do { LOG(__VA_ARGS__); exit(1); } while(0)
#define ASSERT(c)  if (!((c))) { ERROR("ASSERT: " #c "\n"); }

#define VID 0x0519
#define PID 0x2018

int main(int argc, char **argv) {
    ASSERT(argc > 2);
    int relay = atoi(argv[1]);  // 0 | 1
    int state = atoi(argv[2]);  // 1, 2, ...
    //LOG("relay = %d, state = %d\n", relay, state);
    for(struct hid_device_info *dev = hid_enumerate(VID,PID); dev; dev=dev->next) {
        LOG("%ls %ls %s\n", dev->manufacturer_string, dev->product_string, dev->path);
        hid_device *handle;
        ASSERT(handle = hid_open_path(dev->path));
        unsigned char buf[2] = {
            0,
            relay + (state ? 0xF0 : 0x00)
        };
        // for(int i=0; i<sizeof(buf); i++) LOG(" %02x", buf[i]); LOG("\n");
        ASSERT(hid_write(handle, buf, sizeof(buf)) >= 0);
        return 0;
    }
    return 0;
}
