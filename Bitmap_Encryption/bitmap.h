

struct BitmpaFileHeader
{
	char bitmapFlag_B;
	char bitmapFlag_M;
	int bitmapFileSize;
	short Reserved1;//have no use -_-||
	short Reserved2;
	int bitsOffset;//where the bit data begin
};

struct BitmapInfo
{
	int bitmapInfoSize;//the length of this struct, it always 40
	int bitmapWidth;
	int bitmapHeight;
	short Planes;//it always 1.(I realy do not know why...)
	short bitCount;//the lenght of every bit point(could be one of 1, 4, 8, 24)
	int bitmapCompression;//0 mean have not compressed,and it maybe 1 or 2
	int bitmapSizeImage;//the size of bit points
	int xPelsPerMeter;
	int yPelsPerMeter;
	int colorUsed;//can be 0
	int colorImportant;//can be 0
};
