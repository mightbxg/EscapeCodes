#include <QCoreApplication>
#include <iostream>

using namespace std;

#ifndef CS
#include <QDebug>
#define CS qDebug()
#endif

#define COLOR_STR(code, var) (QString("\033[%1m%2\033[0m").arg(code).arg(var))

QString getSample(int code, QString sample = "Sample")
{
    return QString("%1:%2").arg(code, 3).arg(COLOR_STR(code, sample));
}

void printSpecialSample(int code, QString description, QString warnMsg = "")
{
    QString sample = getSample(code);
    QString msg = sample + " - " + description;
    if (!warnMsg.isEmpty()) {
        msg += QString("\n%1%2").arg("", 13).arg(COLOR_STR(1, warnMsg));
    }
    CS << qPrintable(msg);
}

void printControlCode(QString code, QString description)
{
    QString codeString = QString("%1").arg("\\33[" + code);
    QString msg = QString("%1 - %2").arg(codeString).arg(description);
    CS << qPrintable(msg);
}

int main(int argc, char* argv[])
{
    CS << "ANSI Escape Codes";
    CS << "---------------------------";

    CS << "\nForeground Colors";
    CS << "---------------------------";
    for (int code = 30; code < 38; code++) {
        QString msg = QString("%1 %2")
                          .arg(getSample(code))
                          .arg(getSample(code + 60));
        CS << qPrintable(msg);
    }
    printSpecialSample(39, "Default foreground color");

    CS << "\nBackground Colors";
    CS << "---------------------------";
    for (int code = 40; code < 48; code++) {
        QString msg = QString("%1 %2")
                          .arg(getSample(code))
                          .arg(getSample(code + 60));
        CS << qPrintable(msg);
    }
    printSpecialSample(49, "Default background color");

    CS << "\nSpecial Display Fonts";
    CS << "---------------------------";
    printSpecialSample(0, "Reset / Normal", "All attributes off");
    printSpecialSample(1, "Bold or increased intensity [CANCEL: 22]");
    printSpecialSample(2, "Faint(decreased intensity) [CANCEL: 22]");
    printSpecialSample(3, "Italic [CANCEL: 23]", "Not widely supported. Sometimes treated as inverse.");
    printSpecialSample(4, "Underline [CANCEL: 24]");
    printSpecialSample(5, "Slow Blink [CANCEL: 25]", "Less than 150 per minute");
    printSpecialSample(6, "Rapid Blink", "MS-DOS ANSI.SYS; 150+ per minute; not widely supported");
    printSpecialSample(7, "Reverse video", "Swap foreground and background colors");
    printSpecialSample(8, "Conceal [CANCEL: 28]", "Not widely supported");
    printSpecialSample(9, "Crossed-out [CANCEL: 29]", "Characters legible, but marked for deletion.");
    printSpecialSample(10, "Primary(defalut) font");
    printSpecialSample(20, "Fraktur [CANCEL: 23]", "Rarely supported");
    printSpecialSample(51, "Framed [CANCEL: 54]");
    printSpecialSample(52, "Encircled [CANCEL: 54]");
    printSpecialSample(53, "Overlined [CANCEL: 55]");

    CS << "\nControl Codes";
    CS << "---------------------------";
#define iN COLOR_STR(3, "n")
    printControlCode(iN + "A", "Move cursor up " + iN);
    printControlCode(iN + "B", "Move cursor down " + iN);
    printControlCode(iN + "C", "Move cursor right " + iN);
    printControlCode(iN + "D", "Move cursor left " + iN);
    printControlCode(iN + "A", "Move cursor up " + iN);
    printControlCode(COLOR_STR(3, "y") + ";" + COLOR_STR(3, "x") + "H",
        QString("Move cursor to (%1,%2)").arg(COLOR_STR(3, "x")).arg(COLOR_STR(3, "y")));
    printControlCode("2J", "Clear screen");
    printControlCode("K", "Clear contents from current cursor to the end of the line");
    printControlCode("s", "Save current positon of cursor");
    printControlCode("u", "Recover saved positon of cursor");
    printControlCode("?25l", "Conceal cursor");
    printControlCode("?25h", "Reveal cursor");

    CS << "";
    return 0;
}
