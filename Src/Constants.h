#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const double g_mass_gamma = 0.0; //MeV
const double g_mass_electron = 0.511; //MeV
const double g_mass_positron = 0.511; //MeV

const double g_threshold_gamma = 10.; // Soglia in MeV per i gamma per fare produzione di coppia (ottenuto "ad occhio" dai grafici di probabilità di interazione di gamma). 
const double g_threshold_electron = 88.05; // Soglia in MeV per gli elettroni per fare bremmstrahlung.
const double g_threshold_positron = 88.05; // Soglia in MeV per gli positroni per fare bremmstrahlung.

const double g_c = 299792458.0; //m/s
const double g_c2 = 8.98755178736817600e+16; //m/s

const double g_masses[] = {
  g_mass_gamma,
  g_mass_electron,
  g_mass_positron
};

const double g_threshold[] = {
  g_threshold_gamma,
  g_threshold_electron,
  g_threshold_positron
};

#endif
