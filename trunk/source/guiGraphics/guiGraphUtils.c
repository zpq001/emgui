
#include "stdint.h"
#include "guiConfig.h"
#include "guiGraphCommon.h"
#include "guiGraphUtils.h"




//==============================================================//
// Fills buffer with specified value
//	Parameters:
//		uint8_t value							- value to fill with
//==============================================================//
void guiGraph_FillBuffer(uint8_t value)
{
    uint16_t i;
    for (i=0;i<DISPLAY_BUFFER_SIZE;i++)
    {
        display_buffer[i] = value;
    }
}




//==============================================================//
// Modify single pixel
//	Parameters:
//		uint8_t x_pos							- pixel x coordinate
//		uint8_t y_pos							- pixel y coordinate
//		uint8_t mode							- pixel output mode, PIXEL_OFF, PIXEL_ON, PIXEL_XOR
//==============================================================//
void guiGraph_PutPixel (uint8_t x_pos, uint8_t y_pos, uint8_t mode)
{
int16_t buffer_index;
uint8_t offset, data;
    // Get byte index
    #ifdef SOFT_HORIZ_REV
        buffer_index = (y_pos / 8)*DISPLAY_XSIZE + DISPLAY_XSIZE - 1 - x_pos;
    #else
        buffer_index = (y_pos / 8)*DISPLAY_XSIZE + x_pos;
    #endif
    // Get bit offset
  offset  = y_pos % 8;
  data = (uint8_t)display_buffer[buffer_index];
  if ( mode == PIXEL_OFF ) data &= ( ~( 0x01 << offset ) );
      else if ( mode == PIXEL_ON ) data |= ( 0x01 << offset );
           else if ( mode  == PIXEL_XOR ) data ^= ( 0x01 << offset );
  display_buffer[buffer_index] = data;
}



void guiGraph_PutHorLine(uint8_t x_pos, uint8_t y_pos, uint8_t length, uint8_t mode)
{
  uint8_t cnt_done=0;
  while (cnt_done<length)
    guiGraph_PutPixel(x_pos+cnt_done++,y_pos,mode);
}

void guiGraph_PutVertLine(uint8_t x_pos, uint8_t y_pos, uint8_t length, uint8_t mode)
{
  uint8_t cnt_done=0;
  while (cnt_done<length)
    guiGraph_PutPixel(x_pos,y_pos+cnt_done++,mode);
}





//==============================================================//
// Print an image at specified area
// Parameters:
//		uint8_t* img					- pointer to image
//          if img = 0, area is filled with color, depending on mode[0] bit
//		uint8_t x_pos					- horizontal image position, pixels
//		uint8_t y_pos					- vertical image position, pixels
//		uint8_t width					-	image width
//		uint8_t height				- image height
//      mode[0]:
//          IMAGE_MODE_NORM - normal image,   if img = 0, image is treated as all 1's
//          IMAGE_MODE_INVERSE - inversed image, if img = 0, image is treated as all 0's
//      mode[2:1]:
//          PIXEL_MODE_REWRITE - output rewrites previous buffer content
//          PIXEL_MODE_OR  - output is ORed with previous buffer content
//          PIXEL_MODE_AND - output is ANDed with previous buffer content
//          PIXEL_MODE_XOR - output is XORed with previous buffer content
//
// If defined SOFT_HORIZ_REV, function will put image reversed
//==============================================================//
void guiGraph_DrawImage(uint8_t* img, uint8_t x_pos, uint8_t y_pos, uint8_t width, uint8_t height, uint8_t mode)
{
	uint16_t vertical_bits_remain, counter_inc;
	uint16_t picture_index, buffer_index;
	uint16_t start_buffer_index;
	uint16_t i;
	uint16_t img_shift;
	uint8_t mask, temp;
	uint8_t offset = y_pos % 8;
    uint8_t img_inv_mask = (mode & 0x01) ? 0xFF : 0x00;
    mode &= 0xFE;

	#ifdef SOFT_HORIZ_REV
        start_buffer_index = (y_pos / 8)*DISPLAY_XSIZE + DISPLAY_XSIZE - 1 - x_pos;
	#else
        start_buffer_index = (y_pos / 8)*DISPLAY_XSIZE + x_pos;
	#endif
	
	//-------------//
	
	// X-loop
	for (i=0;i<width;i++)
	{
			img_shift = 0;
			picture_index = i;
			#ifdef SOFT_HORIZ_REV
				buffer_index =  start_buffer_index - i;
			#else
				buffer_index =  start_buffer_index + i;
			#endif
			vertical_bits_remain = height;
			mask = -(1<<offset); 
			
			if (offset + height < 8 )
			{
				temp = (1<<(offset + height))-1;
				mask &= temp;
				counter_inc = height;
			}
			else
			{
				counter_inc = 8-offset;
			}
		

			// Y-loop
			while(vertical_bits_remain)
			{			  
                if (img != 0)
                    temp = img[picture_index];                  // get image byte
                else
                    temp = 0xFF;
                temp ^= img_inv_mask;
				img_shift |= temp << offset;					// add shifted value to the 16-bit accumulator
		
                temp = (uint8_t)display_buffer[buffer_index];	// get old value

                if (!(mode & 0x2))
                    temp &= ~mask;  							// clear used bits

                if (!(mode & 0x4))
                    temp |= (img_shift & mask);                 // NORMAL or ORed
                else if (!(mode & 0x8))
                    temp &= (img_shift | ~mask);                // ANDed
                else
                    temp ^= (img_shift & mask);                 // XORed


                display_buffer[buffer_index] = temp;			// write new value back
		
				img_shift = img_shift >> 8;						// shift 16-bit register
                buffer_index += DISPLAY_XSIZE;
				picture_index += width;	
			
				vertical_bits_remain -= counter_inc;
				if (vertical_bits_remain >= 8)
					counter_inc = 8;
				else
					counter_inc = vertical_bits_remain;	
				mask = (1 << counter_inc)-1;
							
			}
	}
}


