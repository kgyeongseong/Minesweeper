/**
* @file source.cpp
*/

#include <iostream>
#include <vector>

using namespace std;

const int BEGINNER     = 0;
const int INTERMEDIATE = 1;
const int ADVANCED     = 2;

const int MAXSIDE = 30; /**< ���� �ִ�� ũ�� */

int NROWS;    /**<    ���� �迭 �� ���� */
int NCOLUMNS; /**<    ���� �迭 �� ���� */
int MINES;    /**<    ���� �迭 ���� ���� */

/**
* @fn    void chooseDifficultyLevel()
* @brief ����ã�� ���̵� ���� �Լ�
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
* @brief ����ã�� ���� ġ��� �Լ�
*/
void clearBoards(char mineBoard[][MAXSIDE], char gameBoard[][MAXSIDE]) {
    /*���� ��ü ġ���*/
    for (int i = 0; i < NROWS; i++)
        for (int j = 0; j < NCOLUMNS; j++)
            gameBoard[i][j] = mineBoard[i][j] = '.';

    return;
}

/**
* @fn              void placeMines(char mineBoard[][MAXSIDE], int mines)
* @brief           ���� ��ġ �Լ�
* @param mineBoard ���� ���� �迭
* @param mines     ���� ��
*/
void placeMines(char mineBoard[][MAXSIDE], int mines) {
    /*���ڰ� ��ġ�� ��*/
    int placed = 0;

    while (placed < mines) {
        
        /*
        * int rand() �ּҰ� = -32727
        * int rand() �ִ밪 = 32727
        * random ���� �ּҰ� random ���� �ּҰ�  = (NROWS * NCOLUMNS) ���� �������� �����⸦ �Ͽ� �������� ���� �� = 0
        * BEGINNER ���̵� random ���� �ִ밪     = (NROWS * NCOLUMNS) ���� �������� �����⸦ �Ͽ� �������� {(NROWS * NCOLUMNS) - 1} �� �� = 80
        * INTERMEDIATE ���̵� random ���� �ִ밪 = (NROWS * NCOLUMNS) ���� �������� �����⸦ �Ͽ� �������� {(NROWS * NCOLUMNS) - 1} �� �� = 255
        * ADVANCED ���̵� random ���� �ִ밪     = (NROWS * NCOLUMNS) ���� �������� �����⸦ �Ͽ� �������� {(NROWS * NCOLUMNS) - 1} �� �� = 479
        */
        int random = rand() % (NROWS * NCOLUMNS);

                                                      /*
        * ���ڰ� �������� ���� ������
        * ex1) �ּ� random �� ����                     : 0   / 9  = 0
        * ex2) BEGINNER ���̵� �ִ� random �� ����     : 80  / 9  = 8
        * ex3) INTERMEDIATE ���̵� �ִ� random �� ���� : 255 / 16 = 15
        * ex3) ADVANCED ���̵� �ִ� random �� ����     : 479 / 30 = 15
        */
        int row = random / NCOLUMNS;

        /*
        * ���ڰ� �������� ���� ������
        * ex1) ADVANCED ���̵� �ּ� random �� ���� : 0   / 16 = 0
        * ex2) ADVANCED ���̵� �ִ� random �� ���� : 479 / 16 = 29
        */
        int col = random % NROWS;

        /*�������� ���õ� ���� ���� Ÿ�Ͽ� �̹� ���ڰ� ��ġ�� ���*/
        if (mineBoard[row][col] == '#') continue; /*���ڸ� ��ġ���� ����*/

        /*�������� ���õ� ���� ���� Ÿ�Ͽ� ���ڰ� ��ġ���� ���� ���*/
        mineBoard[row][col] = '#'; /*���� ��ġ*/

        /*���ڰ� ��ġ�� Ÿ���� �� ����*/
        placed++;
    }

    return;
}

/**
 * @fn              void replaceMine(int row, int col, char mineBoard[][MAXSIDE])
 * @brief           �÷��̾�� ó�� �Է� ���� ������ ���� ��ġ�� ���ڰ� �ִ� ��� �ش� ���� ���� ��ġ �����ϴ� �Լ�
 * @param row       ������ ��
 * @param col       ������ ��
 * @param mineBoard ���� ����
 */
void replaceMine(int row, int col, char mineBoard[][MAXSIDE]) {
    placeMines(mineBoard, 1);  /*������ �ٸ� �� ��ġ�� �� ���� 1�� ��ġ*/
    mineBoard[row][col] = '.'; /*������ �ش� �� ��ġ�� �ִ� ���� ����*/
    return;
}

/**
 * @fn          char indexToChar(int index)
 * @brief       0~29 ������ ���� ��, �� ���� ����ȭ
 * @param index ������ ��, �� ��
 */
