/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan.
 */

#include "analogFunc.h"
#include <fstream>
#include <poll.h>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

const int NUM_CYCLES = 1024;
const int PEAK_LIMIT = NUM_CYCLES / 8;
const double ONE_MIL = 1000000.0;
const double ONE_BIL = 1000000000.0;

int main() {
  timespec startTime, endTime, runTime;
//  timeval startTime, endTime, runTime;
  double waveform[NUM_CYCLES];
  double FFTdouble[NUM_CYCLES];
  fftw_complex FFT[NUM_CYCLES];
/*
  octave_value_list octFFT;
  octave_value_list octWave;
*/
  double aIn;
  double totalSec, avgSec;
  fftw_plan fftPlan;
/*  char * strAddr; */
/*  unsigned long * map_base, * virt_addr;
//  off_t ain = 0x44e0d000;
  off_t ain = 0x54c00000; */

//  char strIn [50] = "/sys/bus/iio/devices/iio:device0/in_voltage0_raw";
  char strIn [35] = "/sys/devices/ocp.3/helper.15/AIN0";
//  char str2In [35] = "/sys/devices/ocp.3/helper.15/AIN1";
//  char str3In [35] = "/sys/devices/ocp.3/helper.15/AIN2";
//  char str4In [35] = "/sys/devices/ocp.3/helper.15/AIN3";
  char FFTout [35] = "/root/code/output.txt";
  char waveOut [35] = "/root/code/waveform.txt";
/*  char trigger [40] = "/sys/bus/devices/trigger0/trigger_now";
  char * ONE = "1"; */

  std::cout << "\nStarting program to read analog signals.\n" << std::endl;
  
  std::cout << strIn << std::endl;
  
  int strHandle = open(strIn, O_RDONLY | O_SYNC);
  std::perror("Result");
//  int triggerHandle = open(trigger, O_WRONLY);
//  unsigned long * address = 0x44e0d000;
//  unsigned long * address = 0x54c00000;
//  strAddr = (int*)mmap(0, getpagesize(), PROT_READ, MAP_SHARED, strHandle, 0x44e0d000 & ~MAP_MASK);
/*  map_base = (unsigned long*)mmap(0, 16, PROT_READ, MAP_SHARED, strHandle, ain);

  virt_addr = map_base + (ain & MAP_MASK);

  std::cout << "Address: " << (unsigned long*)virt_addr << std::endl; */

  std::cout << "\nEntering the loop..." << std::endl;
/*
  pollfd strFile;
  strFile.fd = strHandle;
  strFile.events = POLLIN;
  strFile.revents = POLLIN;
*/
  clock_gettime(CLOCK_MONOTONIC, &startTime);

  for (int i = 0; i < NUM_CYCLES; i++) {

//    heart();

//    poll(&strFile, 1, -1);
    aIn = getAnalog(1, /* virt_addr); */ strHandle);  // strFile.fd);
    lseek(strHandle, 0, SEEK_SET);
/*    write(triggerHandle, ONE, 1);
    lseek(triggerHandle, 0, SEEK_SET); */

    waveform[i] = aIn;

//    octWave.append(octave_value(aIn));

//    usleep(680);    
    
//    heart();

//    aIn2 = getAnalog(2, str2In);
    
//    heart();
    
//    aIn3 = getAnalog(3, str3In);
    
//    heart();
    
//    aIn4 = getAnalog(4, str4In);
    
  }
  
  clock_gettime(CLOCK_MONOTONIC,&endTime);
  runTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
  runTime.tv_nsec = endTime.tv_nsec - startTime.tv_nsec;
//  timersub(&endTime,&startTime,&runTime);
  totalSec = runTime.tv_sec + runTime.tv_nsec / ONE_BIL;
  avgSec = totalSec / NUM_CYCLES;
  std::cout << "Total runtime is: " << totalSec << std::endl;
  std::cout << "Average sample time is: " << avgSec << std::endl;
//  close(triggerHandle);
  close(strHandle);



/*
  octFFT = Ffft(octWave, NUM_CYCLES - 1);
  octave_value anOctVal;
  for (int i = 0; i < NUM_CYCLES; i++) {
    anOctVal = octFFT(i);
    std::cout << anOctVal.type_name() << std::endl;
    std::cout << anOctVal.class_name() << std::endl;
    FFT[i] = abs(anOctVal.double_value());
  }
*/




  fftPlan = fftw_plan_dft_r2c_1d(NUM_CYCLES, waveform, FFT, FFTW_DESTROY_INPUT | FFTW_MEASURE);
  std::cout << "Made it here!" << std::endl;
  fftw_execute(fftPlan);

// Write waveform and FFT result to files.
  std::ofstream wavFile;
  std::fstream FFTfile;
  wavFile.open(waveOut);
  FFTfile.open(FFTout);
  for (int i = 0; i < (NUM_CYCLES / 2 + 1); i++) {
    wavFile << waveform[i] << std::endl;
    FFTfile << FFT[i][0] << std::endl;
  }
  wavFile.close();
  FFTfile.close();

  for (int j = 1; j < (NUM_CYCLES); j++) {
    FFTdouble[j] = fabs(FFT[j][0]);
/*    if (FFT[j] < 0) {
      FFTdouble[j] = -1 * FFT[j];
    } else {
      FFTdouble[j] = FFT[j];
    } */
  }

  double sampleFrequency = 1 / avgSec;
  double frequency = getFrequency(FFTdouble, NUM_CYCLES - 1, PEAK_LIMIT, sampleFrequency);
  double ideal = 97.99;
  std::cout << "Frequency: " << frequency << std::endl;
  std::cout << "Cent Difference: " << getCents(frequency, ideal) << std::endl;
  return 0;
}
