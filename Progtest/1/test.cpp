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

class Pixel {
  public:
    Pixel();
    void Set(int r, int g, int b, int a);
    int GetR() {return _r;};
    int GetG() {return _g;};
    int GetB() {return _b;};
    int GetA() {return _a;};
    static bool Compare(Pixel & a, Pixel & b);
  private:
    int _r;
    int _g;
    int _b;
    int _a;
};

Pixel::Pixel(){
  _r = 0;
  _g = 0;
  _b = 0;
  _a = 0;
}

void Pixel::Set(int r, int g, int b, int a){
  _r = r;
  _g = g;
  _b = b;
  _a = a;
}

bool Pixel::Compare(Pixel & a, Pixel & b){
  if(a._a != b._a || a._b != b._b || a._g != b._g || a._r != b._r)
    return false;
  return true;
}


int GetInt8(const char m1){
  return (int)m1;
}

uint16_t GetUint16(const char m1, const char m2){
  uint16_t res = (uint16_t)m1 << 8;
  res += (uint16_t)m2;
  return res;
}

char GetSCharUint16(uint16_t x){
  return (x >> 8);
}

char GetFCharUint16(uint16_t x){
  return x;
}

class Image {
  private:
    const uint16_t ENDIAN_LITTLE_G1 =     0x0000;
    const uint16_t ENDIAN_LITTLE_G8 =     0x000c;
    const uint16_t ENDIAN_LITTLE_G16 =    0x0010;
    const uint16_t ENDIAN_LITTLE_RGB1 =   0x0002;
    const uint16_t ENDIAN_LITTLE_RGB8 =   0x000e;
    const uint16_t ENDIAN_LITTLE_RGB16 =  0x0012;
    const uint16_t ENDIAN_LITTLE_RGBA1 =  0x0003;
    const uint16_t ENDIAN_LITTLE_RGBA8 =  0x000f;
    const uint16_t ENDIAN_LITTLE_RGBA16 = 0x0013;
    
    Pixel ** _bitmap;
    uint16_t _w;
    uint16_t _h;
    uint16_t _wFormat;
    int _channels;
    int _bits;
    uint16_t _type;
    int _fileLenght;
    char * memblock;
  public:
    Image() { _w = 0; _h = 0; _channels = 0; _bits = 0; _type = 0; memblock = NULL; _bitmap = NULL; };
    bool LoadHeader(const char * memblock);
    bool LoadImage(const char * src);
    bool SaveImage(const char * dst) const;
    void FlipHorizontal();
    void FlipVertical();
    void Print() const;
    static bool Compare(Image & img1, Image & img2);
    ~Image();
};


bool Image::LoadHeader(const char * memblock){
  uint16_t type = GetUint16(memblock[0], memblock[1]);
  if(type != ENDIAN_LITTLE && type != ENDIAN_BIG)
    return false;
  _type = type;
  if(type == ENDIAN_LITTLE){

    uint16_t w = GetUint16(memblock[3], memblock[2]);
    if(w <= 0)
      return false;
    _w = w;

    uint16_t h = GetUint16(memblock[5], memblock[4]);
    if(h <= 0)
      return false;
    _h = h;    

    uint16_t tmp = GetUint16(memblock[7], memblock[6]);
    if(tmp == ENDIAN_LITTLE_G1)
    {
      _channels = 1;
      _bits = 1;
    }else if(tmp == ENDIAN_LITTLE_G8)
    {
      _channels = 1;
      _bits = 8;
    }else if(tmp == ENDIAN_LITTLE_G16)
    {
      _channels = 1;
      _bits = 16;
    }else if(tmp == ENDIAN_LITTLE_RGB1)
    {
      _channels = 3;
      _bits = 1;
    }else if(tmp == ENDIAN_LITTLE_RGB8)
    {
      _channels = 3;
      _bits = 8;
    }else if(tmp == ENDIAN_LITTLE_RGB16)
    {
      _channels = 3;
      _bits = 16;
    }else if(tmp == ENDIAN_LITTLE_RGBA1)
    {
      _channels = 4;
      _bits = 1;
    }else if(tmp == ENDIAN_LITTLE_RGBA8)
    {
      _channels = 4;
      _bits = 8;
    }else if(tmp == ENDIAN_LITTLE_RGBA16)
    {
      _channels = 4;
      _bits = 16;
    }else{
      return false;
    }
    _wFormat = GetUint16(memblock[7], memblock[6]);
  }else{
    return false;
  }

  return true;
}