char indexToChar(int index) {
    /*10 ���� ���� ������ ��� 0~9*/
    if (index < 10)
        /*10 ���� ���� ������ ����ȭ*/
        /* ex1) 0 + '0' (48, decimal) = '0' (char)*/
        /* ex2) 1 + '0' (48, decimal) = '1' (char)*/
        return index + '0';
    /*10 �̻��� ������ ���*/
    else
        /*10 �̻��� ������ ����ȭ*/
        /* ex1) 'a' (97, decimal) + (10 - 10) = 'a' (97, decimal)(char)*/
        /* ex2) 'a' (97, decimal) + (11 - 10) = 'b' (98, decimal)(char)*/
        /* ex3) ADVANCED ���̵� NCOLUMNS(�� ����) �ִ밪 29 ���� : 'a' (97, decimal) + (29 - 10) = 't' (116, decimal)(char)*/
        return 'a' + (index - 10);
}

/**
 * @fn       int charToIndex(char ch)
 * @brief    �÷��̾ �Է��� ��ġ '0'~'t' ������ ���ڸ� ����ȭ
 * @param ch �÷��̾ �Է��� ��ġ ����
 */
int charToIndex(char ch) {
    /*'0'~'9'�� ���ڸ� ����ȭ*/
    if (ch <= '9')
        /* ex1) '0' (48, decimal) - '0' (48, decimal) = 0 (decimal)*/
        /* ex2) '9' (57, decimal) - '0' (48, decimal) = 9 (decimal)*/
        return ch - '0';
    /*'a'~'t'�� ���ڸ� ����ȭ*/
    else
        /* ex1) ( 'a' (97, decimal) - 'a' (97, decimal) ) + 10 = 10 (decimal)*/
        /* ex2) ( 't' (116, decimal) - 'a' (97, decimal) ) + 10 = 29 (decimal)*/
        return (ch - 'a') + 10;
}

/**
 * @fn void displayBoard(char gameBoard[][MAXSIDE])
 * @brief ����ã�� ���� ��� �Լ�
 */
void displayBoard(char gameBoard[][MAXSIDE]) {
    cout << "  ";
    /*������ �� ���ٿ� �� ��ġ ���*/
    for (int i = 0; i < NCOLUMNS; i++)
        /*BEGINNER ���̵��� NCOLUMNS(�� ����) �ִ밪 9 ����      : '0'~'9' ���*/
        /*INTERMEDIATE ���̵��� NCOLUMNS(�� ����) �ִ밪 15 ���� : '0'~'f' ���*/
        /*ADVANCED ���̵��� NCOLUMNS(�� ����) �ִ밪 29 ����     : '0'~'t' ���*/
        cout << indexToChar(i) << ' ';
    cout << endl << endl;

    /**/
    /*������ �� ���ʿ� �� ��ġ ���*/
    for (int i = 0; i < NROWS; i++) {
        /*BEGINNER ���̵��� NROWS(�� ����) �ִ밪 9 ����      : '0'~'9' ���*/
        /*INTERMEDIATE ���̵��� NROWS(�� ����) �ִ밪 15 ���� : '0'~'f' ���*/
        /*ADVANCED ���̵��� NROWS(�� ����) �ִ밪 15 ����     : '0'~'f' ���*/
        cout << indexToChar(i) << ' ';

        for (int j = 0; j < NCOLUMNS; j++)
            /*����(���ں���X) ������ ���� ' '(����) ���� ä��*/
            cout << gameBoard[i][j] << ' ';

        /*������ �� �����ʿ� �� ��ġ ���*/
        cout << ' ' << indexToChar(i);

        cout << endl;
    }

    cout << endl << "   ";
    /*������ �� �Ʒ��ٿ� �� ��ġ ���*/
    for (int i = 0; i < NCOLUMNS; i++)
        cout << indexToChar(i) << ' ';
    cout << endl;

    return;
}

/**
 * @fn          bool isMine(int row, int col, char board[][MAXSIDE])
 * @brief       ���� üũ �Լ�
 * @param row   ������ ��
 * @param col   ������ ��
 * @param board ���� �迭
 */
bool isMine(int row, int col, char board[][MAXSIDE]) {
    return (board[row][col] == '#');
}

/**
 * @fn        bool isValid(int row, int col)
 * @brief     ���� ���ڰ� ������ �� �ִ� ��ġ���� Ȯ���ϴ� �Լ�
 * @param row ������ ��
 * @param col ������ ��
 * @return 
 */
bool isValid(int row, int col) {
    /*������ ���� �� ���� �ƴϰ� ������ �ǹ� �� �Ʒ��� �ƴϸ鼭*/
    /*������ �ǿ��� �� ������ �ƴϰ� ������ �ǿ����� �� �������� �ƴϸ�*/
    /*true ��ȯ*/
    return (row >= 0) && (row < NROWS) && (col >= 0) && (col < NCOLUMNS);
}

