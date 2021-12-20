/**
* @file source.cpp
*/

#include <iostream>
#include <vector>

using namespace std;

const int BEGINNER     = 0;
const int INTERMEDIATE = 1;
const int ADVANCED     = 2;

const int MAXSIDE = 30; /**< 보드 최대면 크기 */

int NROWS;    /**<    보드 배열 행 갯수 */
int NCOLUMNS; /**<    보드 배열 열 갯수 */
int MINES;    /**<    보드 배열 지뢰 갯수 */

/**
* @fn    void chooseDifficultyLevel()
* @brief 지뢰찾기 난이도 설정 함수
*/
void chooseDifficultyLevel() {
    int level;

    cout << "Enter the Difficulty Level" << endl;
    cout << "Press 0 for BEGINNER     (9  * 9 cells and 10 mines)" << endl;
    cout << "Press 1 for INTERMEDIATE (16 * 16 cells and 40 mines)" << endl;
    cout << "Press 2 for ADVANCED     (16 * 30 cells and 99 mines)" << endl;

    cin >> level;


    if (level == BEGINNER) {
        NROWS    = 9;
        NCOLUMNS = 9;
        MINES    = 10;
    }

    if (level == INTERMEDIATE) {
        NROWS    = 16;
        NCOLUMNS = 16;
        MINES    = 40;
    }

    if (level == ADVANCED) {
        NROWS    = 16;
        NCOLUMNS = 30;
        MINES    = 99;
    }

    return;
}

/**
* @fn    void clearBoards(char mineBoard[][MAXSIDE], char gameBoard[][MAXSIDE])
* @brief 지뢰찾기 보드 치우는 함수
*/
void clearBoards(char mineBoard[][MAXSIDE], char gameBoard[][MAXSIDE]) {
    /*보드 전체 치우기*/
    for (int i = 0; i < NROWS; i++)
        for (int j = 0; j < NCOLUMNS; j++)
            gameBoard[i][j] = mineBoard[i][j] = '.';

    return;
}

/**
* @fn              void placeMines(char mineBoard[][MAXSIDE], int mines)
* @brief           지뢰 설치 함수
* @param mineBoard 지뢰 보드 배열
* @param mines     지뢰 수
*/
void placeMines(char mineBoard[][MAXSIDE], int mines) {
    /*지뢰가 설치된 수*/
    int placed = 0;

    while (placed < mines) {
        
        /*
        * int rand() 최소값 = -32727
        * int rand() 최대값 = 32727
        * random 변수 최소값 random 변수 최소값  = (NROWS * NCOLUMNS) 값과 랜덤값이 나누기를 하여 나머지가 없을 때 = 0
        * BEGINNER 난이도 random 변수 최대값     = (NROWS * NCOLUMNS) 값과 랜덤값이 나누기를 하여 나머지가 {(NROWS * NCOLUMNS) - 1} 일 때 = 80
        * INTERMEDIATE 난이도 random 변수 최대값 = (NROWS * NCOLUMNS) 값과 랜덤값이 나누기를 하여 나머지가 {(NROWS * NCOLUMNS) - 1} 일 때 = 255
        * ADVANCED 난이도 random 변수 최대값     = (NROWS * NCOLUMNS) 값과 랜덤값이 나누기를 하여 나머지가 {(NROWS * NCOLUMNS) - 1} 일 때 = 479
        */
        int random = rand() % (NROWS * NCOLUMNS);

                                                      /*
        * 지뢰가 놓여지는 행을 결정함
        * ex1) 최소 random 값 기준                     : 0   / 9  = 0
        * ex2) BEGINNER 난이도 최대 random 값 기준     : 80  / 9  = 8
        * ex3) INTERMEDIATE 난이도 최대 random 값 기준 : 255 / 16 = 15
        * ex3) ADVANCED 난이도 최대 random 값 기준     : 479 / 30 = 15
        */
        int row = random / NCOLUMNS;

        /*
        * 지뢰가 놓여지는 열을 결정함
        * ex1) ADVANCED 난이도 최소 random 값 기준 : 0   / 16 = 0
        * ex2) ADVANCED 난이도 최대 random 값 기준 : 479 / 16 = 29
        */
        int col = random % NROWS;

        /*랜덤으로 선택된 지뢰 보드 타일에 이미 지뢰가 설치된 경우*/
        if (mineBoard[row][col] == '#') continue; /*지뢰를 설치하지 않음*/

        /*랜덤으로 선택된 지뢰 보드 타일에 지뢰가 설치되지 않은 경우*/
        mineBoard[row][col] = '#'; /*지뢰 설치*/

        /*지뢰가 설치된 타일의 수 증가*/
        placed++;
    }

    return;
}

