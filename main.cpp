#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace std;

int main(int argc, char const *argv[]) {
    //  Указываем путь к файлу file.dat.
    //  Для запуска программы после сборки в cmake - _build/explorer ./explorer file.dat
    const fs::path filePath = fs::current_path() / argv[1] / argv[2];

    //  Получаем имя файла file.dat.
    const fs::path textFilename = filePath.filename();
    //  Получаем время последннего изменения файла file.dat.
    auto ftime = fs::last_write_time(filePath);
    //  Интерпритируем данные времени в строку для вывода.
    std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

    //  Вывод в конец файла.
    ofstream session(filePath, ios_base::app);

    session << "name:\t" << textFilename << endl;
    session << "size:\t" << fs::file_size(filePath) << " Kb" << endl;
    session << "date:\t" << std::asctime(std::localtime(&cftime)) << endl;

    return 0;
}

