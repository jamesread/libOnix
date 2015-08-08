#include <iostream>
#include <stdint.h>

#define NE 0
#define SE 1
#define SW 2
#define NW 3

class Surface {
	public:
		Surface(int w, int h, char fill);
		Surface(int w, int h);
		Surface(int squareSize);


		void fill(char fillChar);
		void set(int x, int y, char c);
		void set(uint32_t pos, char c);
		void rect(int x, int y, int w, int h, char c);
		int getPos(int x, int y);
		char get(int x, int y);
		char get(int x, int y, char clipChar);
		void hline(int x, int y, int l, char fill);
		void vline(int x, int y, int l, char fill);
		void dline(int x, int y, int l, char fill, int dir);
		void sdline(int x, int y, int diagLength, int straightLength, int span, char diagFill, char straightFill, int dir);

		void border();
		void border(char bchar);
		void border(char vchar, char hchar);
		void border(char vchar, char hchar, char cchar);
		void border(int x, int y, int w, int h);
		void border(int x, int y, int w, int h, char vchar, char hchar, char cchar);
		void text(int x, int y, std::string txt);
		void window(int x, int y, int w, int h);
		void blit(int x, int y, Surface* source);
		void blitQuietly(int x, int y, Surface* source);

		void replace(char find, char replace);

		void row(int row, std::string content);
		void rotate(int degrees);
		void rotate(int x, int y, int deg, char clipChar);

		void shift(int x, int y);

		int getWidth();
		int getHeight(); 

		std::string str();
		std::string rawstr();
	private:
		int w;
		int h;
		
		std::string map;

		bool rangeCheck(int x, int y);
		bool rangeCheck(int x, int y, std::string title);
};
