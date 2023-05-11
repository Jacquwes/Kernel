#pragma once

#include <cstdint>

namespace kernel
{
	namespace keyboard_scancodes
	{
		enum keyboard_scancode_azerty : uint8_t
		{
			pow2_pressed = 0x29,
			ampersand_pressed = 0x02,
			eacute_pressed = 0x03,
			quote_double_pressed = 0x04,
			quote_simple_pressed = 0x05,
			left_parenthesis_pressed = 0x06,
			minus_pressed = 0x07,
			egrave_pressed = 0x08,
			underscore_pressed = 0x09,
			c_cedilla_pressed = 0x0a,
			a_grave_pressed = 0x0b,
			right_parenthesis_pressed = 0x0c,
			equals_pressed = 0x0d,
			backspace_pressed = 0x0e,

			tab_pressed = 0x0f,
			a_pressed = 0x10,
			z_pressed = 0x11,
			e_pressed = 0x12,
			r_pressed = 0x13,
			t_pressed = 0x14,
			y_pressed = 0x15,
			u_pressed = 0x16,
			i_pressed = 0x17,
			o_pressed = 0x18,
			p_pressed = 0x19,
			circumflex_pressed = 0x1a,
			dollar_pressed = 0x1b,
			enter_pressed = 0x1c,

			caps_lock_pressed = 0x3a,
			q_pressed = 0x1e,
			s_pressed = 0x1f,
			d_pressed = 0x20,
			f_pressed = 0x21,
			g_pressed = 0x22,
			h_pressed = 0x23,
			j_pressed = 0x24,
			k_pressed = 0x25,
			l_pressed = 0x26,
			m_pressed = 0x27,
			ugrave_pressed = 0x28,
			asterisk_pressed = 0x2b,

			left_shift_pressed = 0x2a,
			less_than_pressed = 0x56,
			w_pressed = 0x2c,
			x_pressed = 0x2d,
			c_pressed = 0x2e,
			v_pressed = 0x2f,
			b_pressed = 0x30,
			n_pressed = 0x31,
			comma_pressed = 0x32,
			semicolon_pressed = 0x33,
			colon_pressed = 0x34,
			exclamation_mark_pressed = 0x35,
			right_shift_pressed = 0x36,

			left_control_pressed = 0x1d,
			left_windows_pressed = 0x5b,
			left_alt_pressed = 0x38,
			space_pressed = 0x39,
			right_alt_pressed = 0x38,
			right_windows_pressed = 0x5c,
			menu_pressed = 0x5d,
			right_control_pressed = 0x1d,
		};
	}

	class keyboard_manager
	{
	public:
		keyboard_manager();
		static keyboard_manager* instance;

		void handle_scancode_azerty(keyboard_scancodes::keyboard_scancode_azerty const& scancode);
	private:
		bool shift_pressed = false,
			alt_pressed = false,
			ctrl_pressed = false;
	};
}