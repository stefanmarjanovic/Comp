#include "competition.h"

extern QSqlDatabase tennisTestDB;
Competition::Competition()  //generic constructor
{
        id = 0;

        division = 0;
        rounds = 0;
        boxes = 0;
        teams = 0;

        name = " ";
        startDate = "";
        finishDate = "";
        year = "";

        teamIds = new int[teams];
}

void Competition::addNewComp(){


}

void Competition::addMatch(int r, int c, int val)
{
    this->draw[r][c] = val;
}

