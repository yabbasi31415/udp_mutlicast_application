#include <benchmark/benchmark.h>
#include <byteswap.h>//to be used
#include <arpa/inet.h>//for ntohl ntohs

using namespace std;
union bytes4
{
    int32_t value;
    char ch[4];
};

union bytes2
{
    int16_t value;
    char ch[2];
};

static void changeEndianness16Union(benchmark::State& state)
{
    bytes2 temp;
    temp.value=16;
    char x;
   for (auto _ : state) {
      x= temp.ch[0];
      temp.ch[0]=temp.ch[1];
      temp.ch[1]=x;
   }
}

static void changeEndianness32Union(benchmark::State& state)
{
    bytes4 temp;
    temp.value=13;
    char x;
   for (auto _ : state) {
      x= temp.ch[0];
      temp.ch[0]=temp.ch[1];
      temp.ch[1]=x;

      x= temp.ch[2];
      temp.ch[2]=temp.ch[3];
      temp.ch[3]=x;
   }
   
}

static void changeEndianness16BitShift(benchmark::State& state)
{
   int16_t val = 13;
   for (auto _ : state) {
     val = (val << 8) | ((val >> 8) & 0x00ff); 
   }
   
}

static void changeEndianness32BitShift(benchmark::State& state)
{
   int16_t val = 13;
   for (auto _ : state) {
     val = (val << 24) |
          ((val <<  8) & 0x00ff0000) |
          ((val >>  8) & 0x0000ff00) |
          ((val >> 24) & 0x000000ff);
   }
  
}

static void changeEndiannessNtohl(benchmark::State& state)
{
   int32_t val = 13;
   for (auto _ : state) {
     val = ntohl(val);
   }
   
}

static void changeEndiannessNtohs(benchmark::State& state)
{
   int16_t val = 13;
   for (auto _ : state) {
     val = ntohs(val);
   }
  
}

BENCHMARK(changeEndianness16Union);
BENCHMARK(changeEndianness32Union);
BENCHMARK(changeEndianness16BitShift);
BENCHMARK(changeEndianness32BitShift);
BENCHMARK(changeEndiannessNtohs);
BENCHMARK(changeEndiannessNtohl);
