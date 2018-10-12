#include "viewdraw.h"
#include "ui_viewdraw.h"

ViewDraw::ViewDraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDraw)
{
    ui->setupUi(this);

    int maxSize=6;
    int rounds=3;
    ui->viewDrawTable->setRowCount(maxSize/2*rounds+(2*rounds)-1);
    ui->viewDrawTable->setColumnCount(maxSize-1);
    QVector<QVector <int>> draw;
    QVector<QVector <QString>> drawPretty;

    for(int x = 0; x < maxSize; x++)
    {
        draw.push_back(QVector <int>(maxSize));
    }
    for(int x = 0; x< maxSize/2;x++)
    {
        drawPretty.push_back(QVector <QString>(maxSize-1));
    }


    draw[0][0] = 1;
    draw[maxSize-1][0] = 1;


    for(int x = 0; x < maxSize-1; x++)
        for(int y = 0; y < maxSize-1; y++)
        {
            if(x == 0)
            {
                draw[x][y] = y+1;
                continue;
            }

            if(draw[x-1][y]+1 == maxSize)
                draw[x][y] = 1;
            else
                draw[x][y] = draw[x-1][y] + 1;

            if(x==y)
            {
                draw[maxSize-1][y] = draw[x][y];
            }
        }

    for(int x=0; x<maxSize; x++)
    {
        QString out = "";
        for(int y = 0; y< maxSize-1; y++)
        {
            out += "[" + QString::number(draw[x][y]) + "]";
        }
        qDebug() << out;
    }


    for(int x=1; x<maxSize; x++)
    {
        for(int y = 0; y< x; y++)
        {
            for(int z = 0; z< maxSize/2; z++)
            {
                if(drawPretty[z][draw[x][y]-1] == "")
                {

                    drawPretty[z][draw[x][y]-1] = (QString::number(x+1) + " v " + QString::number(y+1));
                    break;
                }
            }
        }
    }
    int roundRow=0;
    for (int currRound = 0; currRound < rounds; currRound++)
    {
        for(int y = 0; y<maxSize-1; y++)
        {
            QTableWidgetItem *box = new QTableWidgetItem("R" + QString::number(currRound+1) + "B" + QString::number(y+1));
            ui->viewDrawTable->setItem(roundRow, y, box);
        }
        roundRow+=5;
    }
    roundRow=0;
    for (int currRound = 0; currRound < rounds; currRound++)
    {
        for(int x = 0; x < maxSize/2; x++)
        {
            for(int y = 0; y < maxSize-1; y++)
            {
                if(currRound%2==1)
                {
                    QStringList tempMatch = drawPretty[x][y].split(" ");
                    QTableWidgetItem *match = new QTableWidgetItem(tempMatch[2] + " v " + tempMatch[0]);
                    ui->viewDrawTable->setItem(roundRow+x+1, y, match);

                }
                else
                {
                    QTableWidgetItem *match =  new QTableWidgetItem(drawPretty[x][y]);
                    ui->viewDrawTable->setItem(roundRow+x+1, y, match);
                }
               // match->setBackgroundColor(Qt::red);
            }
        }
        roundRow+=5;
    }
}


ViewDraw::~ViewDraw()
{
    delete ui;
}
