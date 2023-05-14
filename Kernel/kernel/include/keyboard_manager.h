#pragma once

#include <cstdint>

namespace kernel
{
	namespace keyboard_scancodes
	{
		enum keyboard_scancode : uint8_t
		{
			backtick_pressed = 0x29,
			escape_pressed = 0x01,
			one_pressed = 0x02,
			two_pressed = 0x03,
			three_pressed = 0x04,
			four_pressed = 0x05,
			five_pressed = 0x06,
			six_pressed = 0x07,
			seven_pressed = 0x08,
			eight_pressed = 0x09,
			nine_pressed = 0x0a,
			zero_pressed = 0x0b,
			minus_pressed = 0x0c,
			equals_pressed = 0x0d,
			backspace_pressed = 0x0e,

			tab_pressed = 0x0f,
			q_pressed = 0x10,
			w_pressed = 0x11,
			e_pressed = 0x12,
			r_pressed = 0x13,
			t_pressed = 0x14,
			y_pressed = 0x15,
			u_pressed = 0x16,
			i_pressed = 0x17,
			o_pressed = 0x18,
			p_pressed = 0x19,
			left_bracket_pressed = 0x1a,
			right_bracket_pressed = 0x1b,
			enter_pressed = 0x1c,

			caps_lock_pressed = 0x3a,
			a_pressed = 0x1e,
			s_pressed = 0x1f,
			d_pressed = 0x20,
			f_pressed = 0x21,
			g_pressed = 0x22,
			h_pressed = 0x23,
			j_pressed = 0x24,
			k_pressed = 0x25,
			l_pressed = 0x26,
			semi_colon_pressed = 0x27,
			single_quote_pressed = 0x28,
			hash_pressed = 0x29,

			left_shift_pressed = 0x2a,
			backslash_pressed = 0x2b,
			z_pressed = 0x2c,
			x_pressed = 0x2d,
			c_pressed = 0x2e,
			v_pressed = 0x2f,
			b_pressed = 0x30,
			n_pressed = 0x31,
			m_pressed = 0x32,
			comma_pressed = 0x33,
			dot_pressed = 0x34,
			slash_pressed = 0x35,
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

		void handle_scancode(keyboard_scancodes::keyboard_scancode const& scancode);
	private:
		bool shift_pressed = false,
			alt_pressed = false,
			ctrl_pressed = false;
	};
}