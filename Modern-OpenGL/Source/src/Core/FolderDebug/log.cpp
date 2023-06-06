#include <log.h>


Log Log::log;

// ------------------------ Function --------------------------------------

void Log::OpenFile(filesystem::path const& filename)
{

    log.file.open(filename);

    if (log.file)
    {
        cout << "file is open." << endl;
    }

	if (!log.file)
	{
		cout << "file '%s' NOT open, \n path name must start by './Assets/log/(name)'" << endl;
	}


}

void Log::Print(const char* fmt, ...)
{

    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0')
    {
        if (*fmt == '%')
        {
            ++fmt;
            if (*fmt == 'd' || *fmt == 'i')
            {
                // note automatic conversion to integral type
                int i = va_arg(args, int);
                std::cout << i;
                if (log.file) { log.file << i; }
            }

            else if (*fmt == 'c')
            {
                // note automatic conversion to character type
                int c = va_arg(args, int);
                std::cout << static_cast<char>(c);
                if(log.file) { log.file << static_cast<char>(c);}
            }

            else if (*fmt == 's')
            {
                // note automatic conversion to string type
                char* c = va_arg(args, char*);
                std::cout << c;
                if (log.file) { log.file << c; }
            }

            else if (*fmt == 'f')
            {
                // note automatic conversion to float type
                double d = va_arg(args, double);
                std::cout << d;
                if (log.file) { log.file << d; }
            }
        }

        else
        {
            std::cout << *fmt;
            if (log.file) { log.file << *fmt; }
        }

        ++fmt;
    }

    
    va_end(args);
}


void Log::PrintFileLine(const source_location loc)
{
    uint32_t line = loc.line();

    string fileName = loc.file_name();
    fileName = fileName.substr(fileName.find_last_of(92) + 1);
    string str = fileName + "(" + to_string(line) + ")";

    cout << str <<  " ";
    if (log.file)
        log.file << str << " ";
}

// ----------------------------- Builder -------------------------------

Log::Log()
{

}
Log::~Log()
{
	file.close();

}
