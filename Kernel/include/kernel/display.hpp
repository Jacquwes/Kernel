#pragma once

#include <cstdint>

namespace Kernel::Display
{
	/// <summary>
	/// Represents the colors that can be used in the console.
	/// </summary>
	enum class Colors : uint8_t
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGrey = 7,
		DarkGrey = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		LightBrown = 14,
		White = 15,
	};

	/// <summary>
	/// 
	/// </summary>
	struct ColorSet
	{
		Colors Foreground;
		Colors Background;
	};

	static const ColorSet DefaultColorSet = { Colors::LightGrey, Colors::Black };

	/// <summary>
	/// Serves as a wrapper for the video memory.
	/// </summary>
	class Console
	{
	public:
		Console() = default;
		~Console() = default;

		/// <summary>
		/// Replaces all characters on the screen with spaces.
		/// </summary>
		void ClearScreen();

		/// <summary>
		/// Prints a character to the screen.
		/// </summary>
		/// <param name="c">The character to print.</param>
		/// <param name="colorSet">The color set to use.</param>
		/// <param name="blink">Whether or not the character should blink.</param>
		void Print(char const& c, ColorSet const& colorSet = DefaultColorSet, bool const& blink = false);

		/// <summary>
		/// Prints a character to the screen at the specified position.
		/// </summary>
		/// <param name="c">The character to print.</param>
		/// <param name="positionX">The position of the character on the x-axis.</param>
		/// <param name="positionY">The position of the character on the y-axis.</param>
		/// <param name="colorSet">The color set to use.</param>
		/// <param name="blink">Whether or not the character should blink.</param>
		void Print(char const& c, uint8_t positionX, uint8_t positionY, ColorSet const& colorSet = DefaultColorSet, bool const& blink = false);

		static const uint8_t Height = 25;
		static const uint8_t Width = 80;

	private:
		uint16_t* videoMemory = (uint16_t*)0xb8000;
		uint8_t cursorX = 0;
		uint8_t cursorY = 0;
	};

	void Console::ClearScreen()
	{
		for (uint8_t y = 0; y < Height; y++)
			for (uint8_t x = 0; x < Width; x++)
			{
				Print(' ');
			}

		cursorX = 0;
		cursorY = 0;
	}

	void Console::Print(char const& c, ColorSet const& colorSet, bool const& blink)
	{
		videoMemory[(cursorY * Width) + cursorX] = c | (static_cast<uint8_t>(colorSet.Foreground) << 8) | (static_cast<uint8_t>(colorSet.Background) << 12) | (blink << 14);

		cursorX++;
		if (cursorX >= Width)
		{
			cursorX = 0;
			cursorY++;
		}
	}


	void Console::Print(char const& c, uint8_t positionX, uint8_t positionY, ColorSet const& colorSet, bool const& blink)
	{
		cursorX = positionX;
		cursorY = positionY;

		Print(c, colorSet, blink);
	}
}