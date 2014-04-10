/* Testing FFT results
 * By Cheyn Rushing
 */

#include "analogFunc.h"
#include <fstream>

using namespace std;

int main() {
  double waveform[4096];
  fftw_complex FFT[4096];
  char value[4];
  char filename [13] = "waveform.txt";
  ifstream wavFile;
  wavFile.open(filename);
  if (wavFile.is_open()) {
    cout << "I am open!" << endl;
  }
  for (int i = 0; i < 4096; i++) {
    wavFile.getline(value,128);
    cout << value << endl;
    waveform[i] = atof(value);
    cout << waveform[i] << endl;
  }
  wavFile.close();
  fftw_plan fftPlan = fftw_plan_dft_r2c_1d(4096, waveform, FFT, FFTW_DESTROY_INPUT);
  fftw_execute(fftPlan);
  double frequency = getFrequency(FFT, 4095, 500, 929.2);
  cout << "Frequency: " << frequency << endl;
  return 0;
}
