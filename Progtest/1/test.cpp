#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */

/**
 * @brief Get the Uint 16 of object
 * 
 * @param input1 Left 8 Bits
 * @param input2 Right 8 Bits
 * @return uint16_t 16 Bit int from inputs
 */
uint16_t GetUint16( const char input1, const char input2 ){
  uint16_t res = ( int )( uint8_t )input1 << 8;
  res += ( int )( uint8_t )input2;
  return res;
}

/**
 * @brief Image class for manipulation of image data
 * 
 */
class Image {
  private:    
    uint16_t _w;
    uint16_t _h;
    int _fileLenght;
    int _sampleLenght;
    char * _memHeader;
    char * _memData;    
  public:
    /**
     * @brief Construct a new Image object
     * 
     */
    Image() { 
      _w = 0; 
      _h = 0; 
      _fileLenght = 0;
      _sampleLenght = 0;
      _memHeader = NULL; 
      _memData = NULL; 
    }

    /**
     * @brief Method for parsing loaded header of file
     * 
     * @return true Header was parsed ok
     * @return false Error in header
     */
    bool ParseHeader(){ 
      uint16_t type = GetUint16( _memHeader[ 0 ], _memHeader[ 1 ] );
      uint16_t format = 0;

      if( type != ENDIAN_LITTLE && type != ENDIAN_BIG )
        return false;
        
      if( type == ENDIAN_LITTLE ){
        uint16_t w = GetUint16( _memHeader[ 3 ], _memHeader[ 2 ] );
        if(w <= 0)
          return false;
        _w = w;

        uint16_t h = GetUint16( _memHeader[ 5 ], _memHeader[ 4 ] );
        if( h <= 0 )
          return false;
          
        _h = h;    

        format = GetUint16( _memHeader[ 7 ], _memHeader[ 6 ] );
      } else{
        uint16_t w = GetUint16( _memHeader[ 2 ], _memHeader[ 3 ] );
        if( w <= 0 )
          return false;
        _w = w;

        uint16_t h = GetUint16( _memHeader[ 4 ], _memHeader[ 5 ] );
        if( h <= 0 )
          return false;
        _h = h;    

        format = GetUint16( _memHeader[ 6 ], _memHeader[ 7 ] );
      }

      int channels = 0;
      int bytes = 0;

      //Channels check
      if( ( format & 3 ) == 0 ){
        channels = 1;
      } else if( ( format & 3 ) == 2 ){
        channels = 3;
      } else if( ( format & 3 ) == 3 ){
        channels = 4;
      } else{
        return false;
      }

      //Num of Bytes check
      if( ( ( format >> 2 ) & 7 ) == 0 ){
        return false;
      } else if( ( ( format >> 2 ) & 7 ) == 3 ){
        bytes = 1;
      } else if( ( ( format >> 2 ) & 7 ) == 4 ){
        bytes = 2;
      } else{
        return false;
      }

      _sampleLenght = channels * bytes;
      
      return true;
    }

    /**
     * @brief Method for loading image data, which loads header and content of image
     * 
     * @param src Filepath of image
     * @return true Image was loaded and stored in object
     * @return false Image loading failed
     */
    bool LoadImage(const char * src){
      
      ifstream inp ( src, ios_base::binary );

      if( !inp.is_open() || !inp.good() ){
        inp.close();
        return false;
      }

      inp.seekg ( 0, inp.end );
      _fileLenght = inp.tellg();
      inp.seekg ( 0, inp.beg );

      if( !inp  || !inp.good() ){
        inp.close();
        return false;
      }

      //Header lenght check
      if( _fileLenght < 8 ){
        inp.close();
        return false;
      }

      _memHeader = new char [ 8 ];
      inp.read( _memHeader, 8 );

      if( !inp || !inp.good() ){
        inp.close();
        delete[] _memHeader;
        return false;
      }

      cout << "Parsing header: " << src << endl;

      if( !ParseHeader() ){
        inp.close();
        return false;
      }

      cout << "Parsed header: " << src << endl;
      cout << left << setw(10) << "Width" << setw(10) << "Height" << setw(15) << "Sample Bytes" << setw(15) << "File Bytes" << endl;
      cout << left << setw(10) << _w << setw(10) << _h << setw(15) << _sampleLenght << setw(15) << _fileLenght << right << endl;

      if(_w <= 0 || _h <= 0){
        inp.close();
        return false;
      }
      
      int checkSum = _fileLenght - 8 - _w * _h * _sampleLenght;
      cout << "Checksum: " << checkSum  << endl;

      //Checksum validation
      if( checkSum != 0 ){
        inp.close();
        return false;
      }

      _memData = new char [ _fileLenght - 8 ];
      inp.read( _memData, _fileLenght - 8 );

      if( !inp || !inp.good() ){
        inp.close();
        return false;
      }

      inp.close();
      return true;
    }

    /**
     * @brief Method for saving image to disk
     * 
     * @param dst Destination file path
     * @return true Image was saved 
     * @return false Image saving failed
     */
    bool SaveImage( const char * dst ) const{
      ofstream out ( dst, ios_base::binary );
      
      if( !out.is_open() || !out.good() ){
        out.close();
        return false;
      }

      out.write( _memHeader, 8 );
      out.write( _memData, _fileLenght - 8 );

      if( !out || !out.good() ){
        out.close();
        return false;
      }

      out.close();
      return true;
    }

    /**
     * @brief Get the pointer to start of datablock at specific position
     * 
     * @param j x position of image
     * @param i y position of image
     * @return char* Pointer to start of datablock
     */
    char * GetData( int j, int i ){
      return &_memData[ i * _w * _sampleLenght + j * _sampleLenght ];
    } 

