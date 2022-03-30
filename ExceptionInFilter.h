#include <iostream>
#include <fstream>

#pragma once

class FileOpenFailedException : public std::exception {
public:
    FileOpenFailedException(std::string path);

    const char *what() const noexcept override;

private:
    std::string message_;
};

class NotEnoughArgumentsException : public std::exception {
public:
    NotEnoughArgumentsException(int argc);

    const char *what() const noexcept override;

private:
    std::string message_;
};

class InvalidFilter : public std::exception {
public:
    InvalidFilter(std::string name_of_filter);

    const char *what() const noexcept override;

private:
    std::string message_;
};

class InvalidParameterInHeader : public std::exception {
public:
    InvalidParameterInHeader(std::string exception);

    const char *what() const noexcept override;

private:
    std::string message_;
};

class InvalidByte : public std::exception {
public:
    const char *what() const noexcept override;
};

class InvalidFormat : public std::exception {
public:
    InvalidFormat(std::string parameter);

    const char *what() const noexcept override;

private:
    std::string message_;
};