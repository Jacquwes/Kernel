#pragma once

#include <cstdint>

namespace kernel
{
	constexpr auto CONFIG_ADDRESS = 0xcf8;
	constexpr auto CONFIG_DATA = 0xcfc;

#pragma region class_codes
	namespace class_codes
	{
		enum class_code
		{
			unclassified = 0x00,
			mass_storage_controller = 0x01,
			network_controller = 0x02,
			display_controller = 0x03,
			multimedia_controller = 0x04,
			memory_controller = 0x05,
			bridge_device = 0x06,
			simple_communication_controller = 0x07,
			base_system_peripheral = 0x08,
			input_device_controller = 0x09,
			docking_station = 0x0a,
			processor = 0x0b,
			serial_bus_controller = 0x0c,
			wireless_controller = 0x0d,
			intelligent_controller = 0x0e,
			satellite_communication_controller = 0x0f,
			encryption_controller = 0x10,
			signal_processing_controller = 0x11,
			processing_accelerator = 0x12,
			non_essential_instrumentation = 0x13,
			coprocessor = 0x40,
			unknown = 0xff
		};

		enum subclass
		{
			non_vga_compatible_devices = 0x00,
			vga_compatible_devices = 0x01,
			scsi_bus_controller = 0x00,
			ide_controller = 0x01,
			floppy_disk_controller = 0x02,
			ipi_bus_controller = 0x03,
			raid_controller = 0x04,
			ata_controller = 0x05,
			sata_controller = 0x06,
			serial_attached_scsi_controller = 0x07,
			non_volatile_memory_controller = 0x08,
			ethernet_controller = 0x00,
			token_ring_controller = 0x01,
			fddi_controller = 0x02,
			atm_controller = 0x03,
			isdn_controller = 0x04,
			worldfip_controller = 0x05,
			picmg_controller = 0x06,
			infiniband_controller = 0x07,
			fabric_controller = 0x08,
			vga_compatible_controller = 0x00,
			xga_controller = 0x01,
			_3d_controller = 0x02,
			multimedia_video_controller = 0x03,
			multimedia_audio_controller = 0x04,
			computer_telephony_device = 0x05,
			audio_device = 0x06,
			ram_controller = 0x00,
			flash_controller = 0x01,
			host_bridge = 0x00,
			isa_bridge = 0x01,
			eisa_bridge = 0x02,
			mca_bridge = 0x03,
			pci_to_pci_bridge = 0x04,
			pcmcia_bridge = 0x05,
			nu_bus_bridge = 0x06,
			cardbus_bridge = 0x07,
			raceway_bridge = 0x08,
			pci_to_pci_bridge_semi_transparent = 0x09,
			infiniband_to_pci_host_bridge = 0x0a,
			serial_controller = 0x00,
			parallel_controller = 0x01,
			multiport_serial_controller = 0x02,
			modem = 0x03,
			iee_488_gpib_controller = 0x04,
			smart_card_controller = 0x05,
			pic = 0x00,
			dma_controller = 0x01,
			timer = 0x02,
			rtc_controller = 0x03,
			pci_hot_plug_controller = 0x04,
			sd_host_controller = 0x05,
			iommu = 0x06,
			keyboard_controller = 0x00,
			digitizer_pen = 0x01,
			mouse_controller = 0x02,
			scanner_controller = 0x03,
			gameport_controller = 0x04,
			generic = 0x00,
			_386 = 0x00,
			_486 = 0x01,
			pentium = 0x02,
			pentium_pro = 0x03,
			alpha = 0x10,
			power_pc = 0x20,
			mips = 0x30,
			co_processor = 0x40,
			firewire_controller = 0x00,
			access_bus_controller = 0x01,
			ssa_controller = 0x02,
			usb_controller = 0x03,
			fibre_channel_controller = 0x04,
			smbus_controller = 0x05,
			infiniband_controller_2 = 0x06,
			ipmi_interface = 0x07,
			sercos_interface = 0x08,
			canbus_controller = 0x09,
			irda_compatible_controller = 0x00,
			consumer_ir_controller = 0x01,
			rf_controller = 0x10,
			bluetooth_controller = 0x11,
			broadband_controller = 0x12,
			ethernet_controller_2 = 0x20,
			ehternet_controller_3 = 0x21,
			i20_controller = 0x00,
			satellite_tv_controller = 0x01,
			satellite_audio_controller = 0x02,
			satellite_voice_controller = 0x03,
			satellite_data_controller = 0x04,
			encryption_controller_2 = 0x00,
			signal_processing_controller_2 = 0x01,
			other = 0x80
		};
	}
#pragma endregion

