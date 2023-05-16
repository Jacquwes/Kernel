#include "logger.h"
#include "pci.h"
#include "pic.h"


namespace kernel
{
	pci_manager* pci_manager::instance = nullptr;

	pci_manager::pci_manager()
	{
		instance = this;

		logger::log(debug, "PCI manager > Initializing.");

		enumerate_buses();

		logger::log(debug, "PCI manager > Initialized. Found %d devices.", pci_device_count);
	}

	uint16_t pci_manager::read(uint32_t bus, uint32_t device, uint32_t function, uint8_t offset)
	{
		uint32_t address = 0;

		address |= (1 << 31);
		address |= (bus << 16);
		address |= (device << 11);
		address |= (function << 8);
		address |= (offset & 0xfc);

		pic::outl(CONFIG_ADDRESS, address);
		return (pic::inl(CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff;
	}

	void pci_manager::write(uint32_t bus, uint32_t device, uint32_t function, uint8_t offset, uint16_t value)
	{
		uint32_t address = 0;

		address |= (1 << 31);
		address |= (bus << 16);
		address |= (device << 11);
		address |= (function << 8);
		address |= (offset & 0xfc);

		pic::outl(CONFIG_ADDRESS, address);
		pic::outl(CONFIG_DATA, value);
	}



	uint16_t pci_manager::get_vendor_id(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x00);
	}

	uint16_t pci_manager::get_device_id(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x02);
	}



	pci_command_register pci_manager::get_command(uint32_t bus, uint32_t device, uint32_t function)
	{
		return (pci_command_register)read(bus, device, function, 0x04);
	}

	pci_status_register pci_manager::get_status(uint32_t bus, uint32_t device, uint32_t function)
	{
		return (pci_status_register)read(bus, device, function, 0x06);
	}



	uint8_t pci_manager::get_revision_id(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x08);
	}

	uint8_t pci_manager::get_programming_interface(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x08) >> 0x8;
	}
	
	uint8_t pci_manager::get_subclass(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x0a) & 0xff;
	}

	uint8_t pci_manager::get_class_code(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0xa) >> 0x8;
	}



	uint8_t pci_manager::get_cache_line_size(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x0c) & 0xff;
	}

	uint8_t pci_manager::get_latency_timer(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x0c) >> 0x08;
	}

	uint8_t pci_manager::get_header_type(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x0e) & 0xff;
	}

	uint8_t pci_manager::get_bist(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x0e) >> 0x08;
	}

	uint8_t pci_manager::get_secondary_bus_number(uint32_t bus, uint32_t device, uint32_t function)
	{
		return read(bus, device, function, 0x18) >> 0x08;
	}



	void pci_manager::check_bus(uint32_t bus)
	{
		for (uint32_t device = 0; device < 32; device++)
		{
			if (get_vendor_id(bus, device, 0) == 0xffff)
				continue;

			check_device(bus, device);
		}
	}

	void pci_manager::check_device(uint32_t bus, uint32_t device)
	{
		uint8_t header_type = get_header_type(bus, device, 0);
		// If bit 7 is set, the device has multiple functions; otherwise, it is a single function device.
		uint8_t function_count = (header_type & 0x80) ? 8 : 1;

		for (uint32_t function = 0; function < function_count; function++)
		{
			if (get_vendor_id(bus, device, function) == 0xffff)
				continue;

			check_function(bus, device, function);
		}
	}

	void pci_manager::check_function(uint32_t bus, uint32_t _device, uint32_t function)
	{
		uint8_t class_code = get_class_code(bus, _device, function);
		uint8_t subclass = get_subclass(bus, _device, function);
		uint8_t programming_interface = get_programming_interface(bus, _device, function);
		uint8_t header_type = get_header_type(bus, _device, function);

		pci_device device;
		device.bus = bus;
		device.device = _device;
		device.function = function;

		device.header.bist = get_bist(bus, _device, function);
		device.header.cache_line_size = get_cache_line_size(bus, _device, function);
		device.header.class_code = class_code;
		device.header.header_type = header_type;
		device.header.latency_timer = get_latency_timer(bus, _device, function);
		device.header.programming_interface_bit = programming_interface;
		device.header.revision_id = get_revision_id(bus, _device, function);
		device.header.subclass = subclass;
		device.header.vendor_id = get_vendor_id(bus, _device, function);
		device.header.device_id = get_device_id(bus, _device, function);
		device.header.command = get_command(bus, _device, function);
		device.header.status = get_status(bus, _device, function);

		pci_devices[pci_device_count++] = pci_device();

		if (class_code == class_codes::bridge_device && subclass == class_codes::pci_to_pci_bridge)
		{
			uint8_t secondary_bus = get_secondary_bus_number(bus, _device, function);
			check_bus(secondary_bus);
		}
	}

	void pci_manager::enumerate_buses()
	{
		pci_device_count = 0;

		uint8_t header_type = get_header_type(0, 0, 0);
		// If bit 7 is set, the device has multiple functions; otherwise, it is a single function device.
		uint8_t function_count = (header_type & 0x80) ? 8 : 1;

		if (function_count == 1)
		{
			check_bus(0);
		}
		else
		{
			for (uint32_t function = 0; function < function_count; function++)
			{
				if (get_vendor_id(0, 0, function) == 0xffff)
					continue;
				check_bus(function);
			}
		}
	}
}