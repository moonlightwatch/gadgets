#include <stdio.h>
#include "bitmap.h"

struct BitmpaFileHeader bitmapHeader;//set a bitmap header
struct BitmapInfo bitmapInfo;//set bitmap info


int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		return 0;
	}

	char *filename = argv[1];//get the filename

	//set the file pointer
	FILE *bitmapreader;
	bitmapreader = fopen(filename, "rb");

	//check the file pointer
	if(bitmapreader == NULL)
	{
		printf("Can not open file %s\n", filename);
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

	//check the bitCount
	if(bitmapInfo.bitCount < 24)
	{
		printf("The BitConut(%d) of this file is not enough.", bitmapInfo.bitCount);
		fclose(bitmapreader);
		return 0;
	}

	printf("This image can encrypt %dkb length data\n", bitmapInfo.bitmapSizeImage/8/1024);

	char *messagefile = argv[2];//get the message
	FILE *messagereader;
	messagereader = fopen(messagefile, "rb");
	if(messagereader == NULL)
	{
		printf("Can not open the message file.\n");
		fclose(bitmapreader);
		return 0;
	}
	//check the size of file
	fseek(messagereader, 0, SEEK_END);
	long filesize = ftell(messagereader);
	fclose(messagereader);
	if(filesize > (bitmapInfo.bitmapSizeImage/8))
	{
		printf("The message file is too big.\n");
		fclose(bitmapreader);
		return 0;
	}
	messagereader = fopen(messagefile, "rb");


	FILE *bitmapwriter;//file writer pointer

	bitmapwriter = fopen("new.bmp","wr");//open a file

	//check the file
	if(bitmapwriter == NULL)
	{
		printf("Can not open a new file %s\n", filename);
		fclose(bitmapreader);
		return 0;
	}

	//write the bitmapfileheader
	short flag = 99;
	fwrite((void*)&bitmapHeader.bitmapFlag_B, 1, 1, bitmapwriter);
	fwrite((void*)&bitmapHeader.bitmapFlag_M, 1, 1, bitmapwriter);
	fwrite((void*)&bitmapHeader.bitmapFileSize, 4, 1, bitmapwriter);
	fwrite((void*)&flag, 2, 1, bitmapwriter);//make a special flag
	fwrite((void*)&flag, 2, 1, bitmapwriter);
	fwrite((void*)&bitmapHeader.bitsOffset, 4, 1, bitmapwriter);

	//write the bitmap info
	fwrite((void*)&bitmapInfo.bitmapInfoSize, 4, 1, bitmapwriter);//get the length this struct 
	fwrite((void*)&bitmapInfo.bitmapWidth, 4, 1, bitmapwriter);//get width
	fwrite((void*)&bitmapInfo.bitmapHeight, 4, 1, bitmapwriter);//get height
	fwrite((void*)&bitmapInfo.Planes, 2, 1, bitmapwriter);
	fwrite((void*)&bitmapInfo.bitCount, 2, 1, bitmapwriter);//get bitcount
	fwrite((void*)&bitmapInfo.bitmapCompression, 4, 1, bitmapwriter);//get compression type
	fwrite((void*)&bitmapInfo.bitmapSizeImage, 4, 1, bitmapwriter);//get the length of bits
	fwrite((void*)&bitmapInfo.xPelsPerMeter, 4, 1, bitmapwriter);
	fwrite((void*)&bitmapInfo.yPelsPerMeter, 4, 1, bitmapwriter);
	fwrite((void*)&bitmapInfo.colorUsed, 4, 1, bitmapwriter);
	fwrite((void*)&bitmapInfo.colorImportant, 4, 1, bitmapwriter);

	//write source and message to new file
	unsigned char ctemp_fromFile, ctemp_fromMsg, ctemp;
	int j = 0;
	while(!feof(bitmapreader))
	{
		fread((void*)&ctemp, 1, 1, messagereader);
		if(!feof(messagereader))
		{
			for(j=0; j<8; j++)
			{
				ctemp_fromMsg = ctemp;
				fread((void*)&ctemp_fromFile, 1, 1, bitmapreader);
				ctemp_fromFile = ctemp_fromFile | 0x01;
				ctemp_fromMsg = ctemp_fromMsg >> (7-j);
				ctemp_fromMsg = ctemp_fromMsg & 0x01;
				ctemp_fromMsg = ctemp_fromMsg | 0xfe;
				ctemp_fromFile = ctemp_fromFile & ctemp_fromMsg;
				fwrite((void*)&ctemp_fromFile, 1, 1, bitmapwriter);
			}
		}
		else
		{
			fread((void*)&ctemp_fromFile, 1, 1, bitmapreader);
			ctemp_fromFile = ctemp_fromFile & 0xfe;
			fwrite((void*)&ctemp_fromFile, 1, 1, bitmapwriter);
		}
	} 
	fclose(bitmapwriter);
	fclose(bitmapreader);
	printf("Finish encrypt.\n");

	return 0;
}
