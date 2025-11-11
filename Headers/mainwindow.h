#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TaskManager.h" // Ներառում ենք մեր TaskManager-ը, որպեսզի կարողանանք այն օգտագործել

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT // Սա Qt-ի պարտադիր մակրոն է, որն անհրաժեշտ է signals & slots-ի համար

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Այս ֆունկցիան (slot) ավտոմատ կերպով կկանչվի, երբ executeButton անունով
    // օբյեկտի clicked() ազդանշանը (signal) աշխատի։
    void on_executeButton_clicked();

private:
    // Սա ցուցիչ է դեպի մեր .ui ֆայլում ստեղծված բոլոր վիզուալ էլեմենտները
    Ui::MainWindow *ui;

    // Սա մեր ծրագրի "հիշողությունն" է։ Ստեղծվում է մեկ անգամ՝ պատուհանի հետ
    // միասին և պահպանում է բոլոր առաջադրանքները։
    TaskManager m_taskManager;

    // Սա օգնական ֆունկցիա է, որը մենք կգրենք՝ առաջադրանքների ցուցակը
    // էկրանին թարմացնելու համար։
    void updateTasksView();
};
#endif // MAINWINDOW_H
