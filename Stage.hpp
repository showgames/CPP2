enum OBJECT {
    WALL,
    GOAL,
    ITEM,
    ITEM_ON_GOAL,
    PLAYER,
    PLAYER_ON_GOAL,
    EMP,
};

const int dirX[4] = {0, 0, -1, 1};
const int dirY[4] = {-1, 1, 0, 0};

class Stage
{
    public:
    void m_init(char* stageData, int sizeX, int sizeY);
    void m_draw();
    void m_update(int dir);
    bool m_checkFinish();

    private:
    void m_searchPlayerPos(int* x, int* y);
    int m_stageSizeX;
    int m_stageSizeY;
    OBJECT* m_board;
};