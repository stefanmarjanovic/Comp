#include "viewdraw.h"
#include "ui_viewdraw.h"

#include <QFileDialog>
#include <QtWidgets>
#include <QPrinter>

ViewDraw::ViewDraw(QString id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDraw)
{
    ui->setupUi(this);
    this->id = id;

    QStringList divisionList = Database::search("DIVISION", "id", "compID = " + id);
    int tableRows = 0;
    int tableColumns =0;
    int roundRow=0;
    int rounds =  Database::search("COMPETITION", "rounds", "id = " + id).first().toInt();
    htmlOut = "";
   // htmlOut += "<img src=\":/logo.png\" style='width:100%'/>";
    htmlOut +="<h1>" + QString(Database::search("COMPETITION", "name", "id =" + id)[0]) + "</h1>";

    for (QString divisionID : divisionList)
    {
        qDebug() << "div id is" << divisionID;

        int teamCount = QString(Database::search("Team", "count(*)", "division_id = " + divisionID).first()).toInt();
        QStringList teamNames = Database::search("TEAM", "name", "division_id = " + divisionID);
        tableRows+= ((teamCount/2)*rounds) + (4*rounds);
        ui->viewDrawTable->setRowCount(tableRows);
        float fontSize = 13 * 13/teamCount;
        qDebug() << "font size is " << fontSize;

        if(teamCount-1>tableColumns) //change only if different division has a greater amount of teams.
            tableColumns=teamCount-1;
        ui->viewDrawTable->setColumnCount(tableColumns);

        QVector<QVector <int>> draw;
        QVector<QVector <QString>> drawPretty;

        for(int x = 0; x < teamCount; x++)
        {
            draw.push_back(QVector <int>(teamCount));
        }
        for(int x = 0; x< teamCount/2;x++)
        {
            drawPretty.push_back(QVector <QString>(teamCount-1));
        }

        draw[0][0] = 1;
        draw[teamCount-1][0] = 1;

        for(int x = 0; x < teamCount-1; x++)
            for(int y = 0; y < teamCount-1; y++)
            {
                if(x == 0)
                {
                    draw[x][y] = y+1;
                    continue;
                }

                if(draw[x-1][y]+1 == teamCount)
                    draw[x][y] = 1;
                else
                    draw[x][y] = draw[x-1][y] + 1;

                if(x==y)
                {
                    draw[teamCount-1][y] = draw[x][y];
                }
            }

        for(int x=0; x<teamCount; x++)
        {
            QString out = "";
            for(int y = 0; y< teamCount-1; y++)
            {
                out += "[" + QString::number(draw[x][y]) + "]";
            }
            qDebug() << out;
        }


        for(int x=1; x<teamCount; x++)
        {
            for(int y = 0; y< x; y++)
            {
                for(int z = 0; z< teamCount/2; z++)
                {
                    if(drawPretty[z][draw[x][y]-1] == "")
                    {

                        drawPretty[z][draw[x][y]-1] = (QString::number(x+1) + " v " + QString::number(y+1));
                        break;
                    }
                }
            }
        }
        roundRow++;
        QTableWidgetItem *division = new QTableWidgetItem(Database::search("DIVISION", "name", "id = " + divisionID).first());
        htmlOut += "<h2>" + division->text() + "</h2>";
        ui->viewDrawTable->setItem(roundRow, 0, division);

        for (int currRound = 0; currRound < rounds; currRound++)
        {
            roundRow++;
            QTableWidgetItem *round = new QTableWidgetItem("Round " + QString::number(currRound+1));
            ui->viewDrawTable->setItem(roundRow, 0, round);

            roundRow++;
            htmlOut += "<h2>" + round->text() + "</h2><table>";
            for(int x = -1; x < teamCount/2; x++)
            {
                htmlOut+= "<tr>";
                for(int y = 0; y < teamCount-1; y++)
                {
                    if(x == -1)
                    {
                        QTableWidgetItem *box = new QTableWidgetItem("R" + QString::number(currRound+1) + "B" + QString::number(y+1));
                         ui->viewDrawTable->setItem(roundRow, y, box);
                        htmlOut+= "<th>" + box->text() + " </th>";
                    }
                    else if(currRound%2==1)
                    {
                        QStringList tempMatch = drawPretty[x][y].split(" ");
                        QTableWidgetItem *match = new QTableWidgetItem(teamNames[ tempMatch[2].toInt()-1 ] + " v " + teamNames[tempMatch[0].toInt()-1]);
    //                    if(tempMatch[2] == "1" || tempMatch[2] == "2")
    //                    {
    //                        match->setBackgroundColor(Qt::white);
    //                        match->setTextColor(Qt::black);
    //                    }
                        ui->viewDrawTable->setItem(roundRow+x+1, y, match);
                        htmlOut+= "<td style='text-align: center; padding-top: 8px; padding-bottom: 8px;font-size: " +QString::number(fontSize) +"px; '>" + teamNames[ tempMatch[2].toInt()-1 ] + "<br>v<br>" + teamNames[tempMatch[0].toInt()-1]+ " </td>";

                    }
                    else
                    {
                        QStringList tempMatch = drawPretty[x][y].split(" ");
                        QTableWidgetItem *match = new QTableWidgetItem(teamNames[ tempMatch[0].toInt()-1 ] + " v " + teamNames[tempMatch[2].toInt()-1]);
                        ui->viewDrawTable->setItem(roundRow+x+1, y, match);
                        htmlOut+= "<td style='text-align: center; padding-top: 8px; padding-bottom: 8px; font-size: " +QString::number(fontSize) +"px;'>" + teamNames[ tempMatch[0].toInt()-1 ] + "<br>v<br>" + teamNames[tempMatch[2].toInt()-1] + " </td>";
                    }
                   // match->setBackgroundColor(Qt::red);
                }
                htmlOut+= "</tr>";

            }
            htmlOut += "</table><br>";
            roundRow+=teamCount/2+1;

        }

    }


    QTableWidgetItem *compName = new QTableWidgetItem(QString(Database::search("COMPETITION", "name", "id =" + id)[0]));
    QFont font = compName->font();
    font.setPointSize(18);
    compName->setFont(font);

    ui->viewDrawTable->setItem(0, 0, compName);
    ui->viewDrawTable->resizeColumnsToContents();
    ui->viewDrawTable->resizeRowsToContents();
    ui->viewDrawTable->setRowCount(roundRow+1);
}


ViewDraw::~ViewDraw()
{
    delete ui;
}

void ViewDraw::on_buttonPDFExport_clicked()
{

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName(fileName);
    QTextDocument doc;
    doc.setHtml("<body>" + htmlOut + "</body>");
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}