void Image::FlipHorizontal(){
  int r = 0;
  int g = 0;
  int b = 0;
  int a = 0;
  for(int y = 0; y < _h; y++){
    for(int x = 0; x < ceil(_w/2); x++){
      
       r = _bitmap[x][y].GetR();
       g = _bitmap[x][y].GetG();
       b = _bitmap[x][y].GetB();
       a = _bitmap[x][y].GetA();
      _bitmap[x][y].Set(_bitmap[_w-x-1][y].GetR(),_bitmap[_w-x-1][y].GetG(),_bitmap[_w-x-1][y].GetB(),_bitmap[_w-x-1][y].GetA());
      _bitmap[_w-x-1][y].Set(r,g,b,a);
    }
  }
}

void Image::FlipVertical(){
  int r = 0;
  int g = 0;
  int b = 0;
  int a = 0;
  for(int y = 0; y < ceil(_h/2); y++){
    for(int x = 0; x < _w; x++){
      
       r = _bitmap[x][y].GetR();
       g = _bitmap[x][y].GetG();
       b = _bitmap[x][y].GetB();
       a = _bitmap[x][y].GetA();
      _bitmap[x][y].Set(_bitmap[x][_h-y-1].GetR(),_bitmap[x][_h-y-1].GetG(),_bitmap[x][_h-y-1].GetB(),_bitmap[x][_h-y-1].GetA());
      _bitmap[x][_h-y-1].Set(r,g,b,a);
    }
  }
}

void Image::Print() const{
  for(int y = 0; y < _h; y++){
    for(int x = 0; x < _w; x++){
      cout << setw(3) << _bitmap[x][y].GetR();
      cout << setw(2) << _bitmap[x][y].GetG();
      cout << setw(2) << _bitmap[x][y].GetB();
      cout << setw(2) << _bitmap[x][y].GetA();
    }
    cout << endl;
  }
  cout << "---------------------" << endl;
}

bool Image::SaveImage(const char * dst) const{
  ofstream out;
  
  out.open(dst, ios_base::binary);
  if(!out.is_open() || out.fail() || out.eof() || out.bad()){
    out.close();
    return false;
  }
  
 
  out << GetFCharUint16(_type) << GetSCharUint16(_type) << GetFCharUint16(_w) << GetSCharUint16(_w) << GetFCharUint16(_h) << GetSCharUint16(_h) << GetFCharUint16(_wFormat) << GetSCharUint16(_wFormat);

  if(!out.is_open() || out.fail() || out.eof() || out.bad()|| !out.good()){
    out.close();
    return false;
  }

  
  for(int y = 0; y < _h; y++){
    for(int x = 0; x < _w; x++){
      if(_channels == 1){
        out << (char)_bitmap[x][y].GetG();
      }else if(_channels == 3){
        out << (char)_bitmap[x][y].GetR();
        out << (char)_bitmap[x][y].GetG();
        out << (char)_bitmap[x][y].GetB();
      }else if(_channels == 4){
        out << (char)_bitmap[x][y].GetR();
        out << (char)_bitmap[x][y].GetG();
        out << (char)_bitmap[x][y].GetB();
        out << (char)_bitmap[x][y].GetA();
      }
      if(!out.is_open() || out.fail() || out.eof() || out.bad()|| !out.good()){
        out.close();
        return false;
      }
    }
  }

  out.close();
  return true;
}

