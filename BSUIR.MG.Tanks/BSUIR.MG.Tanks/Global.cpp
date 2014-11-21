#include "Global.h"
#include "FreeImage\FreeImage.h"
bool createTexture(LPTSTR szFileName, unsigned int &texture)                            // Creates Texture From A Bitmap File
{
      HBITMAP hBMP;                                                                 // Handle Of The Bitmap
      BITMAP      BMP;                                                              // Bitmap Structure

      glGenTextures(1, &texture);                                                 // Create The Texture
      hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

      if (!hBMP)                                                                    // Does The Bitmap Exist?
            return FALSE;                                                           // If Not Return False

      GetObject(hBMP, sizeof(BMP), &BMP);                                           // Get The Object
                                                                                    // hBMP:        Handle To Graphics Object
                                                                                    // sizeof(BMP): Size Of Buffer For Object Information
                                                                                    // &BMP:        Buffer For Object Information

      glPixelStorei(GL_UNPACK_ALIGNMENT, 4);                                        // Pixel Storage Mode (Word Alignment / 4 Bytes)

      // Typical Texture Generation Using Data From The Bitmap
      glBindTexture(GL_TEXTURE_2D, texture);                                      // Bind To The Texture ID
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
      glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

      DeleteObject(hBMP);                                                           // Delete The Object

      return TRUE;                                                                  // Loading Was Successful
}

bool createPNGTexture(LPTSTR szFileName, unsigned int &texture)                            // Creates Texture From A Bitmap File
{
	FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(szFileName, 0), szFileName);

	FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);
	glGenTextures(1, &texture);                                                 // Create The Texture

	glPixelStorei(GL_UNPACK_ALIGNMENT, 8);                                        // Pixel Storage Mode (Word Alignment / 4 Bytes)
	// Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture);                                      // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

	FreeImage_Unload(pImage);

	return TRUE;
}