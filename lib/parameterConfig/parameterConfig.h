#ifndef configParameter_h
#define configParameter_h

extern float filterRpm_1;
extern float filterRpm_2;
extern float filterRpm_3;

//  ------- ADC 0 ----------
extern int physicalMinAdc_0;  // unterer physikalischer Messwert
extern int physicalMaxAdc_0; // oberer physikalischer Messwert
extern int minCurrentAdc_0;   // unterer Strommesswert [mA]
extern int maxCurrentAdc_0;  // oberer Strommesswert [mA]
extern float filterAdc_0;  // filter
extern int resistorAdc_0;   // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 1 ----------
extern int physicalMinAdc_1;   // unterer physikalischer Messwert
extern int physicalMaxAdc_1; // oberer physikalischer Messwert
extern int minCurrentAdc_1;    // unterer Strommesswert [mA]
extern int maxCurrentAdc_1;   // oberer Strommesswert [mA]
extern float filterAdc_1;   // filter
extern int resistorAdc_1;    // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 2 ----------
extern int physicalMinAdc_2; // unterer physikalischer Messwert
extern int physicalMaxAdc_2; // oberer physikalischer Messwert
extern int minCurrentAdc_2;  // unterer Strommesswert [mA]
extern int maxCurrentAdc_2; // oberer Strommesswert [mA]
extern float filterAdc_2;  // filter
extern int resistorAdc_2;  // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 3 ----------
extern int physicalMinAdc_3; // unterer physikalischer Messwert
extern int physicalMaxAdc_3; // oberer physikalischer Messwert
extern int minCurrentAdc_3;    // unterer Strommesswert [mA]
extern int maxCurrentAdc_3;   // oberer Strommesswert [mA]
extern float filterAdc_3;    // filter
extern int resistorAdc_3;    // Widerstand an dem die Strommessspannung abfällt


#endif //configParameter_h