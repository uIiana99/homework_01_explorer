#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <cstring>

namespace fs = std::experimental::filesystem;
using namespace std;

int main(int argc, char const *argv[]) {
    try {
        //  Указываем путь к файлу file.dat.
        //  Для запуска программы после сборки в cmake - _build/explorer ./explorer file.dat

        string path;

        for(int i = 1; i < argc; i++) {
            path += argv[i];
            if(i != (argc - 1))
                path += "/";
        }

        if(!fs::exists(path)) throw logic_error("do not found any files");

        const fs::path filePath = fs::current_path() / path;

        //  Получаем имя файла file.dat.
        const fs::path textFilename = filePath.filename();
        //  Получаем время последннего изменения файла file.dat.
        auto ftime = fs::last_write_time(filePath);
        //  Интерпритируем данные времени в строку для вывода.
        std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

        //  Расчитываем размер файла
        double fileSize = fs::file_size(filePath);
        fileSize /= 1000;

        //  Вывод в конец файла.
        ofstream session(filePath, ios_base::app);

        session << "name:\t" << textFilename << endl;
        session << "size:\t" << fileSize << " Kb" << endl;
        session << "date:\t" << std::asctime(std::localtime(&cftime)) << endl;

    } catch(const std::exception& e) {
        cout << e.what() << endl;
    } 

    return 0;
}