/**
 * @fn              void replaceMine(int row, int col, char mineBoard[][MAXSIDE])
 * @brief           플레이어에게 처음 입력 받은 보드의 셀의 위치에 지뢰가 있는 경우 해당 셀의 지뢰 위치 변경하는 함수
 * @param row       보드의 행
 * @param col       보드의 열
 * @param mineBoard 지뢰 보드
 */
void replaceMine(int row, int col, char mineBoard[][MAXSIDE]) {
    placeMines(mineBoard, 1);  /*보드의 다른 셀 위치에 새 지뢰 1개 설치*/
    mineBoard[row][col] = '.'; /*보드의 해당 셀 위치에 있던 지뢰 제거*/
    return;
}

/**
 * @fn          char indexToChar(int index)
 * @brief       0~29 까지의 보드 행, 열 수를 문자화
 * @param index 보드의 행, 열 수
 */
char indexToChar(int index) {
    /*10 보다 작은 정수인 경우 0~9*/
    if (index < 10)
        /*10 보다 작은 정수를 문자화*/
        /* ex1) 0 + '0' (48, decimal) = '0' (char)*/
        /* ex2) 1 + '0' (48, decimal) = '1' (char)*/
        return index + '0';
    /*10 이상의 정수인 경우*/
    else
        /*10 이상의 정수를 문자화*/
        /* ex1) 'a' (97, decimal) + (10 - 10) = 'a' (97, decimal)(char)*/
        /* ex2) 'a' (97, decimal) + (11 - 10) = 'b' (98, decimal)(char)*/
        /* ex3) ADVANCED 난이도 NCOLUMNS(열 갯수) 최대값 29 기준 : 'a' (97, decimal) + (29 - 10) = 't' (116, decimal)(char)*/
        return 'a' + (index - 10);
}

/**
 * @fn       int charToIndex(char ch)
 * @brief    플레이어가 입력한 위치 '0'~'t' 까지의 문자를 정수화
 * @param ch 플레이어가 입력한 위치 문자
 */
int charToIndex(char ch) {
    /*'0'~'9'의 문자를 정수화*/
    if (ch <= '9')
        /* ex1) '0' (48, decimal) - '0' (48, decimal) = 0 (decimal)*/
        /* ex2) '9' (57, decimal) - '0' (48, decimal) = 9 (decimal)*/
        return ch - '0';
    /*'a'~'t'의 문자를 정수화*/
    else
        /* ex1) ( 'a' (97, decimal) - 'a' (97, decimal) ) + 10 = 10 (decimal)*/
        /* ex2) ( 't' (116, decimal) - 'a' (97, decimal) ) + 10 = 29 (decimal)*/
        return (ch - 'a') + 10;
}

/**
 * @fn void displayBoard(char gameBoard[][MAXSIDE])
 * @brief 지뢰찾기 보드 출력 함수
 */
