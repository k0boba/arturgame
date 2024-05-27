#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;

// Размеры игрового поля
const int ROWS = 6;
const int COLS = 7;

// Функция для вывода игрового поля в виде таблицы
void draw_board(char board[ROWS][COLS]) {
    // Выводим верхнюю границу
    cout << "-----------------------------" << endl;

    // Выводим содержимое поля
    for (int i = 0; i < ROWS; ++i) {
        if (i == 6) {
            cout << "|---------------------------|" << endl;
            cout << "| ";
            for (int j = 0; j < COLS; ++j) {
                cout << board[i][j] << " | ";
            }
            cout << endl;
        }
        cout << "| ";
        for (int j = 0; j < COLS; ++j) {
            cout << board[i][j] << " | ";
        }
        cout << endl;
    }

    // Выводим нижнюю границу
    cout << "-----------------------------" << endl << endl;

}

void init_board(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == 6)
                board[i][j] = j + '1';
            else
            board[i][j] = '_';
        }
    }
}

// Функция для совершения хода игрока
void make_move(char board[ROWS][COLS], int col, char player_symbol, bool is_computer) {
    // Проверяем, является ли ход компьютера
    if (is_computer) {
        // Пока выбранный столбец заполнен, выбираем новый случайный столбец
        while (board[0][col] != '_') {
            col = rand() % COLS;
        }
    }
    else {
        // Обычная проверка ввода для игрока
        while (cin.fail() || col < 0 || col > COLS-1 || board[0][col] != '_' ) {
            if (cin.fail() || col < 0 || col > COLS-1) {
                cout << "Некорректный ввод. Введите число от 1 до 7: ";
                cin.clear(); // Очищаем флаг ошибки ввода
                cin.ignore(1000, '\n'); // Очищаем буфер ввода
            }
            else if (board[0][col] != '_') {
                cout << "Столбец уже полностью заполнен. Выберите другой столбец: ";
            }
            cin >> col;
            col--; // Так как столбцы нумеруются с 1, а массивы с 0
        }
    }
    // Сделать ход в выбранный столбец
    bool valid_move = false;
    for (int i = ROWS; i >= 0; --i) {
        if (board[i][col] == '_') {
            board[i][col] = player_symbol;
            valid_move = true;
            break;
        }
    }
}



bool check_winner(char board[ROWS][COLS], char player_symbol) {
    // Проверка по горизонтали
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player_symbol && board[i][j + 1] == player_symbol && board[i][j + 2] == player_symbol && board[i][j + 3] == player_symbol) {
                return true;
            }
        }
    }

    // Проверка по вертикали
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS - 3; ++j) {
            if (board[j][i] == player_symbol && board[j + 1][i] == player_symbol && board[j + 2][i] == player_symbol && board[j + 3][i] == player_symbol) {
                return true;
            }
        }
    }

    // Проверка по диагонали (вверх-вправо)
    for (int i = 0; i < ROWS - 3; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player_symbol && board[i + 1][j + 1] == player_symbol && board[i + 2][j + 2] == player_symbol && board[i + 3][j + 3] == player_symbol) {
                return true;
            }
        }
    }

    // Проверка по диагонали (вниз-вправо)
    for (int i = 3; i < ROWS; ++i) {
        for (int j = 0; j < COLS - 3; ++j) {
            if (board[i][j] == player_symbol && board[i - 1][j + 1] == player_symbol && board[i - 2][j + 2] == player_symbol && board[i - 3][j + 3] == player_symbol) {
                return true;
            }
        }
    }

    return false;
}

bool ask_for_restart() {
    char choice;
    cout << "Хотите ли вы сыграть еще одну партию? (y/n): ";
    cin >> choice;

    // Преобразуем выбор пользователя к нижнему регистру для унификации сравнения
    choice = tolower(choice);

    // Проверяем, был ли введен корректный ответ
    while (choice != 'y' && choice != 'n') {
        cout << "Некорректный ввод. Пожалуйста, введите 'y' или 'n': ";
        cin >> choice;
        choice = tolower(choice); // Преобразуем ответ к нижнему регистру
    }

    return (choice == 'y');
}

// Функция для игры в "Четыре в ряд"
void play_connect_four_2player() {
    char player_symbol = 'X';
    bool play_again = true;

    while (play_again) {
        bool game_over = false;
        char board[ROWS][COLS];
        init_board(board);

        // Выводим игровое поле
        draw_board(board);

        while (!game_over) {
            // Ход игрока
            int col;
            cout << "Ход игрока " << player_symbol << ": ";
            cin >> col;
            col--; // Так как столбцы нумеруются с 1, а массивы с 0
            make_move(board, col, player_symbol, false); // Указываем, что ходит игрок
            draw_board(board);

            // Проверяем, выиграл ли игрок
            if (check_winner(board, player_symbol)) {
                cout << "Игрок " << player_symbol << " выиграл!" << endl;
                game_over = true;
            }

            // Проверяем, закончилась ли игра вничью
            bool board_full = true;
            for (int i = 0; i < COLS; ++i) {
                if (board[0][i] == '_') {
                    board_full = false;
                    break;
                }
            }
            if (board_full) {
                cout << "Ничья!" << endl;
                game_over = true;
            }

            // Меняем символ игрока для следующего хода
            player_symbol = (player_symbol == 'X') ? 'O' : 'X';
        }

        // Спрашиваем пользователя, хочет ли он сыграть ещё раз
        play_again = ask_for_restart();
    }

    cout << "Спасибо за игру! До новых встреч!\n";
}

