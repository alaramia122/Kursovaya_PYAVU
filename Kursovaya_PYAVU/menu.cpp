// menu.cpp
// Интерфейсная часть проекта: красиво, с рамками, на русском.

#include "Header.h"

void show_start_window() {
    system("cls");
    system("color F0");

    std::cout << "\n\n";
    std::cout << "=======================================================================================================================\n";
    std::cout << "                                 АНАЛИЗАТОР ЧАСТОТЫ СЛОВ В ТЕКСТЕ\n";
    std::cout << "                                 Префиксное дерево + Top-K\n";
    std::cout << "                                 Курсовая работа по ПЯВУ\n";
    std::cout << "=======================================================================================================================\n";
    std::cout << "Автор: Осипенко Гавриил Васильевич, группа М7О-407С-22\n";
    std::cout << "Год:   2025\n";
    std::cout << "\n";
    std::cout << "ВАЖНО: Все текстовые файлы в папке SourceTexts должны быть сохранены\n";
    std::cout << "       в кодировке ANSI (Windows-1251), иначе русский текст может отображаться некорректно!\n";
    std::cout << "\n";
    std::cout << "Папка с текстами: SourceTexts (должна быть рядом с программой)\n";
    std::cout << "Результаты сохраняются в: Records\n";
    std::cout << "\n";
    std::cout << "Нажмите любую клавишу для продолжения...\n";
    input_data_reader(true, false, false);  // ждём любую клавишу, эхо выключено
}

int show_main_menu() {
    while (true) {
        system("cls");
        std::cout << "=======================================================================================================================\n";
        std::cout << "                                             ГЛАВНОЕ МЕНЮ\n";
        std::cout << "=======================================================================================================================\n";
        std::cout << "1. Анализ одного файла\n";
        std::cout << "2. Анализ всех файлов в папке SourceTexts\n";
        std::cout << "3. Выход\n";
        std::cout << "=======================================================================================================================\n";

        Input_data input = input_data_reader(false, true, false);
        if (input.Esc_controller) {
            return 3;
        }
        if (!input.result.empty()) {
            if (input.result == "1") return 1;
            if (input.result == "2") return 2;
            if (input.result == "3") return 3;
        }
    }
}

std::string choose_source_file() {
    while (true) {
        system("cls");
        std::vector<std::string> files;
        int current_number = 1;

        std::cout << "=======================================================================================================================\n";
        std::cout << "                                           ВЫБОР ФАЙЛА\n";
        std::cout << "=======================================================================================================================\n";
        std::cout << "ВНИМАНИЕ: Файлы должны быть в кодировке ANSI (Windows-1251)!\n";
        std::cout << "          Иначе русский текст может читаться с ошибками.\n";
        std::cout << "Папка: SourceTexts\n";
        std::cout << "=======================================================================================================================\n";
        
        if (!fs::exists("SourceTexts")) {
            std::cout << "ОШИБКА: Папка SourceTexts не найдена!\n";
            std::cout << "Создайте папку и положите туда текстовые файлы.\n\n";
            std::cout << "Нажмите клавишу для возврата в меню...\n";
            input_data_reader(true, false, false);
            return "";
        }

        for (const auto& entry : fs::directory_iterator("SourceTexts")) {
            if (entry.path().extension() == ".txt") {
                std::cout << current_number << ". " << entry.path().filename().string() << "\n";
                files.push_back(entry.path().filename().string());
                current_number++;
            }
        }

        if (files.empty()) {
            std::cout << "В папке SourceTexts нет .txt файлов!\n\n";
            std::cout << "Нажмите клавишу для возврата...\n";
            input_data_reader(true, false, false);
            return "";
        }

        std::cout << "=======================================================================================================================\n";
        std::cout << "Введите номер файла (или Esc для отмены) > ";

        Input_data input = input_data_reader(true, true, false);

        if (input.Esc_controller) {
            return "";
        }

        if (input.Enter_controller and !input.result.empty() and contains_only(input.result, 'ц')) {
            int choice = std::stoi(input.result);
            if (choice >= 1 and choice <= static_cast<int>(files.size())) {
                return files[choice - 1];
            }
        }
    }
}

SortMode choose_sort_mode() {
    while (true) {
        system("cls");
        std::cout << "=======================================================================================================================\n";
        std::cout << "                                          СОРТИРОВКА РЕЗУЛЬТАТА\n";
        std::cout << "=======================================================================================================================\n";
        std::cout << "1. По частоте (от большего к меньшему) > рекомендуется\n";
        std::cout << "2. По алфавиту (А > Я)\n";
        std::cout << "3. Без сортировки (в порядке обхода дерева)\n";
        std::cout << "0. Назад\n";
        std::cout << "=======================================================================================================================\n";
        std::cout << "Ваш выбор > ";

        Input_data input = input_data_reader(true, true, false);

        if (input.Esc_controller || (input.Enter_controller && input.result == "0")) {
            return SortMode::ByFrequency;  // по умолчанию
        }

        if (input.Enter_controller && !input.result.empty()) {
            if (input.result == "1") return SortMode::ByFrequency;
            if (input.result == "2") return SortMode::Alphabetical;
            if (input.result == "3") return SortMode::NoSort;
        }
    }
}

int input_top_k() {
    while (true) {
        system("cls");
        std::cout << "=======================================================================================================================\n";
        std::cout << "                                       НАСТРОЙКА АНАЛИЗА\n";
        std::cout << "=======================================================================================================================\n";
        std::cout << "Сколько самых частых слов показать? (например, 10, 50, 100)\n";
        std::cout << "Введите число > ";

        Input_data input = input_data_reader(true, true, false);

        if (input.Esc_controller) {
            return -1;
        }

        if (input.Enter_controller and !input.result.empty() and contains_only(input.result, 'ц')) {
            int k = std::stoi(input.result);
            if (k > 0) {
                return k;
            }
        }
    }
}

void show_completion_screen(const std::string& mode, int k) {
    system("cls");
    std::cout << "=======================================================================================================================\n";
    std::cout << "                                            АНАЛИЗ ЗАВЕРШЁН\n";
    std::cout << "=======================================================================================================================\n";
    std::cout << "Режим: " << mode << "\n";
    std::cout << "Top-" << k << " самых частых слов выведены на экран и сохранены в файл.\n";
    std::cout << "\nПуть: Records/\n";
    std::cout << "\n\nНажмите любую клавишу для возврата в главное меню...\n";

    input_data_reader(true, false, false);  // ждём любую клавишу
}