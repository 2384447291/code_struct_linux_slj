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

#endif