void play_connect_four_1player() {
    char player_symbol = 'X', bot_symbol = 'O';
    bool play_again = true;

    while (play_again) {
        bool game_over = false;
        char board[ROWS][COLS];
        init_board(board);

        // Выводим игровое поле
        draw_board(board);
        bool turn_player = true;

        while (!game_over) {
            // Ход игрока
            if (turn_player) {
                int col;
                cout << "Ход игрока " << player_symbol << ": ";
                cin >> col;
                col--; // Так как столбцы нумеруются с 1, а массивы с 0
                make_move(board, col, player_symbol, false); // Указываем, что ходит игрок
                draw_board(board);

                // Проверяем, выиграл ли игрок
                if (check_winner(board, player_symbol)) {
                    cout << "Игрок " << player_symbol << " выиграл!" << endl;
                    game_over = true;
                }

                // Проверяем, закончилась ли игра вничью
                bool board_full = true;
                for (int i = 0; i < COLS; ++i) {
                    if (board[0][i] == '_') {
                        board_full = false;
                        break;
                    }
                }
                if (board_full) {
                    cout << "Ничья!" << endl;
                    game_over = true;
                }
                turn_player = false;
            }
            else {
                int col = rand() % COLS;
                for (int maybe_col = 0; maybe_col < COLS; ++maybe_col) {
                    // Проверяем, можно ли сделать ход в этот столбец
                    if (board[0][maybe_col] == '_') {
                        // Создаем копию доски
                        char temp_board[ROWS][COLS];
                        for (int i = 0; i < ROWS; ++i) {
                            for (int j = 0; j < COLS; ++j) {
                                temp_board[i][j] = board[i][j];
                            }
                        }

                        // Делаем временный ход в этот столбец
                        make_move(temp_board, maybe_col, bot_symbol, true);

                        // Проверяем, выиграл ли компьютер этим ходом
                        if (check_winner(temp_board, bot_symbol)) {
                            col = maybe_col;
                            break;
                        }
                    }
                }
                cout << "Ход компьютера " << bot_symbol << ": " << endl;
                make_move(board, col, bot_symbol, true); // Указываем, что ходит компьютер
                draw_board(board);

                // Проверяем, выиграл ли компьютер
                if (check_winner(board, bot_symbol)) {
                    cout << "Компьютер " << bot_symbol << " выиграл!" << endl;
                    game_over = true;
                }

                // Проверяем, закончилась ли игра вничью
                bool board_full = true;
                for (int i = 0; i < COLS; ++i) {
                    if (board[0][i] == '_') {
                        board_full = false;
                        break;
                    }
                }
                if (board_full) {
                    cout << "Ничья!" << endl;
                    game_over = true;
                }
                turn_player = true;
                    }
                }
         
        // Спрашиваем пользователя, хочет ли он сыграть ещё раз
        play_again = ask_for_restart();
    }

    cout << "Спасибо за игру! До новых встреч!\n";
}

void main()
{
    setlocale(0, "");
    srand(time(0));

    cout << "Вас приветствует игра \"Четыре в ряд\"\n\n\n\
Правила игры:\n\n\
Есть игровое поле размером 6х7\n\
Игроки по очереди добавляют свои фишки в любой свободный столбец.\n\
Фишка всегда падает в самое нижнее свободное место в столбце\n\
Цель игры - собрать свои 4 фишки подряд по горизонтали, вертикали или диагонали\n\
Первый игрок, который соберет 4 фишки подряд, выигрывает партию\n\
Если на игровой доске заканчивается место для ходов, и никто не собрал 4 фишки подряд, игра заканчивается вничью\n\n\
В этой игре есть два режима:\n\
1) P1 vs P2 - режим игры для двоих человек\n\
2) P1 vs ИИ - режим игры против компьютера\n\n\
Выберите режим игры 1 или 2: ";
   
    char mod;
    cin >> mod;
    while (mod != '1' && mod != '2') {
        cout << "Некорректный ввод. Пожалуйста, введите '1' или '2': ";
        cin >> mod;
    }

    if (mod == '1')
        play_connect_four_2player();
    else
        play_connect_four_1player();
}



