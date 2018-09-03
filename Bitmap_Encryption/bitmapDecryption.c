#include <stdio.h>
#include "bitmap.h"

struct BitmpaFileHeader bitmapHeader;//set a bitmap header
struct BitmapInfo bitmapInfo;//set bitmap info


int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		return 0;
	}

	char *filename = argv[1];//get filename

	FILE *bitmapreader;
	bitmapreader = fopen(filename, "rb");

	if(bitmapreader == NULL)
	{
		printf("Can not open the file: %s\n", filename);
		return 0;
	}


	fread((void*)&bitmapHeader.bitmapFlag_B, 1, 1, bitmapreader);
	fread((void*)&bitmapHeader.bitmapFlag_M, 1, 1, bitmapreader);

	//check the file flag
	if(bitmapHeader.bitmapFlag_B != 'B' || bitmapHeader.bitmapFlag_M != 'M')
	{
		printf("This is not a bitmap file.\n");
		fclose(bitmapreader);
		return 0;
	}

	//read the file header
	fread((void*)&bitmapHeader.bitmapFileSize, 4, 1, bitmapreader);//get the file size
	fread((void*)&bitmapHeader.Reserved1, 2, 1, bitmapreader);
	fread((void*)&bitmapHeader.Reserved2, 2, 1, bitmapreader);
	fread((void*)&bitmapHeader.bitsOffset, 4, 1, bitmapreader);//get the data location

	//read the bitmap info
	fread((void*)&bitmapInfo.bitmapInfoSize, 4, 1, bitmapreader);//get the length this struct 
	fread((void*)&bitmapInfo.bitmapWidth, 4, 1, bitmapreader);//get width
	fread((void*)&bitmapInfo.bitmapHeight, 4, 1, bitmapreader);//get height
	fread((void*)&bitmapInfo.Planes, 2, 1, bitmapreader);
	fread((void*)&bitmapInfo.bitCount, 2, 1, bitmapreader);//get bitcount
	fread((void*)&bitmapInfo.bitmapCompression, 4, 1, bitmapreader);//get compression type
	fread((void*)&bitmapInfo.bitmapSizeImage, 4, 1, bitmapreader);//get the length of bits
	fread((void*)&bitmapInfo.xPelsPerMeter, 4, 1, bitmapreader);
	fread((void*)&bitmapInfo.yPelsPerMeter, 4, 1, bitmapreader);
	fread((void*)&bitmapInfo.colorUsed, 4, 1, bitmapreader);
	fread((void*)&bitmapInfo.colorImportant, 4, 1, bitmapreader);

	//check file if it have message
	if(bitmapHeader.Reserved1 != 99 || bitmapHeader.Reserved2 != 99)
	{
		printf("This is not a encrypted file.\n");
		fclose(bitmapreader);
		return 0;
	}


	int i = 0;
	unsigned char ctemp_fromFile, ctemp_fromMsg;
	printf("get message: \n");
	while(!feof(bitmapreader))
	{
		ctemp_fromMsg = 0x00;
		for (i = 0; i < 8; i++)
		{
			fread((void*)&ctemp_fromFile, 1, 1, bitmapreader);
			ctemp_fromFile = ctemp_fromFile & 0x01;
			ctemp_fromMsg = ctemp_fromMsg | (ctemp_fromFile << (7-i));
		}
		printf("%c", ctemp_fromMsg);
		if(ctemp_fromMsg == '\0')
		{
			printf("\n");
			return 0;
		}
	}
	return 0;

}