#ifndef configParameter_h
#define configParameter_h

extern float filterRpm_1;
extern float filterRpm_2;
extern float filterRpm_3;

//  ------- ADC 0 ----------
extern const int physicalMinAdc_0;  // unterer physikalischer Messwert
extern const int physicalMaxAdc_0; // oberer physikalischer Messwert
extern const int minCurrentAdc_0;   // unterer Strommesswert [mA]
extern const int maxCurrentAdc_0;  // oberer Strommesswert [mA]
extern const float filterAdc_0;  // filter
extern const int resistorAdc_0;   // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 1 ----------
extern const int physicalMinAdc_1;   // unterer physikalischer Messwert
extern const int physicalMaxAdc_1; // oberer physikalischer Messwert
extern const int minCurrentAdc_1;    // unterer Strommesswert [mA]
extern const int maxCurrentAdc_1;   // oberer Strommesswert [mA]
extern const float filterAdc_1;   // filter
extern const int resistorAdc_1;    // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 2 ----------
extern const int physicalMinAdc_2; // unterer physikalischer Messwert
extern const int physicalMaxAdc_2; // oberer physikalischer Messwert
extern const int minCurrentAdc_2;  // unterer Strommesswert [mA]
extern const int maxCurrentAdc_2; // oberer Strommesswert [mA]
extern const float filterAdc_2;  // filter
extern const int resistorAdc_2;  // Widerstand an dem die Strommessspannung abfällt
// ------- ADC 3 ----------
extern const int physicalMinAdc_3; // unterer physikalischer Messwert
extern const int physicalMaxAdc_3; // oberer physikalischer Messwert
extern const int minCurrentAdc_3;    // unterer Strommesswert [mA]
extern const int maxCurrentAdc_3;   // oberer Strommesswert [mA]
extern const float filterAdc_3;    // filter
extern const int resistorAdc_3;    // Widerstand an dem die Strommessspannung abfällt


#endif //configParameter_h