#include "Stage.hpp"
#include <ncurses.h>

void
Stage::m_init(char* stageData, int sizeX, int sizeY)
{
    m_stageSizeX = sizeX;
    m_stageSizeY = sizeY;
    m_board = new OBJECT[m_stageSizeX * m_stageSizeY];

    for (int i = 0; i < m_stageSizeX * m_stageSizeY; ++i) {
        OBJECT obj;
        switch(stageData[i]) {
            case '#': obj = WALL; break;
            case '.': obj = GOAL; break;
            case 'o': obj = ITEM; break;
            case 'O': obj = ITEM_ON_GOAL; break;
            case 'p': obj = PLAYER; break;
            case 'P': obj = PLAYER_ON_GOAL; break;
            case ' ': obj = EMP; break;
            default: break;
        }
        m_board[i] = obj;
    }
}

void
Stage::m_draw()
{
    int px, py;
    char obj[] = {'#', '.', 'o', 'O', 'p', 'P', ' '};
    for (int i = 0; i < m_stageSizeX * m_stageSizeY; i++) {
        int y = i / m_stageSizeX;
        int x = i % m_stageSizeX;
        move(y, x);
        addch(obj[m_board[i]]);
    }
}

bool
Stage::m_checkFinish()
{
    for (int i = 0; i < m_stageSizeX * m_stageSizeY; ++i) {
        if (m_board[i] == ITEM) return FALSE;
    }
    return TRUE;
}

void
Stage::m_update(int dir)
{
    int x, y;
    m_searchPlayerPos(&x, &y);
    int dx = dirX[dir], dy = dirY[dir];
    int tx = x + dx, ty = y + dy;
    int np = y * m_stageSizeX + x;
    int tp = ty * m_stageSizeX + tx;
    int tp2 = (ty + dy) * m_stageSizeX + (tx + dx);

    if (m_board[tp] == EMP) {
        m_board[tp] = PLAYER;
        m_board[np] = (m_board[np] == PLAYER_ON_GOAL)? GOAL : EMP;
    } else if (m_board[tp] == GOAL) {
        m_board[tp] = PLAYER_ON_GOAL;
        m_board[np] = (m_board[np] == PLAYER_ON_GOAL)? GOAL : EMP;
    } else if (m_board[tp] == ITEM) {
        if (m_board[tp2] == EMP) {
            m_board[tp2] = ITEM;
            m_board[tp] = PLAYER;
            m_board[np] = (m_board[np] == PLAYER_ON_GOAL) ? GOAL : EMP;
        } else if (m_board[tp2] == GOAL) {
            m_board[tp2] = ITEM_ON_GOAL;
            m_board[tp] = PLAYER;
            m_board[np] = (m_board[np] == PLAYER_ON_GOAL) ? GOAL : EMP;
        } 
    } else if (m_board[tp] == ITEM_ON_GOAL) {
        if (m_board[tp2] == EMP) {
            m_board[tp2] = ITEM;
            m_board[tp] = PLAYER_ON_GOAL;
            m_board[np] = (m_board[np] == PLAYER_ON_GOAL) ? GOAL : EMP;
        } else if (m_board[tp2] == GOAL) {
            m_board[tp2] = ITEM_ON_GOAL;
            m_board[tp] = PLAYER_ON_GOAL;
            m_board[np] = (m_board[np] == PLAYER_ON_GOAL) ? GOAL : EMP;
        } 
    }
}

void
Stage::m_searchPlayerPos(int* x, int* y)
{
    for (int i = 0; i < m_stageSizeX * m_stageSizeY; ++i) {
        if (m_board[i] == PLAYER || m_board[i] == PLAYER_ON_GOAL) {
            *y = i / m_stageSizeX;
            *x = i % m_stageSizeX;
        }
    }
}