bool Image::LoadImage(const char * src){  
  ifstream inp;
  inp.open(src, ios_base::binary);
  if(!inp.is_open() || inp.fail() || inp.eof() || inp.bad()|| !inp.good()){
    inp.close();
    return false;
  }
  
  inp.seekg ( 0, inp.end );
  int streamSize = inp.tellg();
  if(!inp || inp.fail() || inp.eof() || inp.bad() || !inp.good()){
    inp.close();
    return false;
  }
  if(streamSize < 8){
    inp.close();
    return false;
  }
  inp.seekg ( 0, inp.beg );
  
  if(!inp || inp.fail() || inp.eof() || inp.bad()|| !inp.good()){
    inp.close();
    return false;
  }

  memblock = new char [streamSize];
  inp.read( memblock, streamSize );

  if(!inp || inp.fail() || inp.eof() || inp.bad()|| !inp.good()){
    inp.close();
    return false;
  }

  inp.close();
  _fileLenght = streamSize;

  if(!LoadHeader(memblock)) 
    return false; 
  
  int checkSum =  streamSize - 8 - _w*_h*_channels;
  if(checkSum != 0){
    _w = 0;
    _h = 0;
    _bits = 0;
    _channels = 0;
    return false;
  }
  
  
  _bitmap = new Pixel*[_w];
  
  for(int i = 0; i < _w; i++)
    _bitmap[i] = new Pixel[_h];

  int readIndex = 8;
  for(int y = 0; y < _h; y++){
    for(int x = 0; x < _w; x++){
      if(_channels == 1){
        _bitmap[x][y].Set(-1,GetInt8(memblock[readIndex]),-1,-1);
        readIndex++;
      }
      if(_channels == 3){
        _bitmap[x][y].Set(GetInt8(memblock[readIndex]),GetInt8(memblock[readIndex+1]),GetInt8(memblock[readIndex+2]),-1);
        readIndex+=3;
      }    
      if(_channels == 4){
        _bitmap[x][y].Set(GetInt8(memblock[readIndex]),GetInt8(memblock[readIndex+1]),GetInt8(memblock[readIndex+2]),GetInt8(memblock[readIndex+3]));
        readIndex+=4;
      }    
    }
  }
  
  //cout << "Loaded: " << _w << " " << _h << " " << _channels << " " << _bits << endl; 
  return true;
}

Image::~Image(){
  if(_w <= 0 || _h <= 0){
    return;
  }
  for(int i = 0; i < _w; ++i){
    delete[] _bitmap[i];
  }
  if(_h > 0)
    delete[] _bitmap;
  delete[] memblock;
}

bool Image::Compare(Image & img1, Image & img2){
  if(img1._h != img2._h || img1._w != img2._w)
    return false;

  for(int y = 0; y < img1._h; y++){
    for(int x = 0; x < img1._w; x++){
      if(!img1._bitmap[x][y].Compare(img1._bitmap[x][y], img2._bitmap[x][y]))
        return false;
    }
  }
  return true;
}


bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{
  Image img = Image();
  cout << "Loading ";
  if(!img.LoadImage(srcFileName))
    return false;
  cout << "Loaded";
  //img.Print();
  if(flipHorizontal)
    img.FlipHorizontal();
  if(flipVertical)
    img.FlipVertical();
  //img.Print();
  cout << endl;
  if(!img.SaveImage(dstFileName))
    return false;
  return true;
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
  Image img1 = Image();
  cout << "Test: ";
  if(!img1.LoadImage(fileName1))
    return false;
  Image img2 = Image();
  if(!img2.LoadImage(fileName1))
    return false;
  
  cout << img1.Compare(img2, img1) << endl;

  return img1.Compare(img1, img2);
}

int main ( void )
{
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

  assert ( ! flipImage ( "input_09.img", "output_09.img", true, false ) );
/*
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
