// main.cpp
// Точка входа в программу

#include "Header.h"

int main() {
    // Настраиваем консоль на русскую кодировку ANSI (Windows-1251)
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    system("color F0");

    // Приветствие
    show_start_window();

    while (true) {
        int menu_choice = show_main_menu();

        // 3 — Выход
        if (menu_choice == 3) {
            system("cls");
            std::cout << "\n\n";
            std::cout << "=======================================================================================================================\n";
            std::cout << "                                     ПРОГРАММА ЗАВЕРШЕНА. ДО СВИДАНИЯ!\n";
            std::cout << "=======================================================================================================================\n";
            std::cout << "\n\n";
            _getch();
            break;
        }

        // Запрашиваем количество слов в Top-K
        int k = input_top_k();
        if (k <= 0) {
            continue; // Esc — возврат в меню
        }

        // Выбираем режим сортировки
        SortMode sort_mode = choose_sort_mode();

        // Создаём новое дерево для чистого анализа
        Trie trie;
        std::string mode_text;
        std::string source_name;

        if (menu_choice == 1) {
            // === Анализ одного файла ===
            std::string filename = choose_source_file();
            if (filename.empty()) {
                continue; // Esc — назад
            }

            mode_text = "Один файл";
            source_name = filename;

            read_single_file(filename, trie);

        }
        else if (menu_choice == 2) {
            // === Анализ всех файлов ===
            mode_text = "Все файлы";
            source_name = "Папка SourceTexts";

            read_all_files_in_folder(trie);
        }

        // Проверяем, есть ли вообще слова
        if (trie.total_unique_words() == 0) {
            system("cls");
            std::cout << "=======================================================================================================================\n";
            std::cout << "                                     ВНИМАНИЕ!\n";
            std::cout << "=======================================================================================================================\n";
            std::cout << "В выбранных файлах не найдено ни одного слова на кириллице.\n";
            std::cout << "Проверьте:\n";
            std::cout << "  • Кодировка файлов — ANSI (Windows-1251)\n";
            std::cout << "  • Наличие текста на русском языке\n";
            std::cout << "\nНажмите любую клавишу для возврата в меню...\n";
            _getch();
            continue;
        }

        // Получаем Top-K
        auto top_words = trie.get_top_k(k, (menu_choice == 2));

        // Выводим результат на экран
        display_results(top_words, k, mode_text, source_name, sort_mode);

        // Сохраняем в файл
        save_to_file(top_words, k, mode_text, source_name, sort_mode);

        // Экран завершения
        show_completion_screen(mode_text, k);
    }

    return 0;
}