#include <adcClass.h>

adcInputCalc::adcInputCalc(const int physicalMinAdc,
                           const int physicalMaxAdc,
                           const int minCurrentAdc,
                           const int maxCurrentAdc,
                           const float filterAdc,
                           const int resistorAdc)
    : _physicalMinAdc(physicalMinAdc),
      _physicalMaxAdc(physicalMaxAdc),
      _minCurrentAdc(minCurrentAdc),
      _maxCurrentAdc(maxCurrentAdc),
      _filterAdc(filterAdc),
      _resistorAdc(resistorAdc)
{
    _gradientAdc = (float)(_physicalMaxAdc - _physicalMinAdc) / (float)(_maxCurrentAdc - _minCurrentAdc); // m = (y2-y1) / (x2-x1)
    _offsetAdc = _physicalMinAdc - _gradientAdc * _minCurrentAdc;                                         // b = y1 - m*x1
    _maxExpectedMilliVoltAtADC = _maxCurrentAdc * (float)_resistorAdc;                                    // calc max voltage values for ADC settings
}

float adcInputCalc::getMaxExpectedMilliVolt()
{
    return _maxExpectedMilliVoltAtADC;
}

void adcInputCalc::calcFilteredPhysAdcValue(int digitalReadAdc)
{
    _digitalReadAdc = digitalReadAdc;
    _tauAdc = _filterAdc / _durationSincePreviousAdcRead;                                       // calc tau for filter
    _milliVoltAdc = (float)(_selectedGain * _digitalReadAdc) / (32768);                        // max Spannung (gain) / 32769LBS - Auflösung ADC
    _milliAmpereAdc = (float)_milliVoltAdc / _resistorAdc;                                     // calc current
    _physValueAdc = _gradientAdc * (float)_milliAmpereAdc + _offsetAdc;                        // calc physical value
    _filteredPhysValueAdc = (_filteredPhysValueAdc * _tauAdc + _physValueAdc) / (_tauAdc + 1); // final filtered value
}

float adcInputCalc::getFilterdPhysAdcValue()
{
    return _filteredPhysValueAdc;
}

float adcInputCalc::getDigitalReadAdc()
{
    return _digitalReadAdc;
}