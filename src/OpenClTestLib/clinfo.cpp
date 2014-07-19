#include "clinfo.h"

#include <cassert>
#include <sstream>



ClValue::ClValue(bool boolean):
    type(Type::BOOLEAN),
    number(boolean)
{}



ClValue::ClValue(uint32_t number):
    type(Type::NUMBER),
    number(number)
{}



ClValue::ClValue(uint64_t number, Type type):
    type(type),
    number(number)
{}



ClValue::ClValue(const std::string& text):
    type(Type::TEXT),
    text(text)
{}



ClValue::ClValue(const std::vector<size_t> sizeArray):
    type(Type::SIZE_ARRAY),
    sizeArray(sizeArray)
{}



const std::vector<std::string> FP_CONFIG_FIELD_NAMES = {
    "CL_FP_DENORM",
    "CL_FP_INF_NAN",
    "CL_FP_ROUND_TO_NEAREST",
    "CL_FP_ROUND_TO_ZERO",
    "CL_FP_ROUND_TO_INF",
    "CP_FP_FMA",
    "CL_FP_SOFT_FLOAT",
    "CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT"
};

const std::vector<std::string> DEVICE_EXEC_CAPABILITIES_FIELD_NAMES = {
    "CL_EXEC_KERNEL"
    "CL_EXEC_NATIVE_KERNEL"
};

const std::vector<std::string> DEVICE_MEM_CACHE_TYPE_ENUM_NAMES = {
    "CL_NONE",
    "CL_READ_ONLY_CACHE",
    "CL_READ_WRITE_CACHE"
};

const std::vector<std::string> DEVICE_LOCAL_MEM_TYPE_ENUM_NAMES = {
    "",
    "CL_LOCAL",
    "CL_GLOBAL"
};

const std::vector<std::string> COMMAND_QUEUE_PROPERTIES_FIELD_NAMES = {
    "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE",
    "CL_QUEUE_PROFILING_ENABLE"
};

const std::vector<std::string> DEVICE_TYPE_FIELD_NAMES = {
    "CL_DEVICE_TYPE_DEFAULT",
    "CL_DEVICE_TYPE_CPU",
    "CL_DEVICE_TYPE_GPU",
    "CL_DEVICE_TYPE_ACCELERATOR",
    "CL_DEVICE_TYPE_CUSTOM"
};

std::string ClValue::toString() const
{
    switch (type) {
    case Type::BOOLEAN:
        return number ? "true" : "false";
    case Type::NUMBER:
        return formatNumber(number);
    case Type::TEXT:
        return text;
    case Type::SIZE_ARRAY:
        return formatSizeArray(sizeArray);
    case Type::FP_CONFIG:
        return formatBitField(number, FP_CONFIG_FIELD_NAMES);
    case Type::DEVICE_EXEC_CAPABILITIES:
        return formatBitField(number, DEVICE_EXEC_CAPABILITIES_FIELD_NAMES);
    case Type::DEVICE_MEM_CACHE_TYPE:
        return DEVICE_MEM_CACHE_TYPE_ENUM_NAMES.at(number);
    case Type::DEVICE_LOCAL_MEM_TYPE:
        return DEVICE_LOCAL_MEM_TYPE_ENUM_NAMES.at(number);
    case Type::COMMAND_QUEUE_PROPERTIES:
        return formatBitField(number, COMMAND_QUEUE_PROPERTIES_FIELD_NAMES);
    case Type::DEVICE_TYPE:
        return formatBitField(number, DEVICE_TYPE_FIELD_NAMES);
    default:
        assert(false);
        return "";
    }
}



std::string ClValue::formatNumber(uint64_t number)
{
    std::ostringstream oss;
    oss << number;
    return oss.str();
}



std::string ClValue::formatSizeArray(const std::vector<size_t> array)
{
    if (array.empty()) {
        return "";
    }


    std::ostringstream oss;
    oss << array[0];
    for (size_t i = 1; i < array.size(); ++i) {
        oss << ", " << array[i];
    }
    return oss.str();
}



std::string ClValue::formatBitField(
        uint64_t number,
        const std::vector<std::string>& fieldNames)
{
    std::ostringstream oss;
    bool isFirst = true;
    for (uint64_t i = 0; i < fieldNames.size(); ++i) {
        if (number & (1 << i)) {
            if (!isFirst) {
                oss << " | ";
            }
            oss << fieldNames[i];
            isFirst = false;
        }
    }
    return oss.str();
}
