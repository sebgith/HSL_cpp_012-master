#ifndef adcClass_h
#define adcClass_h

class adcInputCalc
{
public:
    adcInputCalc(const int physicalMinAdc,
                 const int physicalMaxAdc,
                 const int minCurrentAdc,
                 const int maxCurrentAdc,
                 const float filterAdc,
                 const int resistorAdc);
    static float _selectedGain;
    static unsigned long _durationSincePreviousAdcRead;
    static unsigned long _previousMillisAdcRead;
    float getMaxExpectedMilliVolt();
    void calcFilteredPhysAdcValue(int digitalReadAdc);
    float getDigitalReadAdc();
    float getFilterdPhysAdcValue();

private:
    // config parameter
    const int _physicalMinAdc; // unterer physikalischer Messwert
    const int _physicalMaxAdc; // oberer physikalischer Messwert
    const int _minCurrentAdc;  // unterer Strommesswert [mA]
    const int _maxCurrentAdc;  // oberer Strommesswert [mA]
    const float _filterAdc;    // filter
    const int _resistorAdc;    // Widerstand an dem die Strommessspannung abfällt
    // runtime parameter
    float _gradientAdc;
    float _offsetAdc;
    float _maxExpectedMilliVoltAtADC;
    int _digitalReadAdc;
    float _tauAdc;
    float _milliVoltAdc;
    float _milliAmpereAdc;
    float _physValueAdc;
    float _filteredPhysValueAdc;
};

#endif // adcClass_h