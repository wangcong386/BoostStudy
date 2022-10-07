#ifndef BOOSTTESTWIN_H
#define BOOSTTESTWIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BoostTestWin; }
QT_END_NAMESPACE

class BoostTestWin : public QMainWindow
{
    Q_OBJECT

public:
    BoostTestWin(QWidget *parent = nullptr);
    ~BoostTestWin();

private:
    Ui::BoostTestWin *ui;
};
#endif // BOOSTTESTWIN_H
