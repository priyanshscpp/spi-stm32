// #include <stdio.h> Cant use them as they operate in user mode, in kernel mode we cant use them
#include <linux/usb.h>
#include <linux/module.h>
#include <linux/mutex.h>

#include "usb_transfer.h"

/* Forward declarations of debug helpers */
int usb_dbg_init(const char *name);
void usb_dbg_exit(void);
void usb_dbg_transfer_inc(void);

static struct usb_device *device;

static struct usb_device_id skel_table[] = {
    {USB_DEVICE(0x0781, 0x5567)},
    {}};
MODULE_DEVICE_TABLE(usb, skel_table);

static DEFINE_MUTEX(device_lock);

static int skel_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;
    iface_desc = interface->cur_altsetting;
    dev_info(&interface->dev, "Interface %d probed: (%04X:%04X)\n",
           iface_desc->desc.bInterfaceNumber,
           id->idVendor, id->idProduct);
    dev_info(&interface->dev, "Endpoints: %02X\n",
            iface_desc->desc.bNumEndpoints);
    dev_info(&interface->dev, "InterfaceClass: %02X\n",
            iface_desc->desc.bInterfaceClass);

    for(i = 0; i< iface_desc->desc.bNumEndpoints; i++){
        endpoint = &iface_desc->endpoint[i].desc;
        dev_info(&interface->dev, "ED[%d]->bEndpointAddress: 0x%02X\n",
                i, endpoint->bEndpointAddress);
        dev_info(&interface->dev, "ED[%d]->bmAttributes: 0x%02X\n",
                i, endpoint->bmAttributes);
        dev_info(&interface->dev, "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, endpoint->wMaxPacketSize,
                endpoint->wMaxPacketSize);
    }
    device = interface_to_usbdev(interface);

    /* Example: increment a transfer counter as part of probe path */
    usb_dbg_transfer_inc();

    return 0;
}

static void skel_disconnect(struct usb_interface *interface)
{
    usb_put_dev(device);
    dev_info(&interface->dev, "Device removed\n");
}

static struct usb_driver skel_driver =
    {
        .name = "usb_driver",
        .probe = skel_probe,
        .disconnect = skel_disconnect,
        .id_table = skel_table,
        .supports_autosuspend = 1,
};

static int __init usb_skel_init(void)
{
    int result;
    int dbg_res;
    mutex_init(&device_lock);
    dbg_res = usb_dbg_init("usb_skel");
    if (dbg_res) {
        pr_err("debugfs init failed: %d\n", dbg_res);
        return dbg_res;
    }
    result = usb_register(&skel_driver);
    if (result < 0)
    {
        pr_err("usb registration failed with %s\n", skel_driver.name);
        usb_dbg_exit();
        return result;
    }
    pr_info("USB driver initialised\n");
    return 0;
}

module_init(usb_skel_init);

static void __exit usb_skel_exit(void)
{
    usb_deregister(&skel_driver);
    usb_dbg_exit();
}

module_exit(usb_skel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lovepreet");
MODULE_DESCRIPTION("USB pendrive registration driver");