    /**
     * @brief Flipping image horizontaly (by x axis)
     * 
     */
    void FlipHorizontal(){
      char * tmp = new char[ _sampleLenght ];
      for( int x = 0; x < _w / 2; x++ ){
        for( int y = 0; y < _h; y++ ){
          memcpy( tmp, GetData( x, y ), _sampleLenght );
          memcpy( GetData( x, y ), GetData( _w - x - 1, y ), _sampleLenght );
          memcpy( GetData( _w - x - 1, y ), tmp, _sampleLenght );          
        }
      }
      delete[] tmp;
    }

    /**
     * @brief Flipping image verticaly (by y axis)
     * 
     */
    void FlipVertical(){
      char * tmp = new char[ _sampleLenght ];
      for( int x = 0; x < _w; x++ ){
        for( int y = 0; y < _h / 2; y++ ){
          memcpy( tmp, GetData(x,y), _sampleLenght);
          memcpy( GetData( x, y ), GetData( x, _h - y - 1 ), _sampleLenght );
          memcpy( GetData( x, _h - y - 1 ), tmp, _sampleLenght );          
        }
      }
      delete[] tmp;
    }

    /**
     * @brief Destructor of the Image object
     * 
     */
    ~Image(){
      if( _memHeader != NULL )
        delete[] _memHeader;
      if( _memData != NULL )
        delete[] _memData;
    }
};

/**
 * @brief Flipping function
 * 
 * @param srcFileName Path to source image
 * @param dstFileName Path for saving result image
 * @param flipHorizontal Flipping horizontal 
 * @param flipVertical Flipping vertical
 * @return true Image was loaded, parsed, flipped by parameters and saved 
 * @return false Image failed to do either load or save
 */
bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{  
  cout << "Loading Image" << endl;

  Image img = Image();
  if( !img.LoadImage( srcFileName ) )
    return false;

  cout << "Loaded Image" << endl;

  cout << "Flipping Image" << endl;

  if( flipHorizontal )
    img.FlipHorizontal();
  if( flipVertical )
    img.FlipVertical();

  cout << "Flipped Image" << endl;
  
  cout << "Saving Image" << endl;

  if( !img.SaveImage( dstFileName ) )
    return false;

  cout << "Saved Image" << endl;
  cout << "----------" << endl;

  return true;
}

#ifndef __PROGTEST__
/**
 * @brief Testing method for two files using memcmp
 * 
 * @param fileName1 First file
 * @param fileName2 Second file
 * @return true Files are identical
 * @return false Files are't identical
 */
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
  char * i1;
  char * i2;
  
  ifstream inp1 ( fileName1, ios_base::binary );
  ifstream inp2 ( fileName2, ios_base::binary );

  inp1.seekg ( 0, inp1.end );
  int l1 = inp1.tellg();
  inp1.seekg ( 0, inp1.beg );
  
  inp2.seekg ( 0, inp2.end );
  int l2 = inp2.tellg();
  inp2.seekg ( 0, inp2.beg );

  if(l1 != l2){
    return false;
  }

  i1 = new char [l1];
  inp1.read(i1, l1);
  inp1.close();

  i2 = new char [l2];
  inp2.read(i2, l2);
  inp2.close();

  if(memcmp(i1, i2, l1)){
    delete[] i1;
    delete[] i2;
    return false;
  }
  
  delete[] i1;
  delete[] i2;
  return true;
}

int main ( void )
{
  //Test asserts

  assert ( flipImage ( "input_00.img", "output_00.img", true, false )
           && identicalFiles ( "output_00.img", "ref_00.img" ) );
  
  assert ( flipImage ( "input_01.img", "output_01.img", false, true )
           && identicalFiles ( "output_01.img", "ref_01.img" ) );

  assert ( flipImage ( "input_02.img", "output_02.img", true, true )
           && identicalFiles ( "output_02.img", "ref_02.img" ) );

  assert ( flipImage ( "input_03.img", "output_03.img", false, false )
           && identicalFiles ( "output_03.img", "ref_03.img" ) );

  assert ( flipImage ( "input_04.img", "output_04.img", true, false )
           && identicalFiles ( "output_04.img", "ref_04.img" ) );

  assert ( flipImage ( "input_05.img", "output_05.img", true, true )
           && identicalFiles ( "output_05.img", "ref_05.img" ) );

  assert ( flipImage ( "input_06.img", "output_06.img", false, true )
           && identicalFiles ( "output_06.img", "ref_06.img" ) );

  assert ( flipImage ( "input_07.img", "output_07.img", true, false )
           && identicalFiles ( "output_07.img", "ref_07.img" ) );

  assert ( flipImage ( "input_08.img", "output_08.img", true, true )
           && identicalFiles ( "output_08.img", "ref_08.img" ) );

  assert ( flipImage ( "input_10.img", "output_10.img", false, true )
           && identicalFiles ( "output_10.img", "ref_10.img" ) );
  
  
  assert ( !flipImage ( "hodn.img", "output_hodn.img", false, true ));

  assert( ! flipImage("tst", "out", true, true));

  assert ( ! flipImage ( "input_09.img", "output_09.img", true, false ) );

  // extra inputs (optional & bonus tests)
  assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
           && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
  assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
           && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
  assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
           && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
  assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
           && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
  assert ( flipImage ( "extra_input_04.img", "extra_out_04.img", true, false )
           && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
  assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
           && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
  assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
           && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
  assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
           && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );

  /*
  assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, false )
           && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
  assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
           && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
  assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
           && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
  assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
           && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
  */
  return 0;
}
#endif /* __PROGTEST__ */
