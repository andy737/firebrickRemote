#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include "esb6300.h"

static void sata_init(struct device *dev)
{
	/* Enable sata devices so the linux sata driver will work */

	/* Enable SATA devices */

	printk(BIOS_DEBUG, "SATA init\n");
        /* SATA configuration */
        pci_write_config8(dev, 0x04, 0x07);
        pci_write_config8(dev, 0x09, 0x8f);

        /* Set timmings */
        pci_write_config16(dev, 0x40, 0x0a307);
        pci_write_config16(dev, 0x42, 0x0a307);

        /* Sync DMA */
        pci_write_config16(dev, 0x48, 0x000f);
        pci_write_config16(dev, 0x4a, 0x1111);

        /* 66 mhz */
        pci_write_config16(dev, 0x54, 0xf00f);

        /* Combine ide - sata configuration */
        pci_write_config8(dev, 0x90, 0x0);

        /* port 0 & 1 enable */
        pci_write_config8(dev, 0x92, 0x33);

        /* initialize SATA  */
        pci_write_config16(dev, 0xa0, 0x0018);
        pci_write_config32(dev, 0xa4, 0x00000264);
        pci_write_config16(dev, 0xa0, 0x0040);
        pci_write_config32(dev, 0xa4, 0x00220043);

	printk(BIOS_DEBUG, "SATA Enabled\n");
}

static void esb6300_sata_set_subsystem(device_t dev, unsigned vendor, unsigned device)
{
	/* This value is also visible in usb1, usb2 and smbus functions */
	pci_write_config32(dev, PCI_SUBSYSTEM_VENDOR_ID,
		((device & 0xffff) << 16) | (vendor & 0xffff));
}

static struct pci_operations lops_pci = {
	.set_subsystem = esb6300_sata_set_subsystem,
};
static struct device_operations sata_ops  = {
	.read_resources   = pci_dev_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init             = sata_init,
	.scan_bus         = 0,
	.ops_pci          = &lops_pci,
};

static const struct pci_driver sata_driver __pci_driver = {
        .ops    = &sata_ops,
        .vendor = PCI_VENDOR_ID_INTEL,
        .device = PCI_DEVICE_ID_INTEL_6300ESB_SATA,
};

static const struct pci_driver sata_driver_nr __pci_driver = {
        .ops    = &sata_ops,
        .vendor = PCI_VENDOR_ID_INTEL,
        .device = PCI_DEVICE_ID_INTEL_6300ESB_SATA_RAID,
};

