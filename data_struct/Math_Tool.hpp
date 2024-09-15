#ifndef MATH_TOOL_HPP
#define MATH_TOOL_HPP

template<typename T>
T clamp(T value, T lower, T upper) {
    if (value < lower) {
        return lower;
    } else if (value > upper) {
        return upper;
    } else {
        return value;
    }
}


template<typename T>
class LowPassFilter {
public:
    T previousFilteredValue;
    T alpha;
    LowPassFilter(T initialFilteredValue, T initialAlpha)
        : previousFilteredValue(initialFilteredValue), alpha(initialAlpha) {}
    LowPassFilter() {}

    T filter(T currentValue) {
        T filteredValue = alpha * currentValue + (1 - alpha) * previousFilteredValue;
        previousFilteredValue = filteredValue;
        return filteredValue;
    }
};

std::string formatNumber(int value, int digits) {
    std::string formatted = std::to_string(value);
    while (formatted.length() < digits) {
        formatted = "0" + formatted;
    }
    return formatted;
}

#endif