	struct pci_command_register
	{
		// Respond to I/O space accesses
		uint16_t io_space : 1;
		// Respond to memory space accesses
		uint16_t memory_space : 1;
		// Behave as a bus master
		uint16_t bus_master : 1;
		// Monitor special cycle operations
		uint16_t memory_write_and_invalidate : 1;
		// Snoop palette registers writes
		uint16_t vga_palette_snoop : 1;
		// Normal action on parity error
		uint16_t parity_error_response : 1;
		uint16_t reserved0 : 1;
		// SERR# driver
		uint16_t serr_enable : 1;
		// Generate fast back-to-back transactions
		uint16_t fast_back_to_back_enable : 1;
		// Assertion of the devices INTx# signal
		uint16_t interrupt_disable : 1;
		uint16_t reserved1 : 6;
	} __attribute__((packed));

	struct pci_status_register
	{
		uint16_t reserved0 : 3;
		// Device's INTx# signal
		uint16_t interrupt_status : 1;
		// Linked list capability at 0x34
		uint16_t capabilities_list : 1;
		// 66 MHz capable
		uint16_t _66_mhz_capable : 1;
		uint16_t reserved1 : 1;
		// Accept fast back-to-back transactions that are not from the same agent
		uint16_t fast_back_to_back_capable : 1;
		// ???
		uint16_t master_data_parity_error : 1;
		// 0 is fast, 1 is medium, 2 is slow
		uint16_t devsl_timing : 2;
		// Target device terminated transaction with target abort
		uint16_t signaled_target_abort : 1;
		// Target device terminated transaction with target abort by master device
		uint16_t received_target_abort : 1;
		// Target device terminated transaction with master abort by master device
		uint16_t received_master_abort : 1;
		// Device asserted SERR#
		uint16_t signaled_system_error : 1;
		// Parity error detected
		uint16_t detected_parity_error : 1;
	} __attribute__((packed));

	struct memory_space_base_address_register
	{
		uint32_t always_0 : 1;
		uint32_t type : 2;
		uint32_t prefetchable : 1;
		uint32_t base_address : 28;
	};

	struct io_space_base_address_register
	{
		uint32_t always_1 : 1;
		uint32_t reserved : 1;
		uint32_t base_address : 30;
	};

	struct pci_device_header
	{
		uint16_t vendor_id;
		uint16_t device_id;

		pci_command_register command;
		pci_status_register status;

		uint8_t revision_id;
		uint8_t programming_interface_bit;
		uint8_t subclass;
		uint8_t class_code;

		uint8_t cache_line_size;
		uint8_t latency_timer;
		uint8_t header_type;
		uint8_t bist;
	} __attribute__((packed));

	struct pci_device_0x0
	{
		pci_device_header header;

		memory_space_base_address_register base_address_register_0;
		memory_space_base_address_register base_address_register_1;
		memory_space_base_address_register base_address_register_2;
		memory_space_base_address_register base_address_register_3;
		memory_space_base_address_register base_address_register_4;
		memory_space_base_address_register base_address_register_5;
		// Points to the card information structure
		uint32_t cardbus_cis_pointer;

		uint16_t subsystem_vendor_id;
		uint16_t subsystem_id;

		uint32_t expansion_rom_base_address;

		uint8_t capabilities_pointer;
		uint8_t reserved0[3];

		uint32_t reserved1;

		uint8_t interrupt_line;
		uint8_t interrupt_pin;
		uint8_t min_grant;
		uint8_t max_latency;
	} __attribute__((packed));

