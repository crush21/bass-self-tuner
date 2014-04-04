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

const int NUM_CYCLES = 4096;
const int PEAK_LIMIT = 300;
const double ONE_MIL = 1000000.0;

int main() {
  timeval startTime, endTime, runTime;
  double waveform[NUM_CYCLES];
  double FFT[NUM_CYCLES];
  double aIn;
  double totalSec, avgSec;
  fftw_plan fftPlan;
/*  char * strAddr; */
  unsigned long * map_base, * virt_addr;
//  off_t ain = 0x44e0d000;
  off_t ain = 0x54c00000;

  char strIn [35] = "/sys/devices/ocp.3/helper.15/AIN0";
//  char str2In [35] = "/sys/devices/ocp.3/helper.15/AIN1";
//  char str3In [35] = "/sys/devices/ocp.3/helper.15/AIN2";
//  char str4In [35] = "/sys/devices/ocp.3/helper.15/AIN3";
  char FFTout [35] = "/root/code/output.txt";
  char waveOut [35] = "/root/code/waveform.txt";

  cout << "\nStarting program to read analog signals.\n" << endl;
  
  cout << strIn << endl;
  
  int strHandle = open(strIn, O_RDONLY);
//  unsigned long * address = 0x44e0d000;
//  unsigned long * address = 0x54c00000;
//  strAddr = (int*)mmap(0, getpagesize(), PROT_READ, MAP_SHARED, strHandle, 0x44e0d000 & ~MAP_MASK);
  map_base = (unsigned long*)mmap(0, 16, PROT_READ, MAP_SHARED, strHandle, ain);

  virt_addr = map_base + (ain & MAP_MASK);

  cout << "Address: " << (unsigned long*)virt_addr << endl;

  cout << "\nEntering infinite loop..." << endl;

  pollfd strFile;
  strFile.fd = strHandle;
  strFile.events = POLLIN;
  strFile.revents = POLLIN;

  gettimeofday(&startTime, NULL);

  for (int i = 0; i < NUM_CYCLES; i++) {

//    heart();

    poll(&strFile, 1, -1);
    aIn = getAnalog(1,  virt_addr); /* strFile.fd); */
    lseek(strHandle, 0, SEEK_SET);

    waveform[i] = aIn;

//    usleep(680);    
    
//    heart();

//    aIn2 = getAnalog(2, str2In);
    
//    heart();
    
//    aIn3 = getAnalog(3, str3In);
    
//    heart();
    
//    aIn4 = getAnalog(4, str4In);
    
  }
  
  gettimeofday(&endTime, NULL);
  timersub(&endTime,&startTime,&runTime);
  totalSec = runTime.tv_sec + runTime.tv_usec / ONE_MIL;
  avgSec = totalSec / NUM_CYCLES;
  cout << "Total runtime is: " << totalSec << endl;
  cout << "Average sample time is: " << avgSec << endl;
//  close(strHandle);
  fftPlan = fftw_plan_r2r_1d(NUM_CYCLES, waveform, FFT, FFTW_R2HC, FFTW_DESTROY_INPUT);
//  cout << "Made it here!" << endl;
  fftw_execute(fftPlan);

  ofstream FFTfile;
  ofstream wavFile;
  FFTfile.open(FFTout);
  wavFile.open(waveOut);
  for (int i = 0; i < (NUM_CYCLES / 2 + 1); i++) {
    FFTfile << FFT[i] << endl;
    wavFile << waveform[i] << endl;
  }
  FFTfile.close();
  wavFile.close();

// Check average of FFT with DC value ( FFT[0] )
/*
  double avg = 0;
  for (int j = 1; j < (NUM_CYCLES / 2 + 1); j++) {
    if (FFT[j] < 0) {
      avg -= FFT[j];
    } else {
      avg += FFT[j];
    }
  }
  avg = avg / NUM_CYCLES;
  cout << "Average: " << avg << endl;
  cout << "FFT[0]: " << FFT[0] << endl;
  if (avg == FFT[0]) {
    cout << "Success! FFT[0] is the average!" << endl;
  }
*/
  FFT[0] = 0;
  double frequency = getFrequency(FFT, NUM_CYCLES, PEAK_LIMIT, totalSec);
  double ideal = 55;
  cout << "Frequency: " << frequency << endl;
  cout << "Cent Difference: " << getCents(frequency, ideal) << endl;
  return 0;
}
