#pragma once

#include <exception>
#include <stdexcept>
#include <new>
#include <typeinfo>
#include <string>
#include <iostream>

// ============================================
// БАЗОВЫЙ КЛАСС ОБРАБОТКИ ИСКЛЮЧЕНИЙ
// ============================================
class ExceptionHandler
{
public:
    virtual ~ExceptionHandler() = default;
    virtual void handle() const = 0;
    virtual const char* what() const noexcept = 0;
};

// ============================================
// ИСКЛЮЧЕНИЯ ЯЗЫКОВОЙ ПОДДЕРЖКИ C++
// ============================================

// bad_alloc - ошибка выделения памяти
class BadAllocException : public ExceptionHandler, public std::bad_alloc
{
private:
    std::string message;
    size_t requestedSize;

public:
    explicit BadAllocException(size_t size = 0) 
        : requestedSize(size)
    {
        message = "bad_alloc: Не удалось выделить память";
        if (size > 0)
            message += " (запрошено: " + std::to_string(size) + " байт)";
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    size_t getRequestedSize() const { return requestedSize; }
};

// bad_cast - ошибка приведения типа
class BadCastException : public ExceptionHandler, public std::bad_cast
{
private:
    std::string message;
    std::string fromType;
    std::string toType;

public:
    explicit BadCastException(const std::string& from = "", const std::string& to = "")
        : fromType(from), toType(to)
    {
        message = "bad_cast: Ошибка приведения типа";
        if (!from.empty() && !to.empty())
            message += " (из " + from + " в " + to + ")";
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА ПРИВЕДЕНИЯ ТИПА: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// bad_typeid - ошибка получения информации о типе
class BadTypeIdException : public ExceptionHandler, public std::bad_typeid
{
private:
    std::string message;

public:
    explicit BadTypeIdException(const std::string& typeName = "")
    {
        message = "bad_typeid: Ошибка получения информации о типе";
        if (!typeName.empty())
            message += " (тип: " + typeName + ")";
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА TYPEID: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// ============================================
// ЛОГИЧЕСКИЕ ОШИБКИ (Logic Errors)
// ============================================

// domain_error - ошибка области определения
class DomainErrorException : public ExceptionHandler, public std::domain_error
{
private:
    std::string message;

public:
    explicit DomainErrorException(const std::string& msg = "Ошибка области определения")
        : std::domain_error(msg), message(msg) {}

    void handle() const override
    {
        std::cerr << "ОШИБКА ОБЛАСТИ ОПРЕДЕЛЕНИЯ: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// invalid_argument - неверный аргумент
class InvalidArgumentException : public ExceptionHandler, public std::invalid_argument
{
private:
    std::string message;
    std::string argumentName;

public:
    explicit InvalidArgumentException(const std::string& argName = "", const std::string& msg = "")
        : std::invalid_argument(msg.empty() ? "Неверный аргумент" : msg), 
          argumentName(argName)
    {
        message = "invalid_argument: Неверный аргумент";
        if (!argName.empty())
            message += " (" + argName + ")";
        if (!msg.empty() && msg != "Неверный аргумент")
            message += ": " + msg;
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА АРГУМЕНТА: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    const std::string& getArgumentName() const { return argumentName; }
};

// length_error - ошибка длины
class LengthErrorException : public ExceptionHandler, public std::length_error
{
private:
    std::string message;
    size_t actualLength;
    size_t maxLength;

public:
    explicit LengthErrorException(size_t actual = 0, size_t max = 0, const std::string& msg = "")
        : std::length_error(msg.empty() ? "Ошибка длины" : msg),
          actualLength(actual), maxLength(max)
    {
        message = "length_error: Превышена допустимая длина";
        if (actual > 0 && max > 0)
            message += " (текущая: " + std::to_string(actual) + ", максимум: " + std::to_string(max) + ")";
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА ДЛИНЫ: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    size_t getActualLength() const { return actualLength; }
    size_t getMaxLength() const { return maxLength; }
};

// out_of_range - выход за границы
class OutOfRangeException : public ExceptionHandler, public std::out_of_range
{
private:
    std::string message;
    size_t index;
    size_t size;

public:
    explicit OutOfRangeException(size_t idx = 0, size_t sz = 0, const std::string& msg = "")
        : std::out_of_range(msg.empty() ? "Выход за границы" : msg),
          index(idx), size(sz)
    {
        message = "out_of_range: Индекс вне допустимого диапазона";
        if (idx >= 0 && sz > 0)
            message += " (индекс: " + std::to_string(idx) + ", размер: " + std::to_string(sz) + ")";
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА ДИАПАЗОНА: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    size_t getIndex() const { return index; }
    size_t getSize() const { return size; }
};

// ============================================
// ОШИБКИ ПЕРЕПОЛНЕНИЯ И НЕДОПОЛНЕНИЯ
// ============================================

// overflow_error - ошибка переполнения
class OverflowErrorException : public ExceptionHandler, public std::overflow_error
{
private:
    std::string message;
    std::string operation;

public:
    explicit OverflowErrorException(const std::string& op = "", const std::string& msg = "")
        : std::overflow_error(msg.empty() ? "Переполнение" : msg), operation(op)
    {
        message = "overflow_error: Переполнение";
        if (!op.empty())
            message += " при операции: " + op;
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА ПЕРЕПОЛНЕНИЯ: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    const std::string& getOperation() const { return operation; }
};

// underflow_error - ошибка недополнения
class UnderflowErrorException : public ExceptionHandler, public std::underflow_error
{
private:
    std::string message;
    std::string operation;

public:
    explicit UnderflowErrorException(const std::string& op = "", const std::string& msg = "")
        : std::underflow_error(msg.empty() ? "Недополнение" : msg), operation(op)
    {
        message = "underflow_error: Недополнение";
        if (!op.empty())
            message += " при операции: " + op;
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА НЕДОПОЛНЕНИЯ: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    const std::string& getOperation() const { return operation; }
};

// ============================================
// ИСКЛЮЧЕНИЯ СТАНДАРТНОЙ БИБЛИОТЕКИ C++
// ============================================

// runtime_error - ошибка времени выполнения
class RuntimeErrorException : public ExceptionHandler, public std::runtime_error
{
private:
    std::string message;

public:
    explicit RuntimeErrorException(const std::string& msg = "Ошибка времени выполнения")
        : std::runtime_error(msg), message(msg) {}

    void handle() const override
    {
        std::cerr << "ОШИБКА ВРЕМЕНИ ВЫПОЛНЕНИЯ: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// range_error - ошибка диапазона
class RangeErrorException : public ExceptionHandler, public std::range_error
{
private:
    std::string message;

public:
    explicit RangeErrorException(const std::string& msg = "Ошибка диапазона")
        : std::range_error(msg), message(msg) {}

    void handle() const override
    {
        std::cerr << "ОШИБКА ДИАПАЗОНА: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// ============================================
// ИСКЛЮЧЕНИЯ ВНЕШНИХ ОШИБОК
// ============================================

// file_error - ошибка работы с файлом
class FileErrorException : public ExceptionHandler, public std::runtime_error
{
private:
    std::string message;
    std::string fileName;
    std::string operation;

public:
    explicit FileErrorException(const std::string& file = "", const std::string& op = "", const std::string& msg = "")
        : std::runtime_error(msg.empty() ? "Ошибка работы с файлом" : msg),
          fileName(file), operation(op)
    {
        message = "file_error: Ошибка работы с файлом";
        if (!file.empty())
            message += " (" + file + ")";
        if (!op.empty())
            message += " при операции: " + op;
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА ФАЙЛА: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    const std::string& getFileName() const { return fileName; }
    const std::string& getOperation() const { return operation; }
};

// network_error - ошибка сети
class NetworkErrorException : public ExceptionHandler, public std::runtime_error
{
private:
    std::string message;
    std::string host;
    int port;

public:
    explicit NetworkErrorException(const std::string& h = "", int p = 0, const std::string& msg = "")
        : std::runtime_error(msg.empty() ? "Ошибка сети" : msg),
          host(h), port(p)
    {
        message = "network_error: Ошибка сети";
        if (!h.empty())
            message += " (" + h;
        if (p > 0)
            message += ":" + std::to_string(p);
        if (!h.empty() || p > 0)
            message += ")";
    }

    void handle() const override
    {
        std::cerr << "ОШИБКА СЕТИ: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    const std::string& getHost() const { return host; }
    int getPort() const { return port; }
};

// system_error - системная ошибка
class SystemErrorException : public ExceptionHandler, public std::system_error
{
private:
    std::string message;
    int errorCode;

public:
    explicit SystemErrorException(int code = 0, const std::string& msg = "")
        : std::system_error(code, std::system_category(), msg.empty() ? "Системная ошибка" : msg),
          errorCode(code)
    {
        message = "system_error: Системная ошибка";
        if (code != 0)
            message += " (код: " + std::to_string(code) + ")";
    }

    void handle() const override
    {
        std::cerr << "СИСТЕМНАЯ ОШИБКА: " << message << std::endl;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }

    int getErrorCode() const { return errorCode; }
};

// ============================================
// УТИЛИТЫ ДЛЯ ОБРАБОТКИ ИСКЛЮЧЕНИЙ
// ============================================

class ExceptionUtils
{
public:
    // Универсальная обработка исключений
    static void handleException(const std::exception& e)
    {
        std::cerr << "Поймано исключение: " << e.what() << std::endl;
        
        // Попытка привести к нашему типу
        try {
            const ExceptionHandler* handler = dynamic_cast<const ExceptionHandler*>(&e);
            if (handler)
            {
                handler->handle();
            }
        }
        catch (...)
        {
            // Если не удалось привести, просто выводим стандартное сообщение
            std::cerr << "Стандартное исключение: " << e.what() << std::endl;
        }
    }

    // Безопасное выполнение с обработкой исключений
    template<typename Func>
    static void safeExecute(Func func, const std::string& operation = "")
    {
        try
        {
            func();
        }
        catch (const BadAllocException& e)
        {
            e.handle();
            throw;
        }
        catch (const BadCastException& e)
        {
            e.handle();
            throw;
        }
        catch (const BadTypeIdException& e)
        {
            e.handle();
            throw;
        }
        catch (const DomainErrorException& e)
        {
            e.handle();
            throw;
        }
        catch (const InvalidArgumentException& e)
        {
            e.handle();
            throw;
        }
        catch (const LengthErrorException& e)
        {
            e.handle();
            throw;
        }
        catch (const OutOfRangeException& e)
        {
            e.handle();
            throw;
        }
        catch (const OverflowErrorException& e)
        {
            e.handle();
            throw;
        }
        catch (const UnderflowErrorException& e)
        {
            e.handle();
            throw;
        }
        catch (const FileErrorException& e)
        {
            e.handle();
            throw;
        }
        catch (const NetworkErrorException& e)
        {
            e.handle();
            throw;
        }
        catch (const SystemErrorException& e)
        {
            e.handle();
            throw;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Неизвестное исключение при операции '" << operation << "': " << e.what() << std::endl;
            throw;
        }
        catch (...)
        {
            std::cerr << "Неизвестное исключение при операции '" << operation << "'" << std::endl;
            throw;
        }
    }
};

