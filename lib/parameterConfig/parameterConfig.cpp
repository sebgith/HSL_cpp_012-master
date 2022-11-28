#include <parameterConfig.h>

float filterRpm_1 = 250;
float filterRpm_2 = 250;
float filterRpm_3 = 250;
// 250 entspricht bei 1 Sekunden (RpmCalcInterval) einem Anteil von 4*neuer Wert und 1*alter Wert
// 500 entspricht bei 1 Sekunden (RpmCalcInterval) einem Anteil von 2*neuer Wert und 1*alter Wert
//  ------- ADC 0 ----------
int physicalMinAdc_0 = 0;  // unterer physikalischer Messwert
int physicalMaxAdc_0 = 30; // oberer physikalischer Messwert
int minCurrentAdc_0 = 4;   // unterer Strommesswert [mA]
int maxCurrentAdc_0 = 20;  // oberer Strommesswert [mA]
float filterAdc_0 = 1000;  // filter
int resistorAdc_0 = 180;   // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 1 ----------
int physicalMinAdc_1 = 0;   // unterer physikalischer Messwert
int physicalMaxAdc_1 = 250; // oberer physikalischer Messwert
int minCurrentAdc_1 = 4;    // unterer Strommesswert [mA]
int maxCurrentAdc_1 = 20;   // oberer Strommesswert [mA]
float filterAdc_1 = 1000;   // filter
int resistorAdc_1 = 180;    // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 2 ----------
int physicalMinAdc_2 = 0; // unterer physikalischer Messwert
int physicalMaxAdc_2 = 4; // oberer physikalischer Messwert
int minCurrentAdc_2 = 4;  // unterer Strommesswert [mA]
int maxCurrentAdc_2 = 20; // oberer Strommesswert [mA]
float filterAdc_2 = 500;  // filter
int resistorAdc_2 = 180;  // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 3 ----------
int physicalMinAdc_3 = -50; // unterer physikalischer Messwert
int physicalMaxAdc_3 = 150; // oberer physikalischer Messwert
int minCurrentAdc_3 = 4;    // unterer Strommesswert [mA]
int maxCurrentAdc_3 = 20;   // oberer Strommesswert [mA]
float filterAdc_3 = 500;    // filter
int resistorAdc_3 = 180;    // Widerstand an dem die Strommessspannung abfällt
