#include "Application.h"
#include "ExceptionHandler.h"
#include <iostream>

int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch (const BadAllocException& e)
    {
        e.handle();
        std::cerr << "Критическая ошибка: недостаточно памяти для работы программы.\n";
        return 1;
    }
    catch (const BadCastException& e)
    {
        e.handle();
        std::cerr << "Критическая ошибка: ошибка приведения типа.\n";
        return 1;
    }
    catch (const BadTypeIdException& e)
    {
        e.handle();
        std::cerr << "Критическая ошибка: ошибка получения информации о типе.\n";
        return 1;
    }
    catch (const InvalidArgumentException& e)
    {
        e.handle();
        std::cerr << "Ошибка: неверные аргументы.\n";
        return 1;
    }
    catch (const OutOfRangeException& e)
    {
        e.handle();
        std::cerr << "Ошибка: выход за границы.\n";
        return 1;
    }
    catch (const LengthErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка: превышена допустимая длина.\n";
        return 1;
    }
    catch (const DomainErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка: некорректная область определения.\n";
        return 1;
    }
    catch (const OverflowErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка: переполнение.\n";
        return 1;
    }
    catch (const UnderflowErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка: недополнение.\n";
        return 1;
    }
    catch (const FileErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка: проблема с файлом.\n";
        return 1;
    }
    catch (const NetworkErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка: проблема с сетью.\n";
        return 1;
    }
    catch (const SystemErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка: системная ошибка.\n";
        return 1;
    }
    catch (const RuntimeErrorException& e)
    {
        e.handle();
        std::cerr << "Ошибка времени выполнения.\n";
        return 1;
    }
    catch (const std::exception& e)
    {
        ExceptionUtils::handleException(e);
        return 1;
    }
    catch (...)
    {
        std::cerr << "Неизвестная критическая ошибка!\n";
        return 1;
    }
    
    return 0;
}

