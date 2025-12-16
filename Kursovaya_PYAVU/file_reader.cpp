// file_reader.cpp
// Чтение и обработка файлов

#include "Header.h"

std::string normalize_word(const std::string& raw) {
    // 1. Приводим к нижнему регистру через std::transform
    std::string lower_word = raw;
    std::transform(lower_word.begin(), lower_word.end(),
        lower_word.begin(),
        ::tolower);

    // 2. Очищаем от всех знаков препинания
    std::string clean_word;
    for (char c : lower_word) {
        std::string char_str(1, c);

        // Оставляем ТОЛЬКО русские буквы
        // 'р' — только кириллица
        // 'б' - кириллица и латиница
        // 'р' - только латиница
        if (contains_only(char_str, 'р') or contains_only(char_str, 'ц')) {
            clean_word += c;
        }
    }

    return clean_word;
}

void read_single_file(const std::string& filename, Trie& trie) {
    std::string full_path = "SourceTexts/" + filename;
    std::ifstream file(full_path);

    if (!file.is_open()) {
        std::cerr << "[ОШИБКА] Не удалось открыть файл: " << filename << "\n";
        return;
    }

    std::cout << "[OK] Обработка файла: " << filename << "\n";

    std::string line;
    int total_words = 0;

    while (std::getline(file, line)) {
        // 1. Разбиваем строку на слова по пробелам
        std::vector<std::string> words = Cutter_of_string(line, ' ');

        for (const std::string& word : words) {
            if (word.empty()) continue;

            // 2. Нормализуем: нижний регистр + только кириллица
            std::string clean = normalize_word(word);

            if (!clean.empty()) {
                trie.insert(clean, filename);
                total_words++;
            }
        }
    }

    file.close();
    std::cout << "[OK] Добавлено слов: " << total_words << " из файла " << filename << "\n";
}

void read_all_files_in_folder(Trie& trie) {
    if (!fs::exists("SourceTexts")) {
        std::cerr << "[ОШИБКА] Папка SourceTexts не найдена!\n";
        return;
    }

    int files_processed = 0;
    for (const auto& entry : fs::directory_iterator("SourceTexts")) {
        if (entry.path().extension() == ".txt") {
            std::string fname = entry.path().filename().string();
            read_single_file(fname, trie);
            files_processed++;
        }
    }

    if (files_processed == 0) {
        std::cout << "[ВНИМАНИЕ] Нет .txt файлов в папке SourceTexts!\n";
    }
    else {
        std::cout << "[ГОТОВО] Обработано файлов: " << files_processed << "\n";
    }
}