/**
 * @fn                vector<pair<int, int>> getNeighbours(int row, int col)
 * @brief             �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ��ȯ�ϴ� �Լ�
 * @param row         ������ ��
 * @param col         ������ ��
 * @return neighbours �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ����� ����
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

    /*�ش� ���� �Ʒ���, ����*/
    for (int dx = -1; dx <= 1; dx++)
        /*�ش� ���� ���ʿ�, ������ ���� �����ʿ�*/
        for (int dy = -1; dy <= 1; dy++)
            /*�ش� ���� �ƴ� ���*/
            if (dx != 0 || dy != 0)
                /*�ش� ���� ���ڰ� ������ �� �ִ� ��ġ���� Ȯ���ϴ� �Լ�*/
                /*�ش� ���� ���ڰ� ������ �� �ִ� ��ġ�̸�*/
                if (isValid(row + dx, col + dy))
                    /*neighbours ���Ϳ� �ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ ����*/
                    neighbours.push_back(make_pair(row + dx, col + dy));

    return neighbours;
}

/**
 * @fn              int countAdjacentMines(int row, int col, char mineBoard[][MAXSIDE])
 * @brief           �ش� �� �������� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ���ڼ��� ������ ī��Ʈ�ϴ� �Լ�
 * @param row       ������ ��
 * @param col       ������ ��
 * @param mineBoard ���� ����
 * @return          �ش� �� �������� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ���ڼ��� ���� ����
 */
int countAdjacentMines(int row, int col, char mineBoard[][MAXSIDE]) {
    vector<pair<int, int>> neighbours = getNeighbours(row, col);

    int count = 0;
    /*�ش� �� �������� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ���ڼ��� ������ ī��Ʈ*/
    for (int i = 0; i < neighbours.size(); i++)
        if (isMine(neighbours[i].first, neighbours[i].second, mineBoard))
            count++;

    return count;
}

/**
 * @fn              void uncoverBoard(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], int row, int col, int* nMoves)
 * @brief           ������ ���� ���� �Լ�
 * @param gameBoard ���� ����
 * @param mineBoard ���� ����
 * @param row       ������ ��
 * @param col       ������ ��
 * @param nMoves    �÷��̾�� ���� �Է� ���� ���� Ÿ���� ��ü ����
 */
void uncoverBoard(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], int row, int col, int* nMoves) {
    (*nMoves)++;
    /*�ش� �� �������� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ���ڼ��� ������ ī��Ʈ�ϴ� �Լ�*/
    int count = countAdjacentMines(row, col, mineBoard);
    /*ī��Ʈ�� ���ڰ��� ����ȭ*/
    gameBoard[row][col] = count + '0';

    /*�ش� �� ���� ������ ���� ��ġ�� ���ڰ� ������*/
    if (count == 0) {
        /*�ش� ���� ������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� ��ǥ�� ��ȯ�ϴ� �Լ�*/
        vector<pair<int, int>> neighbours = getNeighbours(row, col);

        /*������, ��, ��������, ����, ������, ���ʾƷ�, �Ʒ�, �����ʾƷ� �� '.'(���� ���� ���̸�)*/
        for (int i = 0; i < neighbours.size(); i++)
            if (gameBoard[neighbours[i].first][neighbours[i].second] == '.')
                /*������ ���� ���� �Լ�*/
                uncoverBoard(gameBoard, mineBoard, neighbours[i].first, neighbours[i].second, nMoves);
    }

    return;
}

/**
 * @fn              void markMines(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], bool won)
 * @brief           ������ ���� ���� ��� �Ǵ� ���� �����ϴ� �Լ�
 * \param gameBoard ���� ����
 * \param mineBoard ���� ����
 * \param won       �¸� Ȯ��
 */
void markMines(char gameBoard[][MAXSIDE], char mineBoard[][MAXSIDE], bool won) {
    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLUMNS; j++) {
            /*���� ������ �ش� ���� ��ĭ�̰� ���� ������ �ش� ���� �����̸�*/
            if (gameBoard[i][j] == '.' && mineBoard[i][j] == '#') {
                /*����ã�� ���ӿ��� �¸� ������*/
                if (won) {
                    /*�ش� ���� F (Flag, ���) ����*/
                    gameBoard[i][j] = 'F';
                }
                /*����ã�� ���ӿ��� �¸����� �ʾ�����*/
                else {
                    /*�ش� ���� Mine (#, ����) ����*/
                    gameBoard[i][j] = '#';
                }
            }
        }
    }
}