void displayBoard(char gameBoard[][MAXSIDE]) {
    cout << "  ";
    /*보드의 맨 윗줄에 열 위치 출력*/
    for (int i = 0; i < NCOLUMNS; i++)
        /*BEGINNER 난이도의 NCOLUMNS(열 갯수) 최대값 9 기준      : '0'~'9' 출력*/
        /*INTERMEDIATE 난이도의 NCOLUMNS(열 갯수) 최대값 15 기준 : '0'~'f' 출력*/
        /*ADVANCED 난이도의 NCOLUMNS(열 갯수) 최대값 29 기준     : '0'~'t' 출력*/
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    /**/
    /*보드의 맨 왼쪽에 행 위치 출력*/
    for (int i = 0; i < NROWS; i++) {
        /*BEGINNER 난이도의 NROWS(행 갯수) 최대값 9 기준      : '0'~'9' 출력*/
        /*INTERMEDIATE 난이도의 NROWS(행 갯수) 최대값 15 기준 : '0'~'f' 출력*/
        /*ADVANCED 난이도의 NROWS(행 갯수) 최대값 15 기준     : '0'~'f' 출력*/
        cout << indexToChar(i) << ' ';

        for (int j = 0; j < NCOLUMNS; j++)
            /*게임(지뢰보드X) 보드의 열을 ' '(공백) 으로 채움*/
            cout << gameBoard[i][j] << ' ';

        /*보드의 맨 오른쪽에 행 위치 출력*/
        cout << ' ' << indexToChar(i);

        cout << endl;
    }

    cout << endl << "   ";
    /*보드의 맨 아랫줄에 열 위치 출력*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}

/**
 * @fn          bool isMine(int row, int col, char board[][MAXSIDE])
 * @brief       지뢰 체크 함수
 * @param row   보드의 행
 * @param col   보드의 열
 * @param board 보드 배열
 */
bool isMine(int row, int col, char board[][MAXSIDE]) {
    return (board[row][col] == '#');
}

/**
 * @fn        bool isValid(int row, int col)
 * @brief     셀에 지뢰가 존재할 수 있는 위치인지 확인하는 함수
 * @param row 보드의 행
 * @param col 보드의 열
 * @return 
 */
bool isValid(int row, int col) {
    /*보드의 맨위 행 위가 아니고 보드의 맨밑 행 아래가 아니면서*/
    /*보드의 맨왼쪽 열 왼쪽이 아니고 보드의 맨오른쪽 열 오른쪽이 아니면*/
    /*true 반환*/
    return (row >= 0) && (row < NROWS) && (col >= 0) && (col < NCOLUMNS);
}

/**
 * @fn                vector<pair<int, int>> getNeighbours(int row, int col)
 * @brief             해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표를 반환하는 함수
 * @param row         보드의 행
 * @param col         보드의 열
 * @return neighbours 해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표가 저장된 벡터
 */
vector<pair<int, int>> getNeighbours(int row, int col) {
    /*
        N.W    N    N.E
           \   |   /
            \  |  /
        W----Cell----E
            /  |  \
           /   |   \
        S.W    S    S.E

        Cell --> Current Cell ( row, col )
        N    --> North        ( row-1, col )
        S    --> South        ( row+1, col )
        E    --> East         ( row, col+1 )
        W    --> West         ( row, col-1 )
        N.E  --> North-East   ( row-1, col+1 )
        N.W  --> North-West   ( row-1, col-1 )
        S.E  --> South-East   ( row+1, col+1 )
        S.W  --> South-West   ( row+1, col-1 )
    */

    vector<pair<int, int>> neighbours;

    /*해당 셀의 아래행, 위행*/
    for (int dx = -1; dx <= 1; dx++)
        /*해당 셀의 왼쪽열, 선택한 셀의 오른쪽열*/
        for (int dy = -1; dy <= 1; dy++)
            /*해당 셀이 아닌 경우*/
            if (dx != 0 || dy != 0)
                /*해당 셀에 지뢰가 존재할 수 있는 위치인지 확인하는 함수*/
                /*해당 셀이 지뢰가 존재할 수 있는 위치이면*/
                if (isValid(row + dx, col + dy))
                    /*neighbours 벡터에 해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표 저장*/
                    neighbours.push_back(make_pair(row + dx, col + dy));

    return neighbours;
}

/**
 * @fn              int countAdjacentMines(int row, int col, char mineBoard[][MAXSIDE])
 * @brief           해당 셀 기준으로 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 지뢰수의 총합을 카운트하는 함수
 * @param row       보드의 행
 * @param col       보드의 열
 * @param mineBoard 지뢰 보드
 * @return          해당 셀 기준으로 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 지뢰수의 총합 갯수
 */
int countAdjacentMines(int row, int col, char mineBoard[][MAXSIDE]) {
    vector<pair<int, int>> neighbours = getNeighbours(row, col);

    int count = 0;
    /*해당 셀 기준으로 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 지뢰수의 총합을 카운트*/
    for (int i = 0; i < neighbours.size(); i++)
        if (isMine(neighbours[i].first, neighbours[i].second, mineBoard))
            count++;

    return count;
}

/**
 * @fn              void uncoverBoard(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], int row, int col, int* nMoves)
 * @brief           보드의 셀을 여는 함수
 * @param gameBoard 게임 보드
 * @param mineBoard 지뢰 보드
 * @param row       보드의 행
 * @param col       보드의 열
 * @param nMoves    플레이어로 부터 입력 받은 보드 타일의 전체 갯수
 */
void uncoverBoard(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], int row, int col, int* nMoves) {
    (*nMoves)++;
    /*해당 셀 기준으로 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 지뢰수의 총합을 카운트하는 함수*/
    int count = countAdjacentMines(row, col, mineBoard);
    /*카운트한 숫자값을 문자화*/
    gameBoard[row][col] = count + '0';

    /*해당 셀 기준 인접한 셀의 위치에 지뢰가 없으면*/
    if (count == 0) {
        /*해당 셀의 왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 좌표를 반환하는 함수*/
        vector<pair<int, int>> neighbours = getNeighbours(row, col);

        /*왼쪽위, 위, 오른쪽위, 왼쪽, 오른쪽, 왼쪽아래, 아래, 오른쪽아래 중 '.'(열지 않은 셀이면)*/
        for (int i = 0; i < neighbours.size(); i++)
            if (gameBoard[neighbours[i].first][neighbours[i].second] == '.')
                /*보드의 셀을 여는 함수*/
                uncoverBoard(gameBoard, mineBoard, neighbours[i].first, neighbours[i].second, nMoves);
    }

    return;
}