	struct pci_device_0x1
	{
		pci_device_header header;

		memory_space_base_address_register base_address_register_0;
		memory_space_base_address_register base_address_register_1;

		uint8_t primary_bus_number;
		uint8_t secondary_bus_number;
		uint8_t subordinate_bus_number;
		uint8_t secondary_latency_timer;

		uint8_t io_base;
		uint8_t io_limit;
		uint16_t secondary_status;

		uint16_t memory_base;
		uint16_t memory_limit;

		uint16_t prefetchable_memory_base;
		uint16_t prefetchable_memory_limit;

		uint32_t prefetchable_base_upper_32_bits;
		uint32_t prefetchable_limit_upper_32_bits;

		uint16_t io_base_upper_16_bits;
		uint16_t io_limit_upper_16_bits;

		uint8_t capabilities_pointer;
		uint8_t reserved0[3];

		uint32_t expansion_rom_base_address;

		uint8_t interrupt_line;
		uint8_t interrupt_pin;
		uint16_t bridge_control;
	} __attribute__((packed));;

	struct pci_device_0x2
	{
		pci_device_header header;

		uint32_t cardbus_socket_exca_base_address;

		uint8_t capabilities_pointer;
		uint8_t reserved0;
		uint16_t secondary_status;

		uint8_t pci_bus_number;
		uint8_t cardbus_bus_number;
		uint8_t subordinate_bus_number;
		uint8_t cardbus_latency_timer;

		memory_space_base_address_register memory_base_address_0;
		uint32_t memory_limit_0;
		memory_space_base_address_register memory_base_address_1;
		uint32_t memory_limit_1;
		io_space_base_address_register io_base_address_0;
		uint32_t io_limit_0;
		io_space_base_address_register io_base_address_1;
		uint32_t io_limit_1;

		uint8_t interrupt_line;
		uint8_t interrupt_pin;
		uint16_t bridge_control;

		uint16_t subsystem_device_id;
		uint16_t subsystem_vendor_id;

		uint32_t pc_card_legacy_mode_base_address;
	} __attribute__((packed));

	struct pci_device
	{
		pci_device_header header;

		uint8_t bus;
		uint8_t device;
		uint8_t function;
	};

	class pci_manager
	{
	public:
		pci_manager();

		static pci_manager* instance;

		uint16_t read(uint32_t bus, uint32_t device, uint32_t function, uint8_t offset);
		void write(uint32_t bus, uint32_t device, uint32_t function, uint8_t offset, uint16_t value);

		uint16_t get_vendor_id(uint32_t bus, uint32_t device, uint32_t function);
		uint16_t get_device_id(uint32_t bus, uint32_t device, uint32_t function);

		pci_command_register get_command(uint32_t bus, uint32_t device, uint32_t function);
		pci_status_register get_status(uint32_t bus, uint32_t device, uint32_t function);

		uint8_t get_revision_id(uint32_t bus, uint32_t device, uint32_t function);
		uint8_t get_programming_interface(uint32_t bus, uint32_t device, uint32_t function);
		uint8_t get_subclass(uint32_t bus, uint32_t device, uint32_t function);
		uint8_t get_class_code(uint32_t bus, uint32_t device, uint32_t function);

		uint8_t get_cache_line_size(uint32_t bus, uint32_t device, uint32_t function);
		uint8_t get_latency_timer(uint32_t bus, uint32_t device, uint32_t function);
		uint8_t get_header_type(uint32_t bus, uint32_t device, uint32_t function);
		uint8_t get_bist(uint32_t bus, uint32_t device, uint32_t function);

		uint8_t get_secondary_bus_number(uint32_t bus, uint32_t device, uint32_t function);

		void check_bus(uint32_t bus);
		void check_device(uint32_t bus, uint32_t device);
		void check_function(uint32_t bus, uint32_t device, uint32_t function);

		void enumerate_buses();

	private:
		pci_device pci_devices[32];

		uint32_t pci_device_count;
	};
}