/**
* @fn    void playMinesweeper()
* @brief ����ã�� ���� �Լ�
*/
void playMinesweeper() {
    /*�ʱ�ȭ*/ 
    char mineBoard[MAXSIDE][MAXSIDE], gameBoard[MAXSIDE][MAXSIDE];

    /*������ ���ڰ� ���� ���� ��*/
    int nMovesTotal = NROWS * NCOLUMNS - MINES;

    /*����� �� == ���ڼ��� ����*/
    int flags = MINES;

    /*����ã�� ���� ġ��� �Լ�*/
    clearBoards(mineBoard, gameBoard);

    /*���� ��ġ �Լ�*/
    placeMines(mineBoard, MINES);

    /*���ڰ� ���� ���� ���� ���� ��*/
    int nMoves = 0;

    bool gameOver = false;

    /*����ã�� ������ ������ ���� ���*/
    while (!gameOver) {
        /*����ã�� ���� ��� �Լ�*/
        displayBoard(gameBoard);

        cout << flags << " flags left" << endl << endl;

        /*�÷��̾�� ���� ������ �� ��ġ�� �ൿ �Է� �ޱ�*/
        char x, y, z;
        cout << "Enter your move, (row, column, safe(s)/flag(f)) -> ";
        cin >> x >> y >> z;
        cout << endl;

        int row = charToIndex(x); /*�÷��̾�� ���� �Է� ���� �� ��ġ*/
        int col = charToIndex(y); /*�÷��̾�� ���� �Է� ���� �� ��ġ*/

        /*�÷��̾�� ó�� �Է� �޾��� ��*/
        /*ù ��° �õ��� ���*/
        if (nMoves == 0)
            /*���� üũ �Լ�*/
            /*ù ��° �õ����� ������ ���� �����̸�*/
            if (isMine(row, col, mineBoard))
                /*�ش� ���� ���� ��ġ �����ϴ� �Լ�*/
                replaceMine(row, col, mineBoard);

        /*�÷��̾ �ش� ���� ��ġ�� s(safe, ���ڰ� ����, ������)�� �Է��� ���*/
        if (z == 's') {
            /*�ش� ��ġ�� ���� ������ ������ ���� ��('.')�̰� ���� ������ ���ڰ� ���� ��ġ�� ���*/
            if (gameBoard[row][col] == '.' && mineBoard[row][col] == '.') {
                /*������ ���� ���� �Լ�*/
                uncoverBoard(gameBoard, mineBoard, row, col, &nMoves);
                /*���ڰ� ���� ���� ���� ���� ���� ������ ���ڰ� ���� ���� ���� ������*/
                if (nMoves == nMovesTotal) {
                    /*������ ���� ���� ��� �Ǵ� ���� �����ϴ� �Լ�*/
                    markMines(gameBoard, mineBoard, true);
                    /*����ã�� ���� ��� �Լ�*/
                    displayBoard(gameBoard);
                    cout << endl << "You won!!! :)" << endl;
                    gameOver = true;
                }
            }
            /*�ش� ��ġ�� ���� ������ ������ ���� ��('.')�̰� ���� ������ ���ڰ� �ִ� ��ġ�� ���*/
            else if (gameBoard[row][col] == '.' && mineBoard[row][col] == '#') {
                gameBoard[row][col] = '#';
                /*������ ���� ���� ��� �Ǵ� ���� �����ϴ� �Լ�*/
                markMines(gameBoard, mineBoard, false);
                /*����ã�� ���� ��� �Լ�*/
                displayBoard(gameBoard);
                cout << endl << "You lost! :(" << endl;
                gameOver = true;
            }
            /*������ �߸��� �� ��ġ ����*/
            else {
                cout << "Illegal move. ";
                if (gameBoard[row][col] == 'F')
                    cout << "Cell is a flag. Use f to toggle flag off. ";
                else
                    cout << "Cell is already a number. ";
                cout << endl;
            }
        }

        /*�÷��̾ �ش� ���� ��ġ�� f(flag, ���ڰ� �ִ�, ���)�� �Է��� ���*/
        if (z == 'f') {
            /*�ش� ���� ������ ���� ���*/
            if (gameBoard[row][col] == '.') {
                if (flags != 0) {
                    gameBoard[row][col] = 'F';
                    flags--;
                }
                /*���� ����� ���� ���� ���*/
                else {
                    cout << "Illegal move. Too many flags!" << endl;
                }
            }
            /*�ش� ���� ��ġ�� �̹� ����� �ִ� ���*/
            else if (gameBoard[row][col] == 'F') {
                /*��� ���� ���*/
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
    /*���� �� ������ ���� ���� �õ� ����*/
    srand(time(NULL));

    chooseDifficultyLevel();
    playMinesweeper();
    return 0;
}