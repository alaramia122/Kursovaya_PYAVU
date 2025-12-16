// output.cpp
// Финальный вывод: рамки, цвета, статистика, сохранение в файл

#include "Header.h"

void display_results(const std::vector<WordFrequency>& unsorted,
    int k,
    const std::string& mode,
    const std::string& source,
    SortMode sort) {
    // Копируем вектор, чтобы не портить оригинал
    std::vector<WordFrequency> top = unsorted;

    // === СОРТИРОВКА ===
    if (sort == SortMode::ByFrequency) {
        std::sort(top.begin(), top.end());  // уже есть operator< — по частоте
    }
    else if (sort == SortMode::Alphabetical) {
        std::sort(top.begin(), top.end(),
            [](const WordFrequency& a, const WordFrequency& b) {
                return a.word < b.word;
            });
    }
    // NoSort — ничего не делаем

    system("cls");
    system("color F0");

    std::cout << "=======================================================================================================================\n";
    std::cout << "                                          РЕЗУЛЬТАТ АНАЛИЗА\n";
    std::cout << "=======================================================================================================================\n\n";

    std::cout << "Режим анализа: " << mode << "\n";
    if (!source.empty()) std::cout << "Источник:      " << source << "\n";
    std::cout << "Запрошено:     Top-" << k << "\n";
    std::cout << "Найдено:       " << top.size() << " слов\n";

    std::string sort_text;
    if (sort == SortMode::ByFrequency)     sort_text = "по частоте (убывание)";
    else if (sort == SortMode::Alphabetical) sort_text = "по алфавиту";
    else                                   sort_text = "без сортировки";

    std::cout << "Сортировка:    " << sort_text << "\n\n";

    std::cout << "-----------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "  №   | Слово               | Частота   | Документы\n";
    std::cout << "-----------------------------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < top.size(); ++i) {
        std::cout << std::right << std::setw(3) << (i + 1) << "   | ";
        std::cout << std::left << std::setw(19) << top[i].word.substr(0, 19);
        std::cout << " | " << std::right << std::setw(8) << top[i].frequency;

        if (!top[i].documents.empty()) {
            std::cout << " | ";
            for (size_t j = 0; j < top[i].documents.size() && j < 3; ++j) {
                if (j > 0) std::cout << ", ";
                std::cout << top[i].documents[j];
            }
            if (top[i].documents.size() > 3) std::cout << "...";
        }
        std::cout << "\n";
    }

    std::cout << "-----------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "\nНажмите любую клавишу...\n";
    input_data_reader(true, false, false);
}

void save_to_file(const std::vector<WordFrequency>& unsorted,
    int k,
    const std::string& mode,
    const std::string& source_filename,
    SortMode sort) {

    std::vector<WordFrequency> top = unsorted;

    // Сортируем как на экране
    if (sort == SortMode::ByFrequency) {
        std::sort(top.begin(), top.end());
    }
    else if (sort == SortMode::Alphabetical) {
        std::sort(top.begin(), top.end(),
            [](const WordFrequency& a, const WordFrequency& b) {
                return a.word < b.word;
            });
    }

    std::string sort_str = (sort == SortMode::ByFrequency) ? "По_частоте" :
        (sort == SortMode::Alphabetical) ? "По_алфавиту" : "Без_сортировки";

    std::string folder = "Records/TopK_" + mode + "_" + std::to_string(k) + "_" + sort_str + "_" + source_filename;
    fs::create_directories(folder);

    std::string filename = folder + "/Top" + std::to_string(k) + "_" + source_filename + ".txt";
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "ОШИБКА: Не удалось создать файл для записи!\n";
        return;
    }

    file << "=======================================================================================\n";
    file << "                            TOP-" << k << " САМЫХ ЧАСТЫХ СЛОВ\n";
    file << "                            Сортировка: " << sort_str << "\n";
    file << "=======================================================================================\n\n";
    file << "Режим: " << mode << "\n";
    if (!source_filename.empty()) file << "Файл: " << source_filename << "\n";
    file << "Дата: " << __DATE__ << " " << __TIME__ << "\n\n";

    file << "-----------------------------------------------------------------------------------------------------------------------\n";
    file << "  №   Слово                 Частота     Документы\n";
    file << "-----------------------------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < top.size(); ++i) {
        const WordFrequency& wf = top[i];

        file << std::right << std::setw(3) << (i + 1) << "   ";
        file << std::left << std::setw(20) << wf.word.substr(0, 20);
        file << " " << std::right << std::setw(8) << wf.frequency;

        if (!wf.documents.empty()) {
            file << "   ";
            for (size_t j = 0; j < wf.documents.size(); ++j) {
                if (j > 0) file << ", ";
                file << wf.documents[j];
            }
        }
        file << "\n";
    }

    file << "-----------------------------------------------------------------------------------------------------------------------\n";
    file << "\nАнализ выполнен программой «Top-K частых слов через Trie»\n";
    file << "Автор: Осипенко Гавриил Васильевич, группа М7О-407С-22\n";

    file.close();

    std::cout << "[OK] Результат сохранён: " << filename << "\n\n";
}