/**
 * @fn              void markMines(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], bool won)
 * @brief           보드의 지뢰 셀에 깃발 또는 지뢰 저장하는 함수
 * \param gameBoard 게임 보드
 * \param mineBoard 지뢰 보드
 * \param won       승리 확인
 */
void markMines(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], bool won) {
    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLUMNS; j++) {
            /*게임 보드의 해당 셀이 빈칸이고 지뢰 보드의 해당 셀이 지뢰이면*/
            if (gameBoard[i][j] == '.' && mineBoard[i][j] == '#') {
                /*지뢰찾기 게임에서 승리 했으면*/
                if (won) {
                    /*해당 셀에 F (Flag, 깃발) 저장*/
                    gameBoard[i][j] = 'F';
                }
                /*지뢰찾기 게임에서 승리하지 않았으면*/
                else {
                    /*해당 셀에 Mine (#, 지뢰) 저장*/
                    gameBoard[i][j] = '#';
                }
            }
        }
    }
}

/**
* @fn    void playMinesweeper()
* @brief 지뢰찾기 메인 함수
*/
void playMinesweeper() {
    /*초기화*/ 
    char mineBoard[MAXSIDE][MAXSIDE], gameBoard[MAXSIDE][MAXSIDE];

    /*보드의 지뢰가 없는 셀의 수*/
    int nMovesTotal = NROWS * NCOLUMNS - MINES;

    /*깃발의 수 == 지뢰수와 같음*/
    int flags = MINES;

    /*지뢰찾기 보드 치우는 함수*/
    clearBoards(mineBoard, gameBoard);

    /*지뢰 설치 함수*/
    placeMines(mineBoard, MINES);

    /*지뢰가 없는 셀이 열린 곳의 수*/
    int nMoves = 0;

    bool gameOver = false;

    /*지뢰찾기 게임이 끝나지 않은 경우*/
    while (!gameOver) {
        /*지뢰찾기 보드 출력 함수*/
        displayBoard(gameBoard);

        cout << flags << " flags left" << endl << endl;

        /*플레이어로 부터 보드의 셀 위치와 행동 입력 받기*/
        char x, y, z;
        cout << "Enter your move, (row, column, safe(s)/flag(f)) -> ";
        cin >> x >> y >> z;
        cout << endl;

        int row = charToIndex(x); /*플레이어로 부터 입력 받은 행 위치*/
        int col = charToIndex(y); /*플레이어로 부터 입력 받은 열 위치*/

        /*플레이어에게 처음 입력 받았을 때*/
        /*첫 번째 시도인 경우*/
        if (nMoves == 0)
            /*지뢰 체크 함수*/
            /*첫 번째 시도에서 선택한 셀이 지뢰이면*/
            if (isMine(row, col, mineBoard))
                /*해당 셀의 지뢰 위치 변경하는 함수*/
                replaceMine(row, col, mineBoard);

        /*플레이어가 해당 셀의 위치에 s(safe, 지뢰가 없는, 안전함)을 입력한 경우*/
        if (z == 's') {
            /*해당 위치가 게임 보드의 열리지 않은 셀('.')이고 지뢰 보드의 지뢰가 없는 위치인 경우*/
            if (gameBoard[row][col] == '.' && mineBoard[row][col] == '.') {
                /*보드의 셀을 여는 함수*/
                uncoverBoard(gameBoard, mineBoard, row, col, &nMoves);
                /*지뢰가 없는 셀이 열린 곳의 수가 보드의 지뢰가 없는 셀의 수와 같으면*/
                if (nMoves == nMovesTotal) {
                    /*보드의 지뢰 셀에 깃발 또는 지뢰 저장하는 함수*/
                    markMines(gameBoard, mineBoard, true);
                    /*지뢰찾기 보드 출력 함수*/
                    displayBoard(gameBoard);
                    cout << endl << "You won!!! :)" << endl;
                    gameOver = true;
                }
            }
            /*해당 위치가 게임 보드의 열리지 않은 셀('.')이고 지뢰 보드의 지뢰가 있는 위치인 경우*/
            else if (gameBoard[row][col] == '.' && mineBoard[row][col] == '#') {
                gameBoard[row][col] = '#';
                /*보드의 지뢰 셀에 깃발 또는 지뢰 저장하는 함수*/
                markMines(gameBoard, mineBoard, false);
                /*지뢰찾기 보드 출력 함수*/
                displayBoard(gameBoard);
                cout << endl << "You lost! :(" << endl;
                gameOver = true;
            }
            /*보드의 잘못된 셀 위치 선택*/
            else {
                cout << "Illegal move. ";
                if (gameBoard[row][col] == 'F')
                    cout << "Cell is a flag. Use f to toggle flag off. ";
                else
                    cout << "Cell is already a number. ";
                cout << endl;
            }
        }

        /*플레이어가 해당 셀의 위치에 f(flag, 지뢰가 있는, 깃발)을 입력한 경우*/
        if (z == 'f') {
            /*해당 셀이 열리지 않은 경우*/
            if (gameBoard[row][col] == '.') {
                if (flags != 0) {
                    gameBoard[row][col] = 'F';
                    flags--;
                }
                /*남은 깃발의 수가 없는 경우*/
                else {
                    cout << "Illegal move. Too many flags!" << endl;
                }
            }
            /*해당 셀의 위치에 이미 깃발이 있는 경우*/
            else if (gameBoard[row][col] == 'F') {
                /*깃발 적용 취소*/
                gameBoard[row][col] = '.';
                flags++;
            }
            else {
                cout << "Illegal move. Cell is a number. " << endl;
            }
        }
    }

    return;
}

/**
* @fn int main()
*/
int main()
{
    /*랜덤 수 설정을 위한 랜덤 시드 설정*/
    srand(time(NULL));

    chooseDifficultyLevel();
    playMinesweeper();
    return 0;
}