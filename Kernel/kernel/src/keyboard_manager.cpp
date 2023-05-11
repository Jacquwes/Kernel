#include "keyboard_manager.h"

#include "output.h"
#include <cstdio>

namespace kernel
{
	keyboard_manager* keyboard_manager::instance = nullptr;

	keyboard_manager::keyboard_manager()
	{
		instance = this;

		std::printf("Keyboard manager > Initialized.\n");
	}

	void keyboard_manager::handle_scancode_azerty(keyboard_scancodes::keyboard_scancode_azerty const& scancode)
	{
		if (scancode & 0x80)
		{
			switch (scancode & ~0x80)
			{
			case keyboard_scancodes::left_shift_pressed:
			case keyboard_scancodes::right_shift_pressed:
				shift_pressed = false;
				break;
			default:
				break;
			}
			return;
		}

		switch (scancode)
		{
			using namespace keyboard_scancodes;
#define s(a, b) this->shift_pressed ? b : a
#pragma region first_row
		case pow2_pressed:
			output::instance->putchar('²');
			break;

		case ampersand_pressed:
			output::instance->putchar(s('&', '1'));
			break;

		case eacute_pressed:
			output::instance->putchar(s('é','2'));
			break;

		case quote_double_pressed:
			output::instance->putchar(s('"', '3'));
			break;

		case quote_simple_pressed:
			output::instance->putchar(s('\'', '4'));
			break;

		case left_parenthesis_pressed:
			output::instance->putchar(s('(', '5'));
			break;

		case minus_pressed:
			output::instance->putchar(s('-', '6'));
			break;

		case egrave_pressed:
			output::instance->putchar(s('è', '7'));
			break;

		case underscore_pressed:
			output::instance->putchar(s('_', '8'));
			break;

		case c_cedilla_pressed:
			output::instance->putchar(s('ç', '9'));
			break;

		case a_grave_pressed:
			output::instance->putchar(s('à', '0'));
			break;

		case right_parenthesis_pressed:
			output::instance->putchar(s(')', '°'));
			break;

		case equals_pressed:
			output::instance->putchar(s('=', '+'));
			break;

		case backspace_pressed:
			output::instance->putchar('\b');
			break;
#pragma endregion

#pragma region second_row
		case tab_pressed:
			output::instance->putchar('\t');
			break;

		case a_pressed:
			output::instance->putchar(s('a', 'A'));
			break;

		case z_pressed:
			output::instance->putchar(s('z', 'Z'));
			break;

		case e_pressed:
			output::instance->putchar(s('e', 'E'));
			break;

		case r_pressed:
			output::instance->putchar(s('r', 'R'));
			break;

		case t_pressed:
			output::instance->putchar(s('t', 'T'));
			break;

		case y_pressed:
			output::instance->putchar(s('y', 'Y'));
			break;

		case u_pressed:
			output::instance->putchar(s('u', 'U'));
			break;

		case i_pressed:
			output::instance->putchar(s('i', 'I'));
			break;

		case o_pressed:
			output::instance->putchar(s('o', 'O'));
			break;

		case p_pressed:
			output::instance->putchar(s('p', 'P'));
			break;

		case circumflex_pressed:
			output::instance->putchar(s('^', '¨'));
			break;

		case dollar_pressed:
			output::instance->putchar(s('$', '£'));
			break;

		case enter_pressed:
			output::instance->putchar('\n');
			break;
#pragma endregion

#pragma region third_row
		case caps_lock_pressed:
			break;

		case q_pressed:
			output::instance->putchar(s('q', 'Q'));
			break;

		case s_pressed:
			output::instance->putchar(s('s', 'S'));
			break;

		case d_pressed:
			output::instance->putchar(s('d', 'D'));
			break;

		case f_pressed:
			output::instance->putchar(s('f', 'F'));
			break;

		case g_pressed:
			output::instance->putchar(s('g', 'G'));
			break;

		case h_pressed:
			output::instance->putchar(s('h', 'H'));
			break;

		case j_pressed:
			output::instance->putchar(s('j', 'J'));
			break;

		case k_pressed:
			output::instance->putchar(s('k', 'K'));
			break;

		case l_pressed:
			output::instance->putchar(s('l', 'L'));
			break;

		case m_pressed:
			output::instance->putchar(s('m', 'M'));
			break;

		case ugrave_pressed:
			output::instance->putchar(s('ù', '%'));
			break;

		case asterisk_pressed:
			output::instance->putchar(s('*', 'µ'));
			break;
#pragma endregion

#pragma region fourth_row
		case left_shift_pressed:
			shift_pressed = true;
			break;

		case less_than_pressed:
			output::instance->putchar(s('<', '>'));
			break;
		case w_pressed:
			output::instance->putchar(s('w', 'W'));
			break;
		case x_pressed:
			output::instance->putchar(s('x', 'X'));
			break;
		case c_pressed:
			output::instance->putchar(s('c', 'C'));
			break;
		case v_pressed:
			output::instance->putchar(s('v', 'V'));
			break;
		case b_pressed:
			output::instance->putchar(s('b', 'B'));
			break;
		case n_pressed:
			output::instance->putchar(s('n', 'N'));
			break;
		case comma_pressed:
			output::instance->putchar(s(',', '?'));
			break;
		case semicolon_pressed:
			output::instance->putchar(s(';', '.'));
			break;
		case colon_pressed:
			output::instance->putchar(s(':', '/'));
			break;
		case exclamation_mark_pressed:
			output::instance->putchar(s('!', '§'));
			break;
		case right_shift_pressed:
			shift_pressed = true;
			break;
#pragma endregion

#pragma region fifth_row
		case left_control_pressed:
			break;

		case left_alt_pressed:
			break;

		case space_pressed:
			output::instance->putchar(' ');
			break;

		default:
			std::printf("Keyboard manager > Unhandled scancode: %x\n", static_cast<uint8_t>(scancode));
			break;
		}
	}
}