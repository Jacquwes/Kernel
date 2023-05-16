#include "keyboard_manager.h"

#include "output.h"
#include "logger.h"

namespace kernel
{
	keyboard_manager* keyboard_manager::instance = nullptr;

	keyboard_manager::keyboard_manager()
	{
		instance = this;

		logger::log(info, "Keyboard manager > Initialized.");
	}

	void keyboard_manager::handle_scancode(keyboard_scancodes::keyboard_scancode const& scancode)
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
		case backtick_pressed:
			output::instance->putchar('`');
			break;

		case one_pressed:
			output::instance->putchar(s('1', '!'));
			break;

		case two_pressed:
			output::instance->putchar(s('2', '"'));
			break;

		case three_pressed:
			output::instance->putchar(s('3', '£'));
			break;

		case four_pressed:
			output::instance->putchar(s('4', '$'));
			break;

		case five_pressed:
			output::instance->putchar(s('5', '%'));
			break;

		case six_pressed:
			output::instance->putchar(s('6', '^'));
			break;

		case seven_pressed:
			output::instance->putchar(s('7', '&'));
			break;

		case eight_pressed:
			output::instance->putchar(s('8', '*'));
			break;

		case nine_pressed:
			output::instance->putchar(s('9', '('));
			break;

		case zero_pressed:
			output::instance->putchar(s('0', ')'));
			break;

		case minus_pressed:
			output::instance->putchar(s('-', '_'));
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

		case q_pressed:
			output::instance->putchar(s('q', 'Q'));
			break;

		case w_pressed:
			output::instance->putchar(s('w', 'W'));
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

		case left_bracket_pressed:
			output::instance->putchar(s('[', '{'));
			break;

		case right_bracket_pressed:
			output::instance->putchar(s(']', '}'));
			break;

		case enter_pressed:
			output::instance->putchar('\n');
			break;
#pragma endregion

#pragma region third_row
		case caps_lock_pressed:
			break;

		case a_pressed:
			output::instance->putchar(s('a', 'A'));
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

		case semi_colon_pressed:
			output::instance->putchar(s(';', ':'));
			break;

		case single_quote_pressed:
			output::instance->putchar(s('\'', '@'));
			break;

			//case hash_pressed:
				//output::instance->putchar(s('#', '~'));
				//break;
#pragma endregion

#pragma region fourth_row
		case left_shift_pressed:
			shift_pressed = true;
			break;

		case backslash_pressed:
			output::instance->putchar(s('\\', '|'));
			break;
		case z_pressed:
			output::instance->putchar(s('z', 'Z'));
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
		case m_pressed:
			output::instance->putchar(s('m', 'M'));
			break;
		case comma_pressed:
			output::instance->putchar(s(',', '<'));
			break;
		case dot_pressed:
			output::instance->putchar(s('.', '>'));
			break;
		case slash_pressed:
			output::instance->putchar(s('/', '?'));
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
			logger::log(error, "Keyboard manager > Unhandled scancode: %x", static_cast<uint8_t>(scancode));
			break;
		}
	}
}