// menu.h
// Все меню и взаимодействие с пользователем.
#pragma once


// Красивый стартовый экран (название проекта, автор, год)
void show_start_window();

// Главное меню: 1 — один файл, 2 — все файлы, 3 — выход
int  show_main_menu();

// Выбор файла из папки SourceTexts (нумерованный список)
std::string choose_source_file();

// Выбор режима сортировки слов при итоговом выводе
SortMode choose_sort_mode();

// Ввод числа K (только цифры, защита от дурака)
int  input_top_k();

// Экран завершения анализа
void show_completion_screen(const std::string& mode, int k);

