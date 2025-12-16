// output.h
// Красивый вывод на экран и сохранение в файл.
#pragma once



// Выводим результат на экран (с рамками, цветами и т.д.)
void display_results(const std::vector<WordFrequency>& top,
    int k,
    const std::string& mode,
    const std::string& source = "",
    SortMode sort = SortMode::ByFrequency);

// Сохраняем результат в папку Records
void save_to_file(const std::vector<WordFrequency>& top,
    int k,
    const std::string& mode,
    const std::string& source_filename = "",
    SortMode sort = SortMode::ByFrequency);

