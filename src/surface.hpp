#include <iostream>
#include <stdint.h>

class surface {
	public:
		surface(int w, int h, char fill);

		void fill(char fillChar);
		void set(int x, int y, char c);
		void set(uint32_t pos, char c);
		void rect(int x, int y, int w, int h, char c);
		int getPos(int x, int y);
		char get(int x, int y);
		char get(int x, int y, char clipChar);
		void hline(int x, int y, int l, char fill);
		void vline(int x, int y, int l, char fill);
		void border(char bchar);
		void border(char vchar, char hchar);
		void border(int x, int y, int w, int h);
		void border(int x, int y, int w, int h, char vchar, char hchar);
		void window(int x, int y, int w, int h);
		void blit(int x, int y, surface* source);
		void blitQuietly(int x, int y, surface* source);

		void replace(char find, char replace);

		void row(int row, std::string content);
		void rot(int x, int y, int origin, char clipChar);

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
