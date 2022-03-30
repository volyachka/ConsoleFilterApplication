#include "ExceptionInFilter.h"

const char *InvalidParameterInHeader::what() const noexcept {

    return message_.c_str();

}

InvalidParameterInHeader::InvalidParameterInHeader(std::string exception) : message_(
        "InvalidParameterInHeader, got " + exception) {

}


const char *InvalidByte::what() const noexcept {

    return "InvalidByte";

}

FileOpenFailedException::FileOpenFailedException(std::string path)
        : message_("failed to open file: " + path) {}

const char *FileOpenFailedException::what() const noexcept {

    return message_.c_str();

}

NotEnoughArgumentsException::NotEnoughArgumentsException(int argc)
        : message_("Not enough args: " + std::to_string(argc)) {}

const char *NotEnoughArgumentsException::what() const noexcept {

    return message_.c_str();

}

InvalidFilter::InvalidFilter(std::string name_of_filter) : message_("No Filter with name" + name_of_filter) {}

const char *InvalidFilter::what() const noexcept {

    return message_.c_str();

}


InvalidFormat::InvalidFormat(std::string parameter) : message_("Expect BMP format, but got " + parameter) {
}

const char *InvalidFormat::what() const noexcept {
    return message_.c_str();
}


