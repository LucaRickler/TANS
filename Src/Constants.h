#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const double g_mass_gamma = 0.0; // MeV/c^2
const double g_mass_electron = 0.511; // MeV/c^2
const double g_mass_positron = 0.511; // MeV/c^2

const double g_threshold_gamma = 10.; // Soglia in MeV per i gamma per la produzione di coppia.
const double g_threshold_electron = 88.05; // Soglia in MeV per gli elettroni per la bremmstrahlung.
const double g_threshold_positron = g_threshold_electron; // Soglia in MeV per gli positroni per la bremmstrahlung.

const double g_gamma_bs_min_energy = 1.e-3; // MeV , Soglia minima di energia per i fotoni emessi per bremmstrahlung

const double g_absorb_threshold = 2.5; //MeV , soglia discriminante tra i tipi di riassorbimento degli elettroni

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
