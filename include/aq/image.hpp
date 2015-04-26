#ifndef AQ_IMAGE_HPP
#define AQ_IMAG_HPP

#include <aq/types.hpp>



namespace AQ
{

	class Image
	{
		public:
			enum Format
			{
				Format_Grayscale = 1,
				Format_GrayscaleAlpha = 2,
				Format_RGB = 3,
				Format_RGBA = 4,
			};

			Image();
			Image(UInt32 width, UInt32 height, Format format, const UInt8* pixels = nullptr);
			Image(const Image& other);
			Image& operator=(const Image& other);
			~Image();

			bool loadFromFile(const char* filename);
			bool loadFromMemory(UInt32 width, UInt32 height, Format format, const UInt8* pixels);

			inline UInt32 width() const  { return m_width;  }
			inline UInt32 height() const  { return m_height; }

			inline Format format() const { return m_format; }
			inline UInt8* pixelPtr() const { return m_pixels; }

			UInt8* getPixel(UInt32 column, UInt32 row) const;
			void setPixel(UInt32 column, UInt32 row, const UInt32* pixel);


			void flipVertically();
//			void flipHorizontally();
//			void rotateClockwise();
//			void rotateCounterClockwise();

//			void copyRectFromImage(const Image& src, UInt32 srcCol, UInt32 srcRow, UInt32 destCol, UInt32 destRow, UInt32 width, UInt32 height);





//		private:
	//		void setPixels(UInt32 width, UInt32 height, Format format, const UInt8* pixels);

			Format m_format;
			UInt32 m_width;
			UInt32 m_height;
			UInt8* m_pixels;

			

	};



}


#endif